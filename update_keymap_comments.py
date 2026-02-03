#!/usr/bin/env python3
"""
Generate ASCII keymap comments for QMK keymaps and update the keymap file.
This script automatically generates ASCII diagrams for each layer and updates the file.
"""

import re
from typing import List, Tuple, Optional

TEMPLATE = """
/* {name}
 * ,-----------------------------------------------.                    ,-----------------------------------------------.                    
 * |{0}|{1}|{2}|{3}|{4}|{5}|                    |{6}|{7}|{8}|{9}|{10}|{11}|
 * |-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
 * |{12}|{13}|{14}|{15}|{16}|{17}|                    |{18}|{19}|{20}|{21}|{22}|{23}|
 * |-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
 * |{24}|{25}|{26}|{27}|{28}|{29}|-------.    ,-------|{30}|{31}|{32}|{33}|{34}|{35}|
 * |-------+-------+-------+-------+-------+-------| {36}    {37} |-------+-------+-------+-------+-------+-------|
 * |{37}|{38}|{39}|{40}|{41}|{42}|-------|    |-------|{45}|{46}|{47}|{48}|{49}|{50}|
 * `-----------------------------------------------/       /    \\       \\-----------------------------------------------'
 *                   |{51}|{52}|{53}|    /{54}/      \\{55}\\  |{56}|{57}|{58}|
 *                   |       |       |       |   /       /        \\       \\ |       |       |       |
 *                   `----------------------------------'          '-------''-------------------------'
 */
"""

def test():
    a = ['i' for i in range(59)]
    for i in range(len(a)):
        if i == 54:
            a[i] = '   i   '
        else:
            a[i] = '   i   ' 
    result = TEMPLATE.format(name="test", *a)

class KeymapCommentGenerator:
    """Generate ASCII comments for QMK keymap layers."""
    
    # Mapping of keycodes to display names
    KEYCODE_DISPLAY = {
        'KC_NO': 'NO',
        'KC_TRNS': 'TRNS',
        'KC_ESC': 'ESC',
        'KC_TAB': 'Tab',
        'KC_LSFT': 'LShift',
        'KC_RSFT': 'RShift',
        'KC_LCTL': 'LCTRL',
        'KC_RCTL': 'RCTRL',
        'KC_LALT': 'LALT',
        'KC_RALT': 'RALT',
        'KC_LGUI': 'LGUI',
        'KC_RGUI': 'RGUI',
        'KC_SPC': 'Space',
        'KC_ENT': 'Enter',
        'KC_BSPC': 'BackSP',
        'KC_DEL': 'Delete',
        'KC_HOME': 'Home',
        'KC_END': 'End',
        'KC_PGUP': 'PgUp',
        'KC_PGDN': 'PgDn',
        'KC_UP': 'Up',
        'KC_DOWN': 'Down',
        'KC_LEFT': 'Left',
        'KC_RGHT': 'Right',
        'KC_NUM': 'NUM',
        'KC_GRV': '`',
        'KC_MINS': '-',
        'KC_EQL': '=',
        'KC_BSLS': '\\',
        'KC_LBRC': '[',
        'KC_RBRC': ']',
        'KC_SCLN': ';',
        'KC_QUOT': "'",
        'KC_COMM': ',',
        'KC_DOT': '.',
        'KC_SLSH': '/',
        'KC_EXLM': '!',
        'KC_AT': '@',
        'KC_HASH': '#',
        'KC_DLR': '$',
        'KC_PERC': '%',
        'KC_CIRC': '^',
        'KC_AMPR': '&',
        'KC_ASTR': '*',
        'KC_LPRN': '(',
        'KC_RPRN': ')',
        'KC_UNDS': '_',
        'KC_PLUS': '+',
        'KC_LCBR': '{',
        'KC_RCBR': '}',
        'KC_PIPE': '|',
        'KC_TILD': '~',
        'KC_LT': '<',
        'KC_GT': '>',
        'XXXXXXX': 'X',
        '_______': '___',
    }
    
    def __init__(self, rows: int = 4, cols: int = 12):
        """Initialize with keyboard dimensions."""
        self.rows = rows
        self.cols = cols
    
    def keycode_to_display(self, keycode: str) -> str:
        """Convert a keycode to its display representation."""
        keycode = keycode.strip()
        
        # Direct mapping
        if keycode in self.KEYCODE_DISPLAY:
            return self.KEYCODE_DISPLAY[keycode]
        
        # Function keys (KC_F1, KC_F2, etc.)
        if keycode.startswith('KC_F'):
            match = re.match(r'KC_F(\d+)', keycode)
            if match:
                return f"F{match.group(1)}"
        
        # Numpad keys (KC_P0-KC_P9)
        if keycode.startswith('KC_P'):
            match = re.match(r'KC_P(\d)', keycode)
            if match:
                return f"P{match.group(1)}"
        
        # Momentary layer (MO(1), MO(2), etc.)
        if keycode.startswith('MO('):
            return keycode
        
        # Toggle layer (TG(4), etc.)
        if keycode.startswith('TG('):
            return keycode
        
        # Layer tap (LT(_LOWER, KC_SPC), etc.)
        if keycode.startswith('LT('):
            return keycode
        
        # Mod-tap combinations
        if keycode.startswith('LCTL(') or keycode.startswith('LGUI(') or \
           keycode.startswith('LALT(') or keycode.startswith('LSFT(') or \
           keycode.startswith('RCTL(') or keycode.startswith('RGUI(') or \
           keycode.startswith('RALT(') or keycode.startswith('RSFT('):
            # Extract the inner keycode and create abbreviation
            match = re.match(r'([A-Z]+)\(([^)]+)\)', keycode)
            if match:
                mod, inner = match.groups()
                inner_display = self.keycode_to_display(inner)
                # Create abbreviated mod name
                mod_abbr = mod.replace('CTRL', 'C').replace('GUI', 'G').replace('ALT', 'A').replace('SFT', 'S')
                return f"{mod_abbr}+{inner_display}"
        
        # Mouse buttons
        if keycode.startswith('MS_BTN'):
            match = re.match(r'MS_BTN(\d)', keycode)
            if match:
                return f"MB{match.group(1)}"
        
        # Media keys
        if keycode.startswith('KC_M'):
            media_map = {
                'KC_MPLY': 'PLAY',
                'KC_MPRV': 'PREV',
                'KC_MNXT': 'NEXT',
                'KC_MUTE': 'MUTE',
                'KC_VOLU': 'VOL+',
                'KC_VOLD': 'VOL-',
            }
            if keycode in media_map:
                return media_map[keycode]
        
        # RGB/LED keys
        rgb_map = {
            'RGB_TOG': 'RGB',
            'RGB_HUI': 'HUE+',
            'RGB_HUD': 'HUE-',
            'RGB_SAI': 'SAT+',
            'RGB_SAD': 'SAT-',
            'RGB_VAI': 'VAL+',
            'RGB_VAD': 'VAL-',
            'RGB_MOD': 'MODE',
            'UG_TOGG': 'UG_TG',
        }
        if keycode in rgb_map:
            return rgb_map[keycode]
        
        # CW/Caps word
        if keycode == 'CW_TOGG':
            return 'CW_TG'
        
        # OS (one-shot) keys
        if keycode.startswith('OS_'):
            return keycode.replace('OS_', 'OS_')
        

        if keycode.startswith('KC_'):
            return keycode.replace('KC_', '')
        
        
        # Default: return as-is if it's a reasonable length, otherwise truncate
        if len(keycode) <= 6:
            return keycode
        
        return keycode[:5] + '.'
    
    def extract_keycodes_from_layout(self, layout_line: str) -> List[str]:
        """Extract keycodes from a LAYOUT line."""
        # Remove LAYOUT( prefix and trailing )
        layout_line = re.sub(r'.*LAYOUT\s*\(\s*', '', layout_line)
        layout_line = re.sub(r'\)\s*[,)]?\s*$', '', layout_line)
        
        # Split by comma, handling nested parentheses
        keycodes = []
        current = []
        depth = 0
        
        for char in layout_line:
            if char == '(':
                depth += 1
            elif char == ')':
                depth -= 1
            elif char == ',' and depth == 0:
                keycodes.append(''.join(current).strip())
                current = []
                continue
            current.append(char)
        
        if current:
            keycodes.append(''.join(current).strip())
        
        if keycodes:
            for i in range(len(keycodes)):
                keycodes[i] = self.keycode_to_display(keycodes[i])
        
        return keycodes
    
    def generate_comment(self, keycodes: List[str], layer_name: str = "") -> str:
        """Generate ASCII comment for a layer given list of keycodes."""
        if not keycodes:
            return ""
        
        if len(keycodes) != 58:
            return ""
        
        for i in range(len(keycodes)):
            codelen = len(keycodes[i])
            empty_tot = 7 - codelen
            prefix = ''.join([' ' for _ in range(empty_tot // 2)])
            suffix = ''.join([' ' for _ in range(empty_tot // 2 + empty_tot % 2)])
            keycodes[i] = prefix + keycodes[i] + suffix
        
        return TEMPLATE.format(name=layer_name, *keycodes)
 
    def parse_keymap_file(self, filename: str) -> List[Tuple[str, List[str], int]]:
        """Parse keymap file and extract layer information."""
        layers = []
        
        with open(filename, 'r') as f:
            lines = f.readlines()
        
        i = 0
        while i < len(lines):
            line = lines[i]
            
            # Look for layer definition: [_LAYERNAME] = LAYOUT(
            # This pattern finds it even if it's on the same line as */ or other content
            match = re.search(r'\[\s*(_?[0-9A-Z_]+)\s*\]\s*=\s*LAYOUT\s*\(', line)
            if match:
                layer_name = match.group(1)
                start_pos = i
                
                # Collect all lines until we find the closing );
                layout_lines = [line]
                i += 1
                paren_count = line.count('(') - line.count(')')
                
                while i < len(lines) and paren_count > 0:
                    layout_lines.append(lines[i])
                    paren_count += lines[i].count('(') - lines[i].count(')')
                    i += 1
                
                # Combine all layout lines
                full_layout = ''.join(layout_lines)
                
                # Extract keycodes
                keycodes = self.extract_keycodes_from_layout(full_layout)
                
                if keycodes:  # Only add if we found keycodes
                    layers.append((layer_name, keycodes, start_pos))
            else:
                i += 1
        
        return layers
    
    def update_keymap_file(self, filename: str) -> bool:
        """Parse keymap file and update it with generated comments."""
        with open(filename, 'r') as f:
            content = f.read()
        
        layers = self.parse_keymap_file(filename)
        
        if not layers:
            print("No layers found!")
            return False
        
        # Sort layers by position (reverse order so we replace from end to beginning)
        layers.sort(key=lambda x: x[2], reverse=True)
        
        # For each layer, find and replace the comment above it
        for layer_name, keycodes, start_pos in layers:
            # Generate new comment
            new_comment = self.generate_comment(keycodes, layer_name)
            
            # Find the pattern: /* ... */ [_LAYERNAME] = LAYOUT(
            # We want to replace everything from /* to the opening ( on the same line as [_LAYERNAME]
            pattern = r'/\*.*?\*/' + r'\s*\[\s*' + re.escape(layer_name) + r'\s*\]\s*=\s*LAYOUT\s*\('
            
            # Create replacement: new comment + the layer definition line
            # We need to preserve the original LAYOUT line
            match = re.search(pattern, content, re.DOTALL)
            if match:
                # Extract the part after LAYOUT(
                after_layout = content[match.end():]
                
                # Find the start of the next line for the first keycode
                # Keep everything from LAYOUT( onwards
                replacement = new_comment + '\n' + f'[{layer_name}] = LAYOUT('
                
                content = content[:match.start()] + replacement + after_layout
        
        # Write back to file
        with open(filename, 'w') as f:
            f.write(content)
        
        return True

def main():
    """Main function."""
    import sys
    
    if len(sys.argv) < 2:
        print("Usage: python generate_keymap_comments.py <keymap.c> [--update]")
        print("\nOptions:")
        print("  --update    Update the keymap file with generated comments")
        print("\nExample:")
        print("  python generate_keymap_comments.py keyboards/lily58/rev1/keymaps/nickpnevmati/keymap.c")
        print("  python generate_keymap_comments.py keyboards/lily58/rev1/keymaps/nickpnevmati/keymap.c --update")
        sys.exit(1)
    
    filename = sys.argv[1]
    update = '--update' in sys.argv
    
    generator = KeymapCommentGenerator()
    
    if update:
        print(f"Updating {filename}...")
        if generator.update_keymap_file(filename):
            print("✓ File updated successfully!")
        else:
            print("✗ Failed to update file")
            sys.exit(1)
    else:
        layers = generator.parse_keymap_file(filename)
        print(f"Found {len(layers)} layers:\n")
        
        for layer_name, keycodes, _ in layers:
            print(f"Layer: {layer_name} ({len(keycodes)} keycodes)\n")
            comment = generator.generate_comment(keycodes, layer_name)
            print(comment)
            print("\n" + "="*80 + "\n")

if __name__ == '__main__':
    main()
