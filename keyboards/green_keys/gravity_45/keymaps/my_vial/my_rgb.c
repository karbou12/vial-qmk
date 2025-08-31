#ifdef RGBLIGHT_LAYERS
#include <my_keycodes.h>

typedef union {
    uint32_t raw;
    struct {
        bool is_rgb_per_layer;
    };
} user_config_t;

user_config_t user_config;

static hsv_t my_hsv;
static uint8_t my_mode = 0;
static uint8_t current_layer = 0;

/**
 * There are two way for implementations.
 * - USE_LAYER_SEGMENT
 *   - It may be common way because it is described on QMK web site.
 *   - If Hue and Sat are changed by key or rotary encorder on non-default layer, these are not changed as WYSIWYG.
 *
 * - Not USE_LAYER_SEGMENT
 *   - It may not be common way.
 *   - If Hue and Sat are changed by key or rotary encorder on non-default layer, these are changed as WYSIWYG.
 */

// #define USE_LAYER_SEGMENT

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_TURQUOISE});
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_CYAN});
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_MAGENTA});
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW});
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_AZURE});
const rgblight_segment_t PROGMEM my_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_SPRINGGREEN});
const rgblight_segment_t PROGMEM my_layer8_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_ORANGE});
const rgblight_segment_t PROGMEM my_capsword_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});
const rgblight_segment_t PROGMEM my_layerOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_OFF});

const rgblight_segment_t * const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer,
    my_layer4_layer,
    my_layer5_layer,
    my_layer6_layer,
    my_layer7_layer,
    my_layer8_layer,
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

static void set_rgblight_on_current_layer(void) {
    if (current_layer == 0) {
        set_rgblight_on_default_layer();
    } else if (current_layer < ARRAY_SIZE(my_rgb_layers)) {
        if (user_config.is_rgb_per_layer) {
            const rgblight_segment_t* const cur_seg = my_rgb_layers[current_layer];
            rgblight_sethsv_noeeprom(cur_seg->hue, cur_seg->sat, my_hsv.v);
            rgblight_mode_noeeprom(0);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_LAYER_TOG:
            if (record->event.pressed) {
                user_config.is_rgb_per_layer ^= true;
                eeconfig_update_user(user_config.raw);
            }
            return false;
        default:
            return true;
    }
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

void eeconfig_init_user(void) {
    user_config.raw = 1;
    user_config.is_rgb_per_layer = true;
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
#ifdef USE_LAYER_SEGMENT
    rgblight_layers = my_rgb_layers;
#endif
    record_current_rgblight();

    user_config.raw = eeconfig_read_user();
};

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

    if (user_config.is_rgb_per_layer) {
        for (int i = 1; i <= 8; i++) {
            rgblight_set_layer_state(i, layer_state_cmp(state, i));
        }
    }
#else
    const uint8_t prev_layer = current_layer;
    if (prev_layer == 0 && !is_caps_word_on()) {
        record_current_rgblight();
    }

    current_layer = get_highest_layer(state);
    if (!is_caps_word_on()) {
        set_rgblight_on_current_layer();
    }

#endif

    return state;
};

void caps_word_set_user(bool active) {
    if (active) {
        if (user_config.is_rgb_per_layer) {
            const rgblight_segment_t* const cur_seg = my_capsword_layer;
            rgblight_sethsv_noeeprom(cur_seg->hue, cur_seg->sat, my_hsv.v);
            rgblight_mode_noeeprom(0);
        }
    } else {
        set_rgblight_on_current_layer();
    }
}

#endif
