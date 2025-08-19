/*
Copyright 2024 aki27

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"

#define MS_BTN1 KC_MS_BTN1
#define MS_BTN2 KC_MS_BTN2
#define MS_BTN3 KC_MS_BTN3

#define COCOT_SCROLL_INV_DEFAULT false

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_Q,          KC_W,          KC_E,             KC_R,           KC_T,                                  KC_Y,           KC_U,          KC_I,          KC_O,           KC_P,
        KC_A,          LALT_T(KC_S),  LCTL_T(KC_D),     LGUI_T(KC_F),   KC_G,                                  KC_H,           KC_J,          KC_K,          KC_L,           RCTL_T(KC_SCLN),
        LSFT_T(KC_Z),  KC_X,          KC_C,             KC_V,           KC_B,                                  KC_N,           KC_M,          KC_COMM,       RALT_T(KC_DOT), RSFT_T(KC_SLSH),
                                      KC_ESC,           MO(2),          LGUI_T(KC_TAB),  XXXXXXX, MS_BTN1,     RSFT_T(KC_SPC), MO(1),         KC_RGUI
    ),
    [1] = LAYOUT(
        KC_PSLS,       KC_P7,         KC_P8,            KC_P9,          KC_PMNS,                               XXXXXXX,        KC_BSPC,       KC_DEL,        KC_TAB,         KC_MINS,
        KC_PAST,       KC_P4,         KC_P5,            KC_P6,          KC_PPLS,                               KC_LEFT,        KC_DOWN,       KC_UP,         KC_RIGHT,       RCTL_T(KC_ENT),
        LSFT_T(KC_P0), KC_P1,         KC_P2,            KC_P3,          KC_PEQL,                               KC_HOME,        KC_PGDN,       KC_PGUP,       RALT_T(KC_END), KC_RSFT,
                                      KC_SPC,           LT(3, KC_PDOT), LGUI_T(KC_BSPC), MO(5),   LGUI(KC_P0), XXXXXXX,        XXXXXXX,       XXXXXXX
    ),
    [2] = LAYOUT(
        LSFT(KC_SLSH), LSFT(KC_QUOT), LSFT(KC_1),       KC_BSPC,        LSFT(KC_GRAVE),                        XXXXXXX,        LSFT(KC_MINS), LSFT(KC_9),    LSFT(KC_0),     LSFT(KC_5),
        LSFT(KC_2),    KC_QUOT,       LSFT(KC_4),       KC_DEL,         KC_SLSH,                               LSFT(KC_3),     XXXXXXX,       KC_LBRC,       KC_RBRC,        XXXXXXX,
        XXXXXXX,       KC_GRAVE,      LSFT(KC_6),       LSFT(KC_BSLS),  KC_BSLS,                               LSFT(KC_7),     XXXXXXX,       LSFT(KC_LBRC), LSFT(KC_RBRC),  KC_RSFT,
                                      XXXXXXX,          XXXXXXX,        XXXXXXX,         MO(5),   XXXXXXX,     RSFT_T(KC_ENT), MO(3),         XXXXXXX
    ),
    [3] = LAYOUT(
        KC_MUTE,       KC_F7,         KC_F8,            KC_F9,          KC_F12,                                MS_WHLL,        MS_WHLD,       MS_WHLU,       MS_WHLR,        LSG(KC_5),
        KC_VOLU,       KC_F4,         KC_F5,            KC_F6,          KC_F11,                                MS_LEFT,        MS_DOWN,       MS_UP,         MS_RGHT,        KC_BRIU,
        KC_VOLD,       KC_F1,         KC_F2,            KC_F3,          KC_F10,                                XXXXXXX,        KC_RGUI,       KC_RCTL,       KC_RALT,        RSFT_T(KC_BRID),
                                      LCTL(LGUI(KC_Q)), XXXXXXX,        XXXXXXX,         MO(5),   KC_MUTE,     MS_BTN1,        MS_BTN3,       MS_BTN2
    ),
    [4] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               MS_BTN1,        MS_BTN3,       MS_BTN2,       XXXXXXX,        XXXXXXX,
                                      XXXXXXX,          SCRL_MO,        MS_BTN1,         MS_BTN2, XXXXXXX,     XXXXXXX,        XXXXXXX,       XXXXXXX
    ),
    [5] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               RM_NEXT,        RM_HUEU,       RM_SATU,       RM_VALU,        RM_SPDU,
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               RM_PREV,        RM_HUED,       RM_SATD,       RM_VALD,        RM_SPDD,
                                      XXXXXXX,          MO(6),          MO(7),           RM_TOGG, XXXXXXX,     XXXXXXX,        XXXXXXX,       XXXXXXX    ),
    [6] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,
                                      MO(5),            XXXXXXX,        MO(7),           RM_TOGG, XXXXXXX,     XXXXXXX,        XXXXXXX,       XXXXXXX    ),
    [7] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,        XXXXXXX,                               XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,
                                      MO(5),            MO(6),          XXXXXXX,         QK_BOOT, XXXXXXX,     XXXXXXX,        XXXXXXX,       XXXXXXX    )
};



#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [1] =   { ENCODER_CCW_CW(LGUI(KC_PMNS), LGUI(KC_PPLS)) },
    [2] =   { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [3] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [4] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [5] =   { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [6] =   { ENCODER_CCW_CW(RM_HUED, RM_HUEU) },
    [7] =   { ENCODER_CCW_CW(RM_SATD, RM_SATU) },
};
#endif



bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
      case KC_LCTL:
        return true;
      case KC_LSFT:
        return true;
      case SCRL_MO:
        return true;
      default:
        return false;
    }
    return is_mouse_record_user(keycode, record);
}



#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    int is_layer = get_highest_layer(layer_state|default_layer_state);
    HSV hsv = {0, 255, rgblight_get_val()};
    if (is_layer == 1) {
      hsv.h = 43; //YELLOW
    } else if (is_layer == 2)  {
      hsv.h = 85; //GREEN
    } else if (is_layer == 3)  {
      hsv.h = 22; //CORAL
    } else if (is_layer == 4)  {
      hsv.h = 0; //RED
    } else if (is_layer == 5)  {
      hsv.h = 191; //PURPLE
    } else if (is_layer == 6)  {
      hsv.h = 64; //CHARTREUSE
    } else if (is_layer == 7)  {
      hsv.h = 224;
    } else {
      hsv.h = 128; //CYAN
    }
    RGB rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i <= led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
          rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return false;
};

#endif

