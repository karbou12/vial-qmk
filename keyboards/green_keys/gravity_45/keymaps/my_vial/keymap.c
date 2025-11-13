// Copyright 2025 takashicompany (@takashicompany)
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <my_keycodes.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐            ┌───┬───┬───┬───┬───┬───┐
      * │ESC│ Q │ W │ E │ R │ T │            │ Y │ U │ I │ O │ P │BSP│
      * ├───┼───┼───┼───┼───┼───┤  ┌──────┐  ├───┼───┼───┼───┼───┼───┤
      * │CTL│ A │ S │ D │ F │ G │  │Center│  │ H │ J │ K │ L │ENT│ENT│
      * ├───┼───┼───┼───┼───┼───┤  └──────┘  ├───┼───┼───┼───┼───┼───┤
      * │SFT│ Z │ X │ C │ V │ B │            │ N │ M │ , │ . │BSP│DEL│
      * └───┴───┼───┼───┼───┼───┤            ├───┼───┼───┼───┼───┴───┘
      *         │CTL│GUI│LN2│TAB│            │SPC│LG1│ALT│GUI│
      *         └───┴───┴───┴───┘            └───┴───┴───┴───┘
      */

    [0] = LAYOUT(
        KC_Q,          KC_W,          KC_E,            KC_R,           KC_T,            MO(2),               MO(2),          KC_Y,           KC_U,          KC_I,          KC_O,           KC_P,
        KC_A,          LALT_T(KC_S),  LCTL_T(KC_D),    LGUI_T(KC_F),   KC_G,            MO(3),      KC_NO,   MO(3),          KC_H,           KC_J,          KC_K,          KC_L,           RCTL_T(KC_SCLN),
        LSFT_T(KC_Z),  KC_X,          KC_C,            KC_V,           KC_B,            MO(1),               MO(1),          KC_N,           KC_M,          KC_COMM,       RALT_T(KC_DOT), RSFT_T(KC_SLSH),
                                      KC_ESC,          MO(2),          LGUI_T(KC_TAB),  KC_NO,               KC_NO,          RSFT_T(KC_SPC), MO(1),         KC_RGUI
    ),

    [1] = LAYOUT(
        KC_PSLS,       KC_P7,         KC_P8,           KC_P9,          KC_PMNS,         KC_TRNS,             KC_TRNS,        KC_NO,          KC_BSPC,       KC_DEL,        KC_TAB,         KC_MINS,
        KC_PAST,       KC_P4,         KC_P5,           KC_P6,          KC_PPLS,         KC_TRNS,    MO(4),   KC_TRNS,        KC_LEFT,        KC_DOWN,       KC_UP,         KC_RIGHT,       RCTL_T(KC_ENT),
        LSFT_T(KC_P0), KC_P1,         KC_P2,           KC_P3,          KC_PEQL,         KC_TRNS,             KC_TRNS,        KC_HOME,        KC_PGDN,       KC_PGUP,       RALT_T(KC_END), KC_RSFT,
                                      KC_SPC,          LT(3, KC_PDOT), LGUI_T(KC_BSPC), KC_NO,               KC_NO,          KC_NO,          KC_NO,         KC_NO
    ),

    [2] = LAYOUT(
        LSFT(KC_SLSH), LSFT(KC_QUOT), LSFT(KC_1),      KC_BSPC,        LSFT(KC_GRAVE),  KC_TRNS,             KC_TRNS,        KC_NO,          LSFT(KC_MINS), LSFT(KC_9),    LSFT(KC_0),     LSFT(KC_5),
        LSFT(KC_2),    KC_QUOT,       LSFT(KC_4),      KC_DEL,         KC_SLSH,         KC_TRNS,    MO(4),   KC_TRNS,        LSFT(KC_3),     KC_NO,         KC_LBRC,       KC_RBRC,        KC_NO,
        KC_NO,         KC_GRAVE,      LSFT(KC_6),      LSFT(KC_BSLS),  KC_BSLS,         KC_TRNS,             KC_TRNS,        LSFT(KC_7),     KC_NO,         LSFT(KC_LBRC), LSFT(KC_RBRC),  KC_RSFT,
                                      KC_NO,           KC_NO,          KC_NO,           KC_NO,               KC_NO,          RSFT_T(KC_ENT), MO(3),         KC_NO
    ),

    [3] = LAYOUT(
        KC_MUTE,       KC_F7,         KC_F8,            KC_F9,         KC_F12,          LSG(KC_3),           KC_PSCR,        MS_WHLL,        MS_WHLD,       MS_WHLU,       MS_WHLR,        LSG(KC_5),
        KC_VOLU,       KC_F4,         KC_F5,            KC_F6,         KC_F11,          LSG(KC_4),  MO(5),   LALT(KC_PSCR),  MS_LEFT,        MS_DOWN,       MS_UP,         MS_RGHT,        KC_BRIU,
        KC_VOLD,       KC_F1,         KC_F2,            KC_F3,         KC_F10,          LSG(KC_5),           LSG(KC_S),      KC_NO,          KC_RGUI,       KC_RCTL,       KC_RALT,        RSFT_T(KC_BRID),
                                      LCTL(LGUI(KC_Q)), KC_NO,         KC_NO,           KC_NO,               KC_NO,          MS_BTN1,        MS_BTN3,       MS_BTN2
    ),

    [4] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
                          MO(5),   MO(6),   MO(7),   MO(8),            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [5] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   UG_HUEU, UG_SATU, UG_VALU, KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   UG_HUED, UG_SATD, UG_VALD, KC_NO,  KC_NO,
                          MO(5),   MO(6),   MO(7),   MO(8),            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [6] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
                          MO(5),   MO(6),   MO(7),   MO(8),            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [7] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
                          MO(5),   MO(6),   MO(7),   MO(8),            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [8] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
                          MO(5),   MO(6),   MO(7),   MO(8),            KC_NO,   KC_NO,   KC_NO,   KC_NO
    )
};
