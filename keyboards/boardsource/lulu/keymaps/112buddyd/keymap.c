#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _GAME,
    _COLE,
    _CTRL,
    _FUNC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC, KC_LGUI, KC_LALT, MO(3), KC_SPC, KC_ENT, MO(4), KC_BSPC, KC_DEL),
	[1] = LAYOUT(KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSLS, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LALT, KC_LALT, MO(3), KC_TRNS, KC_TRNS, MO(4), KC_TRNS, KC_TRNS),
	[2] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSLS, KC_LCTL, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC, KC_LGUI, KC_MINS, MO(3), KC_SPC, KC_ENT, MO(4), KC_EQL, KC_DEL),
	[3] = LAYOUT(KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR, KC_NO, KC_NO, KC_PGDN, KC_PGUP, KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_UP, KC_NO, KC_LSFT, TO(0), TO(1), TO(2), KC_NO, KC_NO, KC_MINS, KC_EQL, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[4] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LSFT, TO(0), TO(1), TO(2), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

#ifdef OLED_ENABLE

int current_wpm = 0;

#include "main-screen.c"
#include "luna.c"
#include "ocean_dream.c"

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  }
  return OLED_ROTATION_270;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
            isBarking = (record->event.pressed) ? true : false;
            is_calm = (record->event.pressed) ? true : false;
            break;
        case KC_LCTL:
        case KC_RCTL:
            isSneaking = (record->event.pressed) ? true : false;
            is_calm = (record->event.pressed) ? true : false;
            break;
        case KC_SPC:
                if (record->event.pressed) {
                    isJumping  = true;
                    showedJump = false;
                } else {
                    isJumping = false;
                }
            break;
    }
    return true;
}

bool oled_task_user(void) {
    current_wpm = get_current_wpm();

    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_stars();
    }
    return false;
}
#endif

