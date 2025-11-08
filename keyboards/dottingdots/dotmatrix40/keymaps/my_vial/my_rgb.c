// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef RGBLIGHT_LAYERS

static hsv_t my_hsv;
static uint8_t my_mode = 0;

/**
 * There are two implementations.
 * - USE_LAYER_SEGMENT
 *   - It may be common way because it is described on QMK web site.
 *   - If Hue and Sat are changed by key or rotary encorder on non-default layer, these are not changed as WYSIWYG.
 *
 * - Not USE_LAYER_SEGMENT
 *   - It may not be common way.
 *   - If Hue and Sat are changed by key or rotary encorder on non-default layer, these are changed as WYSIWYG.
 */

// #define USE_LAYER_SEGMENT

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_YELLOW});
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_GREEN});
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_CYAN});
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_ORANGE});
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_CHARTREUSE});
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_MAGENTA});
const rgblight_segment_t PROGMEM my_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_BLUE});
const rgblight_segment_t PROGMEM my_capsword_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_RED});
const rgblight_segment_t PROGMEM my_layerOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_OFF});

const rgblight_segment_t * const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer,
    my_layer4_layer,
    my_layer5_layer,
    my_layer6_layer,
    my_layer7_layer,
    my_capsword_layer
);

static void record_current_rgblight(void) {
    my_mode = rgblight_get_mode();
    my_hsv.h = rgblight_get_hue();
    my_hsv.s = rgblight_get_sat();
    my_hsv.v = rgblight_get_val();
}

static void set_rgblight_on_default_layer(void) {
    rgblight_sethsv_noeeprom(my_hsv.h, my_hsv.s, my_hsv.v);
    rgblight_mode_noeeprom(my_mode);
}

void keyboard_post_init_user() {
#ifdef USE_LAYER_SEGMENT
    rgblight_layers = my_rgb_layers;
#endif
    record_current_rgblight();
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UG_NEXT:
        case UG_PREV:
            my_mode = rgblight_get_mode();
            break;

        case UG_HUED:
        case UG_HUEU:
            my_hsv.h = rgblight_get_hue();
            break;

        case UG_SATD:
        case UG_SATU:
            my_hsv.s = rgblight_get_sat();
            break;

        case UG_VALD:
        case UG_VALU:
            my_hsv.v = rgblight_get_val();
            break;

        default:
            break;
    }
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    record_current_rgblight();
    set_rgblight_on_default_layer();

    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {

#ifdef USE_LAYER_SEGMENT
    if (get_highest_layer(state) == 0) {
        record_current_rgblight();
    }

    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    rgblight_set_layer_state(7, layer_state_cmp(state, 7));
#else
    static uint8_t prev_layer = 0;
    if (prev_layer == 0) {
        record_current_rgblight();
    }

    uint8_t current_layer = get_highest_layer(state);
    if (1 <= current_layer && current_layer <= 7) {
        const rgblight_segment_t* const cur_seg = my_rgb_layers[current_layer];
        rgblight_sethsv_noeeprom(cur_seg->hue, cur_seg->sat, my_hsv.v);
        rgblight_mode_noeeprom(0);
    } else {
        set_rgblight_on_default_layer();
    }

    prev_layer = current_layer;
#endif

    return state;
}

void caps_word_set_user(bool active) {
    if (active) {
        const rgblight_segment_t* const cur_seg = my_capsword_layer;
        rgblight_sethsv_noeeprom(cur_seg->hue, cur_seg->sat, my_hsv.v);
        rgblight_mode_noeeprom(0);
    } else {
        set_rgblight_on_default_layer();
    }
}

#endif
