// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "config.h"
#ifdef RGBLIGHT_LAYERS
#include "my_keycodes.h"
#include "my_eeconfig.h"
#include "my_rgb.h"

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

static const rgblight_segment_t PROGMEM my_reset_layer[] =       RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_WHITE});
static const rgblight_segment_t PROGMEM my_turn_on_layer[] =     RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GOLD});
static const rgblight_segment_t PROGMEM my_turn_off_layer[] =    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});
static const rgblight_segment_t PROGMEM my_set_default_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});

static const rgblight_segment_t * const PROGMEM my_blink_layers[] = RGBLIGHT_LAYERS_LIST(
    my_reset_layer,
    my_turn_on_layer,
    my_turn_off_layer,
    my_set_default_layer
);

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

static bool my_is_keyboard_post_init_user_called = false;
static bool my_is_rgblight_set_by_key = false;
static bool my_is_retain_val_toggled = false;

static void my_set_rgblight_on_layer_of(const my_user_config_field_e field) {
    if (is_caps_word_on()) {
        return;
    }

    const my_hsvm_t* p = MY_EECONFIG_get_hsvm_layer_from_mem(field);
    if (!p) {
        return;
    }

    uint8_t use_val = p->hsv.v;
    if (MY_EECONFIG_get_retain_val_from_mem() && (field != MY_FIELD_LAYER0)) {
        const my_hsvm_t* p_layer0 = MY_EECONFIG_get_hsvm_layer_from_mem(MY_FIELD_LAYER0);
        use_val = p_layer0->hsv.v;
    }

    MY_DUMP_EECONFIG();
#ifdef CONSOLE_ENABLE
    uprintf("%s, field:%u, hue:%u, sat:%u, val:%u\n", __FUNCTION__, field, p->hsv.h, p->hsv.s, use_val);
#endif

    rgblight_sethsv_noeeprom(p->hsv.h, p->hsv.s, use_val);
    rgblight_mode_noeeprom(p->mode);
}

static void my_record_rgblight_on_layer_of(const my_user_config_field_e field) {
    if (is_caps_word_on()) {
        return;
    }

    MY_DUMP_EECONFIG();
    my_hsvm_t cur_hsvm = {.hsv.h = rgblight_get_hue(), .hsv.s = rgblight_get_sat(),
                          .hsv.v = rgblight_get_val(), .mode = rgblight_get_mode()};

    const my_hsvm_t* p = MY_EECONFIG_get_hsvm_layer_from_mem(field);
    if (!p) {
        return;
    }

    if ((cur_hsvm.hsv.h == p->hsv.h) && (cur_hsvm.hsv.s == p->hsv.s) && (cur_hsvm.mode == p->mode)) {
        if (((field == MY_FIELD_LAYER0) && (cur_hsvm.hsv.v == p->hsv.v)) ||
            ((field != MY_FIELD_LAYER0) && ((cur_hsvm.hsv.v == p->hsv.v) || MY_EECONFIG_get_retain_val_from_mem()))) {
            return;
        }
    }

    MY_EECONFIG_update_hsvm_layer_to_eeprom(field, &cur_hsvm);

    MY_DUMP_EECONFIG();
}

// user button's func
static void my_update_hue_noeeprom(const bool is_increase) {
    if (is_increase) {
        rgblight_increase_hue_noeeprom();
    } else {
        rgblight_decrease_hue_noeeprom();
    }
}

static void my_update_sat_noeeprom(const bool is_increase) {
    if (is_increase) {
        rgblight_increase_sat_noeeprom();
    } else {
        rgblight_decrease_sat_noeeprom();
    }
}

static void my_update_val_noeeprom(const bool is_increase) {
    if (is_increase) {
        rgblight_increase_val_noeeprom();
    } else {
        rgblight_decrease_val_noeeprom();
    }
}

void MY_RGB_eeconfig_init_mem(void) {
    my_hsvm_t* p = my_user_config.hsvm_layer;
    for (int i = 0; i < ARRAY_SIZE(my_user_config.hsvm_layer); i++, p++) {
        const rgblight_segment_t* const cur_seg = my_rgb_layers[i];
        p->hsv.h = cur_seg->hue;
        p->hsv.s = cur_seg->sat;
        p->hsv.v = cur_seg->val;
        p->mode = RGBLIGHT_MODE_STATIC_LIGHT;
    }

    my_user_config.is_rgb_per_layer = true;
    my_user_config.to_retain_val = true;
}

void MY_RGB_eeconfig_init_user_datablock(void) {
    rgblight_enable_noeeprom();
    my_set_rgblight_on_layer_of(MY_EECONFIG_get_current_layer_field(layer_state));
}

void MY_RGB_keyboard_post_init_user(void) {
    rgblight_layers = my_blink_layers;

    rgblight_enable_noeeprom();
    my_set_rgblight_on_layer_of(MY_EECONFIG_get_current_layer_field(layer_state));

    my_is_keyboard_post_init_user_called = true;
};

layer_state_t MY_RGB_default_layer_state_set_user(layer_state_t state) {
    if (!MY_EECONFIG_get_rgb_per_layer_from_mem()) {
        my_set_rgblight_on_layer_of(MY_FIELD_LAYER0);
        my_is_rgblight_set_by_key = false;
        my_is_retain_val_toggled = false;
        return state;
    }

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s def:%u, layer_state:%u, state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state), get_highest_layer(state));
#endif

    // store rgblight automatically if it is changed on vial.
    if (my_is_keyboard_post_init_user_called) {
        if (get_highest_layer(state) == 0 && get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
            my_record_rgblight_on_layer_of(MY_FIELD_LAYER0);
        } else if (!my_is_rgblight_set_by_key && !my_is_retain_val_toggled) {
            my_record_rgblight_on_layer_of(MY_EECONFIG_get_current_layer_field(layer_state));
        }
    }

    my_set_rgblight_on_layer_of(get_highest_layer(state));
    my_is_rgblight_set_by_key = false;
    my_is_retain_val_toggled = false;

    return state;
}

layer_state_t MY_RGB_layer_state_set_user(layer_state_t state) {
    if (is_caps_word_on()) {
        return state;
    }

    if (!MY_EECONFIG_get_rgb_per_layer_from_mem()) {
        my_set_rgblight_on_layer_of(MY_FIELD_LAYER0);
        my_is_rgblight_set_by_key = false;
        my_is_retain_val_toggled = false;
        return state;
    }

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s def:%u, layer_state:%u, state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state), get_highest_layer(state));
#endif

    // store rgblight automatically if it is changed on vial.
    if (my_is_keyboard_post_init_user_called) {
        if (get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
            my_record_rgblight_on_layer_of(MY_FIELD_LAYER0);
        } else if (!my_is_rgblight_set_by_key && !my_is_retain_val_toggled) {
            my_record_rgblight_on_layer_of(MY_EECONFIG_get_current_layer_field(layer_state));
        }
    }

    my_set_rgblight_on_layer_of(MY_EECONFIG_get_current_layer_field(state));

    my_is_rgblight_set_by_key = false;
    my_is_retain_val_toggled = false;

    return state;
};

bool MY_RGB_process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mod_state = get_mods();
    switch (keycode) {
        case USR_RGB_RETAIN_VAL_TOG:
            if (record->event.pressed) {
                const bool cur_flag = MY_EECONFIG_get_retain_val_from_mem();
                rgblight_blink_layer_repeat(cur_flag ? MY_BLINK_OFF : MY_BLINK_ON, 300, 2);
                MY_EECONFIG_update_retain_val_to_eeprom(!cur_flag);
                if (MY_EECONFIG_get_current_layer_field(layer_state) != MY_FIELD_LAYER0) {
                    my_is_retain_val_toggled = true;
                }
            }
            return false;

        case USR_RGB_LAYER_TOG:
            if (record->event.pressed) {
                const bool cur_flag = MY_EECONFIG_get_rgb_per_layer_from_mem();
                rgblight_blink_layer_repeat(cur_flag ? MY_BLINK_OFF : MY_BLINK_ON, 300, 2);
                MY_EECONFIG_update_rgb_per_layer_to_eeprom(!cur_flag);
            }
            return false;

        case USR_RGB_LAYER_HUE_UP:
            if (record->event.pressed && MY_EECONFIG_get_rgb_per_layer_from_mem()) {
                my_update_hue_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_HUE_DOWN:
            if (record->event.pressed && MY_EECONFIG_get_rgb_per_layer_from_mem()) {
                my_update_hue_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_SAT_UP:
            if (record->event.pressed && MY_EECONFIG_get_rgb_per_layer_from_mem()) {
                my_update_sat_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_SAT_DOWN:
            if (record->event.pressed && MY_EECONFIG_get_rgb_per_layer_from_mem()) {
                my_update_sat_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_VAL_UP:
            if (record->event.pressed && MY_EECONFIG_get_rgb_per_layer_from_mem()) {
                my_update_val_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_VAL_DOWN:
            if (record->event.pressed && MY_EECONFIG_get_rgb_per_layer_from_mem()) {
                my_update_val_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_SAVE:
            if (record->event.pressed && MY_EECONFIG_get_rgb_per_layer_from_mem()) {
                rgblight_blink_layer_repeat(MY_BLINK_ON, 200, 3);
                my_record_rgblight_on_layer_of(MY_EECONFIG_get_current_layer_field(layer_state));
            }
            return false;

        default:
            return true;
    }
}

void MY_RGB_post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!my_is_keyboard_post_init_user_called) {
#ifdef CONSOLE_ENABLE
        uprintf("============================================================\n");
        uprintf("%s, def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif
        MY_EECONFIG_read_all_data_from_user_datablock();

        my_is_keyboard_post_init_user_called = true;
    }

    switch (keycode) {
        case UG_NEXT ... RGB_M_TW:
            my_record_rgblight_on_layer_of(MY_FIELD_LAYER0);
            my_is_rgblight_set_by_key = true;
            break;

        case USR_RGB_LAYER_HUE_UP:
        case USR_RGB_LAYER_HUE_DOWN:
        case USR_RGB_LAYER_SAT_UP:
        case USR_RGB_LAYER_SAT_DOWN:
        case USR_RGB_LAYER_VAL_UP:
        case USR_RGB_LAYER_VAL_DOWN:
            my_record_rgblight_on_layer_of(MY_EECONFIG_get_current_layer_field(layer_state));
            my_is_rgblight_set_by_key = true;
            break;

        default:
            break;
    }
}

void MY_RGB_caps_word_set_user(bool active) {
    if (!MY_EECONFIG_get_rgb_per_layer_from_mem()) {
        return;
    }

    if (active) {
        const rgblight_segment_t* const cur_seg = my_capsword_layer;
#ifdef CONSOLE_ENABLE
        uprintf("============================================================\n");
        uprintf("%s, active def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif

        rgblight_sethsv_noeeprom(cur_seg->hue, cur_seg->sat, MY_EECONFIG_get_hsvm_layer_from_mem(MY_FIELD_LAYER0)->hsv.v);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    } else {
#ifdef CONSOLE_ENABLE
        uprintf("%s, inactive def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif
        my_set_rgblight_on_layer_of(MY_EECONFIG_get_current_layer_field(layer_state));
    }
}

#endif
