// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "config.h"
#ifdef RGBLIGHT_LAYERS
#include "g45_keycodes.h"
#include "g45_eeconfig.h"
#include "g45_rgb.h"

const rgblight_segment_t PROGMEM g45_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_TURQUOISE});
const rgblight_segment_t PROGMEM g45_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_CYAN});
const rgblight_segment_t PROGMEM g45_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_MAGENTA});
const rgblight_segment_t PROGMEM g45_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM g45_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW});
const rgblight_segment_t PROGMEM g45_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM g45_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_AZURE});
const rgblight_segment_t PROGMEM g45_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_SPRINGGREEN});
const rgblight_segment_t PROGMEM g45_layer8_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_ORANGE});
const rgblight_segment_t PROGMEM g45_capsword_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});
const rgblight_segment_t PROGMEM g45_layerOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_OFF});

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

static void g45_set_rgblight_on_layer_of(const g45_user_config_field_e field) {
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

    if ((cur_hsvm.hsv.h == p->hsv.h) && (cur_hsvm.hsv.s == p->hsv.s) &&
        (cur_hsvm.hsv.v == p->hsv.v) && (cur_hsvm.mode == p->mode)) {
        return;
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

void G45_RGB_eeconfig_init_mem(void) {
    g45_hsvm_t* p = g45_user_config.hsvm_layer;
    for (int i = 0; i < ARRAY_SIZE(g45_user_config.hsvm_layer); i++, p++) {
        const rgblight_segment_t* const cur_seg = g45_rgb_layers[i];
        p->hsv.h = cur_seg->hue;
        p->hsv.s = cur_seg->sat;
        p->hsv.v = cur_seg->val;
        p->mode = RGBLIGHT_MODE_STATIC_LIGHT;
    }

    g45_user_config.is_rgb_per_layer = true;
    g45_user_config.to_retain_val = true;
}

void G45_RGB_eeconfig_init_user_datablock(void) {
    rgblight_enable_noeeprom();
    g45_set_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(layer_state));
}

void G45_RGB_keyboard_post_init_user(void) {
    rgblight_layers = g45_blink_layers;

    rgblight_enable_noeeprom();
    g45_set_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(layer_state));

    g45_is_keyboard_post_init_user_called = true;
};

layer_state_t G45_RGB_default_layer_state_set_user(layer_state_t state) {
    if (!G45_EECONFIG_get_rgb_per_layer_from_mem()) {
        g45_set_rgblight_on_layer_of(G45_FIELD_LAYER0);
        return state;
    }

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s def:%u, layer_state:%u, state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state), get_highest_layer(state));
#endif

    // store rgblight of layer 0 automatically if it is changed on vial.
    if (g45_is_keyboard_post_init_user_called) {
        if (get_highest_layer(state) == 0 && get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
            g45_record_rgblight_on_layer_of(G45_FIELD_LAYER0);
        }
    }

    g45_set_rgblight_on_layer_of(get_highest_layer(state));

    return state;
}

layer_state_t G45_RGB_layer_state_set_user(layer_state_t state) {
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

    // store rgblight of layer 0 automatically if it is changed on vial.
    if (g45_is_keyboard_post_init_user_called) {
        if (get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
            g45_record_rgblight_on_layer_of(G45_FIELD_LAYER0);
        }
    }

    g45_set_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(state));

    return state;
};

bool G45_RGB_process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mod_state = get_mods();
    switch (keycode) {
        case USR_RGB_RETAIN_VAL_TOG:
            if (record->event.pressed) {
                const bool cur_flag = G45_EECONFIG_get_retain_val_from_mem();
                rgblight_blink_layer_repeat(cur_flag ? G45_BLINK_OFF : G45_BLINK_ON, 300, 2);
                G45_EECONFIG_update_retain_val_to_eeprom(!cur_flag);
            }
            return false;

        case USR_RGB_LAYER_TOG:
            if (record->event.pressed) {
                const bool cur_flag = G45_EECONFIG_get_rgb_per_layer_from_mem();
                rgblight_blink_layer_repeat(cur_flag ? G45_BLINK_OFF : G45_BLINK_ON, 300, 2);
                G45_EECONFIG_update_rgb_per_layer_to_eeprom(!cur_flag);
            }
            return false;

        case USR_RGB_LAYER_HUE_UP:
            if (record->event.pressed && G45_EECONFIG_get_rgb_per_layer_from_mem()) {
                g45_update_hue_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_HUE_DOWN:
            if (record->event.pressed && G45_EECONFIG_get_rgb_per_layer_from_mem()) {
                g45_update_hue_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_SAT_UP:
            if (record->event.pressed && G45_EECONFIG_get_rgb_per_layer_from_mem()) {
                g45_update_sat_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_SAT_DOWN:
            if (record->event.pressed && G45_EECONFIG_get_rgb_per_layer_from_mem()) {
                g45_update_sat_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_VAL_UP:
            if (record->event.pressed && G45_EECONFIG_get_rgb_per_layer_from_mem()) {
                g45_update_val_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_VAL_DOWN:
            if (record->event.pressed && G45_EECONFIG_get_rgb_per_layer_from_mem()) {
                g45_update_val_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_SAVE:
            if (record->event.pressed && G45_EECONFIG_get_rgb_per_layer_from_mem()) {
                rgblight_blink_layer_repeat(G45_BLINK_ON, 200, 3);
                g45_record_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(layer_state));
            }
            return false;

        default:
            return true;
    }
}

void G45_RGB_post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!g45_is_keyboard_post_init_user_called) {
#ifdef CONSOLE_ENABLE
        uprintf("============================================================\n");
        uprintf("%s, def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif
        G45_EECONFIG_read_all_data_from_user_datablock();

        g45_is_keyboard_post_init_user_called = true;
    }

    switch (keycode) {
        case UG_NEXT:
        case UG_PREV:
        case UG_HUED:
        case UG_HUEU:
        case UG_SATD:
        case UG_SATU:
        case UG_VALD:
        case UG_VALU:
            g45_record_rgblight_on_layer_of(G45_FIELD_LAYER0);
            break;

        case USR_RGB_LAYER_HUE_UP:
        case USR_RGB_LAYER_HUE_DOWN:
        case USR_RGB_LAYER_SAT_UP:
        case USR_RGB_LAYER_SAT_DOWN:
        case USR_RGB_LAYER_VAL_UP:
        case USR_RGB_LAYER_VAL_DOWN:
            g45_record_rgblight_on_layer_of(G45_EECONFIG_get_current_layer_field(layer_state));
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
