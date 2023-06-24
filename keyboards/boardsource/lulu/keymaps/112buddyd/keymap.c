#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _GAME,
    _CONTROL,
    _NUMPAD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC, KC_LGUI, KC_LGUI, MO(_CONTROL), KC_SPC, KC_ENT, MO(_CONTROL), KC_RALT, KC_RGUI),
	[_GAME] = LAYOUT(KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSLS, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_TRNS, KC_TRNS, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC, KC_LALT, KC_LALT, MO(_CONTROL), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[_CONTROL] = LAYOUT(KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_BSPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_UP, KC_NO, TO(_QWERTY), TO(_GAME), TO(_NUMPAD), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[_NUMPAD] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSLS, KC_PAST, KC_PMNS, KC_NO, KC_BSPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_PCMM, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_PEQL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P0, KC_PDOT, KC_PENT)
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
