#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.                    
 * | NUM  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | TG(4)|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |OS_SFT|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  ESC  |    | RCTRL |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |CW_TG |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LALT |LOWER | /Space  /       \Enter \  |RAISE | NO   | NO   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */ [_QWERTY] = LAYOUT(
  KC_NUM,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TG(4),
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    OS_LSFT,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_ESC,   KC_RCTL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  CW_TOGG,
                        KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_NO, KC_NO
),
/* LOWER (Layer 1)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | NO   | F13  | F14  | F15  | F16  | F17  |                    |G+SPC | MPRV | MPLY | MNXT | NO   | NO   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |A+TAB | GRV  |C+W   |G+E   |C+R   |C+T   |                    | HOME | PGUP |  UP  | PGDN |  INS | NO   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS |C+A   | MB3  | MB2  | MB1  | F12  |-------.    ,-------|  END | LEFT | DOWN | RGHT |  DEL | NO   |
 * |------+------+------+------+------+------|PSCR  |    | TRNS  |------+------+------+------+------+------|
 * |LCTRL |LGUI  |C+X   |C+C   |C+V   |      |-------|    |-------|  NO  | NO   | NO   | NO   | NO   |CAPS  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | TRNS | TRNS | TRNS | / NO    /       \BSPC \ | ADJUST| NO   | NO   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  KC_NO, KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,                     LGUI(KC_SPC), KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO,
  LALT(KC_TAB), KC_GRV, LCTL(KC_W), LGUI(KC_E), LCTL(KC_R), LCTL(KC_T),    KC_HOME, KC_PGUP, KC_UP, KC_PGDN, KC_INS, KC_NO,
  KC_TRNS, LCTL(KC_A), MS_BTN3, MS_BTN2, MS_BTN1, KC_F12,                   KC_END, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, KC_NO,
  KC_LCTL, KC_LGUI, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_PSCR, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_CAPS,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_BSPC, MO(_ADJUST), KC_NO, KC_NO
),
/* RAISE (Layer 2)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | NO   | NO   | NO   | NO   | NO   | NO   |                    |  NO  | NO   | NO   | NO   | NO   | NO   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |A+TAB | NO   | NO   |A+E   | NO   | NO   |                    |  NO  |  <   |  >   | NO   | NO   | NO   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS | NO   | GRV  | MINS |  EQL | BSLS |-------.    ,-------|  NO  |  (   |  {   |  [   | NO   | NO   |
 * |------+------+------+------+------+------|  NO   |    | TRNS  |------+------+------+------+------+------|
 * | TRNS | NO   | TILD | UNDS | PLUS | PIPE |-------|    |-------|  NO  |  )   |  }   |  ]   | NO   | NO   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | TRNS | TRNS |ADJUST| / NO    /       \NO    \ | TRNS | NO   | NO   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT(
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  LALT(KC_TAB), KC_NO, KC_NO, RALT(KC_E), KC_NO, KC_NO,        KC_NO, KC_LT, KC_GT, KC_NO, KC_NO, KC_NO,
  KC_TRNS, KC_NO, KC_GRV, KC_MINS, KC_EQL, KC_BSLS,             KC_NO, KC_LPRN, KC_LCBR, KC_LBRC, KC_NO, KC_NO,
  KC_TRNS, KC_NO, KC_TILD, KC_UNDS, KC_PLUS, KC_PIPE, KC_NO, KC_TRNS, KC_NO, KC_RPRN, KC_RCBR, KC_RBRC, KC_NO, KC_NO,
                             KC_TRNS, KC_TRNS, MO(_ADJUST), KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
),
/* ADJUST (Layer 3)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | NO   | NO   | NO   | NO   | NO   | NO   |                    |  NO  |  P7  |  P8  |  P9  | NO   |UG_TG |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | NO   |  F1  |  F2  |  F3  |  F4  | NO   |                    |  NO  |  P4  |  P5  |  P6  |LALT  | NO   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS |  F5  |  F6  |  F7  |  F8  |LGUI  |-------.    ,-------|  NO  |  P1  |  P2  |  P3  | NO   | NO   |
 * |------+------+------+------+------+------|  NO   |    | TRNS  |------+------+------+------+------+------|
 * | TRNS |  F9  | F10  | F11  | F12  | NO   |-------|    |-------|  P0  | NO   | NO   | NO   | NO   | NO   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | NO   | NO   | TRNS | / NO    /       \NO    \ | TRNS | NO   | NO   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_P7, KC_P8, KC_P9, KC_NO, UG_TOGG,
  KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO,                   KC_NO, KC_P4, KC_P5, KC_P6, KC_LALT, KC_NO,
  KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_LGUI,               KC_NO, KC_P1, KC_P2, KC_P3, KC_NO, KC_NO,
  KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_TRNS, KC_P0, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
  ),

  /* GAMING (Layer 4)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | NO   | NO   | NO   | NO   | NO   | NO   |                    |  NO  | NO   |  UP  | NO   | NO   | TG(4)|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |  NO  | NO   | NO   | NO   | NO   | NO   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | NO   |   A  |   S  |   D  |   F  |   J  |-------.    ,-------|  NO  | LEFT | DOWN | RGHT | NO   | NO   |
 * |------+------+------+------+------+------|  NO   |    | TRNS  |------+------+------+------+------+------|
 * | NO   |   Z  |   X  |   C  |   V  |   M  |-------|    |-------|  NO  | NO   | NO   | NO   | NO   | NO   |
 * `-----------------------------------------/   I   /     \      \-----------------------------------------'
 *                   | NO   | NO   | NO   | /       /       \      \ | NO   | NO   | NO   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [4] = LAYOUT(
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                     KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, TG(4),
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  KC_NO, KC_A, KC_S, KC_D, KC_F, KC_J,                          KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,
  KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_M, KC_I, KC_TRNS,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
