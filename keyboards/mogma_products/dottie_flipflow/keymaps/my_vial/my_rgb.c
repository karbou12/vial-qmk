#ifdef RGBLIGHT_LAYERS

typedef union {
    uint32_t raw;
    struct {
        hsv_t hsv;
        uint8_t mode;
    };
} user_config_t;

static user_config_t user_config;

static hsv_t my_hsv;
static uint8_t my_mode = 0;
static uint8_t current_layer = 0;

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

static void record_current_rgblight_on_eeconfig(void) {
    user_config.hsv.h = rgblight_get_hue();
    user_config.hsv.s = rgblight_get_sat();
    user_config.hsv.v = rgblight_get_val();
    user_config.mode = rgblight_get_mode();
    eeconfig_update_user(user_config.raw);
}

static void record_rgblight_edited_by_vial(void) {
    if (current_layer == 0 && !is_caps_word_on()) {
        if (get_highest_layer(default_layer_state) == 0) {
            record_current_rgblight();
        } else {
            record_current_rgblight_on_eeconfig();
        }
    }
}

static void set_rgblight_on_layer_of(uint8_t layer) {
    if (layer == 0) {
        rgblight_sethsv_noeeprom(my_hsv.h, my_hsv.s, my_hsv.v);
        rgblight_mode_noeeprom(my_mode);
    } else if (layer == 1) {
        rgblight_sethsv_noeeprom(user_config.hsv.h, user_config.hsv.s, user_config.hsv.v);
        rgblight_mode_noeeprom(user_config.mode);
    } else if (layer < ARRAY_SIZE(my_rgb_layers)) {
        const rgblight_segment_t* const cur_seg = my_rgb_layers[layer];
        rgblight_sethsv_noeeprom(cur_seg->hue, cur_seg->sat, my_hsv.v);
        rgblight_mode_noeeprom(1);
    }
}

static void set_rgblight_on_current_layer(void) {
    set_rgblight_on_layer_of((current_layer == 0) ? get_highest_layer(default_layer_state) : current_layer);
}

void eeconfig_init_user(void) {
    const rgblight_segment_t* const df0_seg = my_rgb_layers[0];
    my_hsv.h = df0_seg->hue;
    my_hsv.s = df0_seg->sat;
    my_hsv.v = df0_seg->val;
    my_mode = 1;

    user_config.raw = 0;

    const rgblight_segment_t* const df1_seg = my_rgb_layers[1];
    user_config.hsv.h = df1_seg->hue;
    user_config.hsv.s = df1_seg->sat;
    user_config.hsv.v = df1_seg->val;
    user_config.mode = 1;
    eeconfig_update_user(user_config.raw);

    rgblight_enable_noeeprom();
    set_rgblight_on_current_layer();
}

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;

    user_config.raw = eeconfig_read_user();
};

layer_state_t default_layer_state_set_user(layer_state_t state) {
    record_rgblight_edited_by_vial();
    current_layer = get_highest_layer(state);
    set_rgblight_on_layer_of(current_layer);

    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    record_rgblight_edited_by_vial();
    current_layer = get_highest_layer(state);

    for (int i = 2; i < 8; i++) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }

    return state;
};

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

void caps_word_set_user(bool active) {
    if (active) {
        const rgblight_segment_t* const cur_seg = my_capsword_layer;
        rgblight_sethsv_noeeprom(cur_seg->hue, cur_seg->sat, my_hsv.v);
        rgblight_mode_noeeprom(1);
    } else {
        set_rgblight_on_current_layer();
    }
}

#endif
