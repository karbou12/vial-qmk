// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_Q,          KC_W,          KC_E,             KC_R,           KC_T,            MO(2),   MO(2),       KC_Y,           KC_U,          KC_I,          KC_O,           KC_P,
        KC_A,          LALT_T(KC_S),  LCTL_T(KC_D),     LGUI_T(KC_F),   KC_G,            MO(3),   MO(3),       KC_H,           KC_J,          KC_K,          KC_L,           RCTL_T(KC_SCLN),
        LSFT_T(KC_Z),  KC_X,          KC_C,             KC_V,           KC_B,            MO(1),   MO(1),       KC_N,           KC_M,          KC_COMM,       RALT_T(KC_DOT), RSFT_T(KC_SLSH),
        KC_NO,         KC_NO,         KC_ESC,           MO(2),          LGUI_T(KC_TAB),       KC_NO,           RSFT_T(KC_SPC), MO(1),         KC_RGUI,       KC_NO,          KC_NO
    ),
    [1] = LAYOUT(
        KC_PSLS,       KC_P7,         KC_P8,            KC_P9,          KC_PMNS,         KC_TRNS, KC_TRNS,     KC_NO,          KC_BSPC,       KC_DEL,        KC_TAB,         KC_MINS,
        KC_PAST,       KC_P4,         KC_P5,            KC_P6,          KC_PPLS,         KC_TRNS, KC_TRNS,     KC_LEFT,        KC_DOWN,       KC_UP,         KC_RIGHT,       RCTL_T(KC_ENT),
        LSFT_T(KC_P0), KC_P1,         KC_P2,            KC_P3,          KC_PEQL,         KC_TRNS, KC_TRNS,     KC_HOME,        KC_PGDN,       KC_PGUP,       RALT_T(KC_END), KC_RSFT,
        KC_NO,         KC_NO,         KC_SPC,           LT(3, KC_PDOT), LGUI_T(KC_BSPC),      KC_NO,           KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO
    ),
    [2] = LAYOUT(
        LSFT(KC_SLSH), LSFT(KC_QUOT), LSFT(KC_1),       KC_BSPC,        LSFT(KC_GRAVE),  KC_TRNS, KC_TRNS,     KC_NO,          LSFT(KC_MINS), LSFT(KC_9),    LSFT(KC_0),     LSFT(KC_5),
        LSFT(KC_2),    KC_QUOT,       LSFT(KC_4),       KC_DEL,         KC_SLSH,         KC_TRNS, KC_TRNS,     LSFT(KC_3),     KC_NO,         KC_LBRC,       KC_RBRC,        KC_NO,
        KC_NO,         KC_GRAVE,      LSFT(KC_6),       LSFT(KC_BSLS),  KC_BSLS,         KC_TRNS, KC_TRNS,     LSFT(KC_7),     KC_NO,         LSFT(KC_LBRC), LSFT(KC_RBRC),  KC_RSFT,
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,                KC_NO,           RSFT_T(KC_ENT), MO(3),         KC_NO,         KC_NO,          KC_NO
    ),
    [3] = LAYOUT(
        KC_MUTE,       KC_F7,         KC_F8,            KC_F9,          KC_F12,      LSG(KC_3), KC_PSCR,       MS_WHLL,        MS_WHLD,       MS_WHLU,       MS_WHLR,        LSG(KC_5),
        KC_VOLU,       KC_F4,         KC_F5,            KC_F6,          KC_F11,      LSG(KC_4), LALT(KC_PSCR), MS_LEFT,        MS_DOWN,       MS_UP,         MS_RGHT,        KC_BRIU,
        KC_VOLD,       KC_F1,         KC_F2,            KC_F3,          KC_F10,      LSG(KC_5), LSG(KC_S),     KC_NO,          KC_RGUI,       KC_RCTL,       KC_RALT,        RSFT_T(KC_BRID),
        LCTL(LGUI(KC_Q)), MO(4),      MO(5),            MO(6),          MO(7),                KC_NO,           MS_BTN1,        MS_BTN3,       MS_BTN2,       KC_NO,          KC_NO
    ),
    [4] = LAYOUT(
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        UG_TOGG,       MO(4),         MO(5),            MO(6),          MO(7),                KC_NO,           KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO
    ),
    [5] = LAYOUT(
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        UG_TOGG,       MO(4),         MO(5),            MO(6),          MO(7),                KC_NO,           KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO
    ),
    [6] = LAYOUT(
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    QK_BOOT,     KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       UG_NEXT,        UG_HUEU,       UG_SATU,       UG_VALU,        UG_SPDU,
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       UG_PREV,        UG_HUED,       UG_SATD,       UG_VALD,        UG_SPDD,
        UG_TOGG,       MO(4),         MO(5),            MO(6),          MO(7),                KC_NO,           KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO
    ),
    [7] = LAYOUT(
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        KC_NO,         KC_NO,         KC_NO,            KC_NO,          KC_NO,          KC_NO,    KC_NO,       KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO,
        UG_TOGG,       MO(4),         MO(5),            MO(6),          MO(7),                KC_NO,           KC_NO,          KC_NO,         KC_NO,         KC_NO,          KC_NO
    ),
    [8] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
    [9] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
/* layer 0 */    [0]   = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU)},
/* layer 1 */    [1]   = { ENCODER_CCW_CW(LGUI(KC_PMNS), LGUI(KC_PPLS))},
/* layer 2 */    [2]   = { ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
/* layer 3 */    [3]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
/* layer 4 */    [4]   = { ENCODER_CCW_CW(UG_HUED, UG_HUEU)},
/* layer 5 */    [5]   = { ENCODER_CCW_CW(UG_SATD, UG_SATU)},
/* layer 6 */    [6]   = { ENCODER_CCW_CW(UG_VALD, UG_VALU)},
/* layer 7 */    [7]   = { ENCODER_CCW_CW(BL_DOWN, BL_UP)},
/* layer 8 */    [8]   = { ENCODER_CCW_CW(KC_NO, KC_NO)},
/* layer 9 */    [9]   = { ENCODER_CCW_CW(KC_NO, KC_NO)}
};
#endif
