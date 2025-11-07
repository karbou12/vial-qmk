// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "config.h"
#ifdef RGBLIGHT_LAYERS
#include "g45_keycodes.h"
#include "g45_eeconfig.h"
#include "g45_rgb.h"

static const rgblight_segment_t PROGMEM g45_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_TURQUOISE});
static const rgblight_segment_t PROGMEM g45_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_CYAN});
static const rgblight_segment_t PROGMEM g45_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_MAGENTA});
static const rgblight_segment_t PROGMEM g45_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});
static const rgblight_segment_t PROGMEM g45_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW});
static const rgblight_segment_t PROGMEM g45_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});
static const rgblight_segment_t PROGMEM g45_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_AZURE});
static const rgblight_segment_t PROGMEM g45_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_SPRINGGREEN});
static const rgblight_segment_t PROGMEM g45_layer8_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_ORANGE});
static const rgblight_segment_t PROGMEM g45_capsword_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});
static const rgblight_segment_t PROGMEM g45_layerOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_OFF});

static const rgblight_segment_t PROGMEM g45_reset_layer[] =       RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_WHITE});
static const rgblight_segment_t PROGMEM g45_turn_on_layer[] =     RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GOLD});
static const rgblight_segment_t PROGMEM g45_turn_off_layer[] =    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});
static const rgblight_segment_t PROGMEM g45_set_default_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});

static const rgblight_segment_t * const PROGMEM g45_blink_layers[] = RGBLIGHT_LAYERS_LIST(
    g45_reset_layer,
    g45_turn_on_layer,
    g45_turn_off_layer,
    g45_set_default_layer
);

const rgblight_segment_t * const PROGMEM g45_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    g45_layer0_layer,
    g45_layer1_layer,
    g45_layer2_layer,
    g45_layer3_layer,
    g45_layer4_layer,
    g45_layer5_layer,
    g45_layer6_layer,
    g45_layer7_layer,
    g45_layer8_layer,
    g45_capsword_layer
);

static bool g45_is_keyboard_post_init_user_called = false;
static bool g45_is_key_pressed_to_skip_rec_rgb = false;

static void g45_set_rgblight_on_layer_of(const g45_user_config_field_e field) {
    if (!g45_is_keyboard_post_init_user_called) {
        return;
    }

    g45_is_key_pressed_to_skip_rec_rgb = false;

    if (is_caps_word_on()) {
        return;
    }

    const g45_hsvm_t* p = G45_EECONFIG_get_hsvm_layer_from_mem(field);
    if (!p) {
        return;
    }

    uint8_t use_val = p->hsv.v;
    if (G45_EECONFIG_get_retain_val_from_mem() && (field != G45_FIELD_LAYER0)) {
        const g45_hsvm_t* p_layer0 = G45_EECONFIG_get_hsvm_layer_from_mem(G45_FIELD_LAYER0);
        use_val = p_layer0->hsv.v;
    }

    G45_DUMP_EECONFIG();
#ifdef CONSOLE_ENABLE
    uprintf("%s, field:%u, hue:%u, sat:%u, val:%u\n", __FUNCTION__, field, p->hsv.h, p->hsv.s, use_val);
#endif

    rgblight_sethsv_noeeprom(p->hsv.h, p->hsv.s, use_val);
    rgblight_mode_noeeprom(p->mode);
}

static void g45_record_rgblight_on_layer_of(const g45_user_config_field_e field) {
    if (!g45_is_keyboard_post_init_user_called) {
        return;
    }

    if (is_caps_word_on()) {
        return;
    }

    G45_DUMP_EECONFIG();
    g45_hsvm_t cur_hsvm = {.hsv.h = rgblight_get_hue(), .hsv.s = rgblight_get_sat(),
                          .hsv.v = rgblight_get_val(), .mode = rgblight_get_mode()};

    const g45_hsvm_t* p = G45_EECONFIG_get_hsvm_layer_from_mem(field);
    if (!p) {
        return;
    }

    if ((cur_hsvm.hsv.h == p->hsv.h) && (cur_hsvm.hsv.s == p->hsv.s) && (cur_hsvm.mode == p->mode)) {
        if (((field == G45_FIELD_LAYER0) && (cur_hsvm.hsv.v == p->hsv.v)) ||
            ((field != G45_FIELD_LAYER0) && ((cur_hsvm.hsv.v == p->hsv.v) || G45_EECONFIG_get_retain_val_from_mem()))) {
            return;
        }
    }

    G45_EECONFIG_update_hsvm_layer_to_eeprom(field, &cur_hsvm);

    G45_DUMP_EECONFIG();
}

// user button's func
static void g45_update_hue_noeeprom(const bool is_increase) {
    if (is_increase) {
        rgblight_increase_hue_noeeprom();
    } else {
        rgblight_decrease_hue_noeeprom();
    }
}

static void g45_update_sat_noeeprom(const bool is_increase) {
    if (is_increase) {
        rgblight_increase_sat_noeeprom();
    } else {
        rgblight_decrease_sat_noeeprom();
    }
}

static void g45_update_val_noeeprom(const bool is_increase) {
    if (is_increase) {
        rgblight_increase_val_noeeprom();
    } else {
        rgblight_decrease_val_noeeprom();
    }
}

static bool g45_is_rgblight_per_layer_enabled(keyrecord_t *record) {
    if (record) {
        return (record->event.pressed && rgblight_is_enabled() && G45_EECONFIG_get_rgb_per_layer_from_mem());
    } else {
        return (rgblight_is_enabled() && G45_EECONFIG_get_rgb_per_layer_from_mem());
    }
}

void G45_RGB_eeconfig_init_mem(void) {
    g45_hsvm_t* p = g45_user_config.hsvm_layer;
    for (uint8_t i = 0; i < ARRAY_SIZE(g45_user_config.hsvm_layer); i++, p++) {
        const rgblight_segment_t* const cur_seg = g45_rgb_layers[i];
        p->hsv.h = cur_seg->hue;
        p->hsv.s = cur_seg->sat;
        p->hsv.v = cur_seg->val;
        p->mode = RGBLIGHT_MODE_STATIC_LIGHT;
    }

    g45_user_config.flag_raw = 0u;
    g45_user_config.flags.is_rgb_per_layer = true;
    g45_user_config.flags.is_auto_save_rgb = true;
    g45_user_config.flags.to_retain_val = true;
}

void G45_RGB_eeconfig_migrate_mem(const g45_user_config_u* bk, const uint32_t prev_ver) {
    if (!bk || prev_ver < G45_BASE_FW_VER_OF_USER_CONFIG_V1) {
        return;
    }

    G45_RGB_eeconfig_init_mem();
    g45_hsvm_t* p = g45_user_config.hsvm_layer;

    const g45_hsvm_t* bk_p = (prev_ver < G45_BASE_FW_VER_OF_USER_CONFIG_V2) ? bk->v1.hsvm_layer
                                                                          : bk->v2.hsvm_layer;

    for (uint8_t i = 0; i < ARRAY_SIZE(g45_user_config.hsvm_layer); i++, p++, bk_p++) {
        p->hsv.h = bk_p->hsv.h;
        p->hsv.s = bk_p->hsv.s;
        p->hsv.v = bk_p->hsv.v;
        p->mode = bk_p->mode;
    }

    if (prev_ver < G45_BASE_FW_VER_OF_USER_CONFIG_V2) {
        g45_user_config.flags.is_rgb_per_layer = bk->v1.is_rgb_per_layer;
        g45_user_config.flags.to_retain_val = bk->v1.to_retain_val;
    } else {
        g45_user_config.flags.is_rgb_per_layer = bk->v2.flags.is_rgb_per_layer;
        g45_user_config.flags.is_auto_save_rgb = bk->v2.flags.is_auto_save_rgb;
        g45_user_config.flags.to_retain_val = bk->v2.flags.to_retain_val;
    }
}

void G45_RGB_keyboard_post_init_user(void) {
    g45_is_keyboard_post_init_user_called = true;
    rgblight_layers = g45_blink_layers;

    rgblight_enable_noeeprom();
    g45_set_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(layer_state));
};

layer_state_t G45_RGB_default_layer_state_set_user(layer_state_t state) {
    if (!rgblight_is_enabled()) {
        return state;
    }

    if (!G45_EECONFIG_get_rgb_per_layer_from_mem()) {
        g45_set_rgblight_on_layer_of(G45_FIELD_LAYER0);
        return state;
    }

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s def:%u, layer_state:%u, state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state), get_highest_layer(state));
#endif

    // store rgblight automatically if it is changed on vial.
    if (get_highest_layer(state) == 0 && get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
        g45_record_rgblight_on_layer_of(G45_FIELD_LAYER0);
    } else if (G45_EECONFIG_get_auto_save_rgb_from_mem() && !g45_is_key_pressed_to_skip_rec_rgb) {
        g45_record_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(layer_state));
    }

    g45_set_rgblight_on_layer_of(get_highest_layer(state));

    return state;
}

layer_state_t G45_RGB_layer_state_set_user(layer_state_t state) {
    if (!rgblight_is_enabled()) {
        return state;
    }

    if (is_caps_word_on()) {
        return state;
    }

    if (!G45_EECONFIG_get_rgb_per_layer_from_mem()) {
        g45_set_rgblight_on_layer_of(G45_FIELD_LAYER0);
        return state;
    }

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s def:%u, layer_state:%u, state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state), get_highest_layer(state));
#endif

    // store rgblight automatically if it is changed on vial.
    if (get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
        g45_record_rgblight_on_layer_of(G45_FIELD_LAYER0);
    } else if (G45_EECONFIG_get_auto_save_rgb_from_mem() &&!g45_is_key_pressed_to_skip_rec_rgb) {
        g45_record_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(layer_state));
    }

    g45_set_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(state));

    return state;
};

bool G45_RGB_process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mod_state = get_mods();
    switch (keycode) {
        case USR_RGB_RETAIN_VAL_TOG:
            if (g45_is_rgblight_per_layer_enabled(record)) {
                const bool cur_flag = G45_EECONFIG_get_retain_val_from_mem();
                rgblight_blink_layer_repeat(cur_flag ? G45_BLINK_OFF : G45_BLINK_ON, 300, 2);
                G45_EECONFIG_update_retain_val_to_eeprom(!cur_flag);
                if (G45_EECONFIG_get_current_layer_field(layer_state) != G45_FIELD_LAYER0) {
                    g45_is_key_pressed_to_skip_rec_rgb = true;
                }
            }
            return false;

        case USR_RGB_LAYER_TOG:
            if (rgblight_is_enabled() && record->event.pressed) {
                const bool cur_flag = G45_EECONFIG_get_rgb_per_layer_from_mem();
                rgblight_blink_layer_repeat(cur_flag ? G45_BLINK_OFF : G45_BLINK_ON, 300, 2);
                G45_EECONFIG_update_rgb_per_layer_to_eeprom(!cur_flag);
            }
            return false;

        case USR_RGB_LAYER_HUE_UP:
            if (g45_is_rgblight_per_layer_enabled(record)) {
                g45_update_hue_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_HUE_DOWN:
            if (g45_is_rgblight_per_layer_enabled(record)) {
                g45_update_hue_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_SAT_UP:
            if (g45_is_rgblight_per_layer_enabled(record)) {
                g45_update_sat_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_SAT_DOWN:
            if (g45_is_rgblight_per_layer_enabled(record)) {
                g45_update_sat_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_VAL_UP:
            if (g45_is_rgblight_per_layer_enabled(record)) {
                g45_update_val_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_VAL_DOWN:
            if (g45_is_rgblight_per_layer_enabled(record)) {
                g45_update_val_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_AUTO_SAVE_TOG:
            if (g45_is_rgblight_per_layer_enabled(record)) {
                const bool cur_flag = G45_EECONFIG_get_auto_save_rgb_from_mem();
                rgblight_blink_layer_repeat(cur_flag ? G45_BLINK_OFF : G45_BLINK_ON, 300, 2);
                G45_EECONFIG_update_auto_save_rgb_to_eeprom(!cur_flag);
            }
            return false;

        default:
            return true;
    }
}

void G45_RGB_post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UG_NEXT ... RGB_M_TW:
            if (rgblight_is_enabled()) {
                g45_record_rgblight_on_layer_of(G45_FIELD_LAYER0);
                g45_is_key_pressed_to_skip_rec_rgb = true;
            }
            break;

        case USR_RGB_LAYER_HUE_UP:
        case USR_RGB_LAYER_HUE_DOWN:
        case USR_RGB_LAYER_SAT_UP:
        case USR_RGB_LAYER_SAT_DOWN:
        case USR_RGB_LAYER_VAL_UP:
        case USR_RGB_LAYER_VAL_DOWN:
            if (g45_is_rgblight_per_layer_enabled(NULL)) {
                g45_record_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(layer_state));
                g45_is_key_pressed_to_skip_rec_rgb = true;
            }
            break;

        default:
            break;
    }
}

void G45_RGB_caps_word_set_user(bool active) {
    if (!G45_EECONFIG_get_rgb_per_layer_from_mem()) {
        return;
    }

    if (active) {
        const rgblight_segment_t* const cur_seg = g45_capsword_layer;
#ifdef CONSOLE_ENABLE
        uprintf("============================================================\n");
        uprintf("%s, active def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif

        rgblight_sethsv_noeeprom(cur_seg->hue, cur_seg->sat, G45_EECONFIG_get_hsvm_layer_from_mem(G45_FIELD_LAYER0)->hsv.v);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    } else {
#ifdef CONSOLE_ENABLE
        uprintf("%s, inactive def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif
        g45_set_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(layer_state));
    }
}

#endif
