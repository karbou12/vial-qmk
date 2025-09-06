#ifdef RGBLIGHT_LAYERS

static hsv_t my_hsv;
static uint8_t my_mode = 0;

const rgblight_segment_t PROGMEM my_win_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_CYAN});
const rgblight_segment_t PROGMEM my_mac_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_CYAN});
const rgblight_segment_t PROGMEM my_win_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_mac_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_win_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_ORANGE});
const rgblight_segment_t PROGMEM my_mac_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_ORANGE});
const rgblight_segment_t PROGMEM my_win_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_SPRINGGREEN});
const rgblight_segment_t PROGMEM my_mac_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_SPRINGGREEN});
const rgblight_segment_t PROGMEM my_capsword_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});
const rgblight_segment_t PROGMEM my_layerOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_OFF});

const rgblight_segment_t * const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_win_layer0_layer,
    my_mac_layer0_layer,
    my_win_layer1_layer,
    my_mac_layer1_layer,
    my_win_layer2_layer,
    my_mac_layer2_layer,
    my_win_layer3_layer,
    my_mac_layer3_layer,
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

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
    record_current_rgblight();
};

layer_state_t default_layer_state_set_user(layer_state_t state) {
    record_current_rgblight();
    set_rgblight_on_default_layer();

    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == 0 || get_highest_layer(state) == 1) {
        record_current_rgblight();
    }

    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    rgblight_set_layer_state(7, layer_state_cmp(state, 7));

    return state;
};

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
