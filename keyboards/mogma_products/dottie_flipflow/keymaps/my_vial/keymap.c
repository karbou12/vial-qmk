// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define L1_ENT LT(1,KC_ENT)
#define L2_SPC LT(2,KC_SPC)
#define L1_ESC LT(1,KC_ESC)
#define L2_RBRC LT(2,KC_RBRC)
#define L3_LBRC LT(3,KC_LBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
      * │ ~ │ Q │ W │ E │ R │ T │   │ Y │ U │ I │ O │ P │ = │
      * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
      * │TAB│ A │ S │ D │ F │ G │   │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ Z │ X │ C │ V │ B │   │ N │ M │ , │ . │ / │ \ │
      * └───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┘
      *     │esc│ [ │GUI│SFT│SPC│   │ENT│SFT│GUI│LT1│BS │
      *     └───┴───┴───┴───┴───┘   └───┴───┴───┴───┴───┘
      */
    [0] = LAYOUT(
        KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                 L1_ESC,  L3_LBRC, KC_LGUI, SC_LSPO, L2_SPC,  L1_ENT,  SC_RSPC, KC_RGUI, L2_RBRC, KC_BSPC
    ),
    [1] = LAYOUT(
        _______, _______, KC_1,    KC_2,    KC_3,    KC_DOT,  _______, _______, _______, _______, _______, _______,
        _______, _______, KC_4,    KC_5,    KC_6,    KC_MINS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, KC_7,    KC_8,    KC_9,    KC_0,    _______, KC_PGDN, KC_PGUP, _______, _______, _______,
                 _______, _______, _______, _______, KC_EQL,  _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F10,  _______,
        _______, _______, _______, KC_BSPC, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

// RGBLayer setting
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_AZURE});
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_ORANGE});
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_SPRINGGREEN});
const rgblight_segment_t PROGMEM my_layerOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_OFF});

const rgblight_segment_t * const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
};

// LayerIndicator
layer_state_t layer_state_set_user(layer_state_t state) {
    // Layer0はVia,remapで設定されたRGBを反映させるためにここでは定義しない
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));

    return state;
};
