// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "g45_eeconfig.h"
#include "g45_keycodes.h"
#include "g45_rgb.h"

g45_user_config_t g45_user_config = {0};

#ifdef CONSOLE_ENABLE
void g45_dump_eeconfig(const char* const func) {
    g45_hsvm_t* p = g45_user_config.hsvm_layer;
    uprintf("------------------------------------------------------------\n");
    uprintf("%s DUMP EEPROM USER DATA. size:%u, defined size:%u\n", func, sizeof(g45_user_config), EECONFIG_USER_DATA_SIZE);
    for (int i = 0; i < ARRAY_SIZE(g45_user_config.hsvm_layer); i++, p++) {
        uprintf("id:%u, hue:%u, sat:%u, val:%u, mode:%u\n", i, p->hsv.h, p->hsv.s, p->hsv.v, p->mode);
    }
    uprintf("is_rgb_per_layer:%s\n", g45_user_config.is_rgb_per_layer ? "true" : "false");
    uprintf("to_retain_val:%s\n", g45_user_config.to_retain_val ? "true" : "false");
    uprintf("is_auto_save_rgb:%s\n", g45_user_config.is_auto_save_rgb ? "true" : "false");

    g45_user_config_field_e* p_os = g45_user_config.os_default_layer;
    for (int i = 0; i < ARRAY_SIZE(g45_user_config.os_default_layer); i++, p_os++) {
        uprintf("id:%u, default layer:%u\n", i, *p_os);
    }
}
#endif

uint32_t g45_get_offset(const g45_user_config_field_e field) {
    switch (field) {
        case G45_FIELD_LAYER0 ... G45_FIELD_LAYER8:
            return sizeof(g45_hsvm_t) * field;
        case G45_FIELD_LAYER_TOGGLE ... G45_FIELD_RETAIN_VAL_TOGGLE:
            return sizeof(g45_hsvm_t) * ARRAY_SIZE(g45_user_config.hsvm_layer) +
                   sizeof(bool) * (field - G45_FIELD_LAYER8 - 1);
        case G45_FIELD_OS_UNSURE ... G45_FIELD_OS_IOS:
            return sizeof(g45_hsvm_t) * ARRAY_SIZE(g45_user_config.hsvm_layer) +
                   sizeof(bool) * (G45_FIELD_OS_UNSURE - G45_FIELD_LAYER8 - 1) +
                   sizeof(g45_user_config_field_e) * (field - G45_FIELD_OS_UNSURE);
        default :
            return 0;
    }
}

g45_user_config_field_e G45_EECONFIG_get_current_layer_field(const layer_state_t state) {
    const uint8_t layer = get_highest_layer(state);
    return (layer == G45_FIELD_LAYER0) ? get_highest_layer(default_layer_state) : layer;
}

void G45_EECONFIG_read_all_data_from_user_datablock(void) {
    eeconfig_read_user_datablock(&g45_user_config, 0, sizeof(g45_user_config));
}
void G45_EECONFIG_update_all_data_to_user_datablock(void) {
    eeconfig_update_user_datablock(&g45_user_config, 0, sizeof(g45_user_config));
}

const g45_hsvm_t* G45_EECONFIG_get_hsvm_layer_from_mem(const g45_user_config_field_e field) {
    if (sizeof(g45_user_config.hsvm_layer) <= field) {
        return NULL;
    }
    return &g45_user_config.hsvm_layer[field];
}

void G45_EECONFIG_update_hsvm_layer_to_eeprom(const g45_user_config_field_e field, const g45_hsvm_t* hsvm_layer) {
    if (sizeof(g45_user_config.hsvm_layer) <= field) {
        return;
    }
    g45_user_config.hsvm_layer[field] = *hsvm_layer;
    eeconfig_update_user_datablock(hsvm_layer, g45_get_offset(field), sizeof(g45_hsvm_t));
}

bool G45_EECONFIG_get_rgb_per_layer_from_mem(void) {
    return g45_user_config.is_rgb_per_layer;
}

void G45_EECONFIG_update_rgb_per_layer_to_eeprom(const bool is_rgb_per_layer) {
    g45_user_config.is_rgb_per_layer = is_rgb_per_layer;
    eeconfig_update_user_datablock(&is_rgb_per_layer, g45_get_offset(G45_FIELD_LAYER_TOGGLE), sizeof(is_rgb_per_layer));

bool G45_EECONFIG_get_auto_save_rgb_from_mem(void) {
    return g45_user_config.is_auto_save_rgb;
}

void G45_EECONFIG_update_auto_save_rgb_to_eeprom(const bool is_auto_save_rgb) {
    g45_user_config.is_auto_save_rgb = is_auto_save_rgb;
    eeconfig_update_user_datablock(&is_auto_save_rgb, g45_get_offset(G45_FIELD_AUTO_SAVE_TOGGLE), sizeof(uint8_t));
}

bool G45_EECONFIG_get_retain_val_from_mem(void) {
    return g45_user_config.to_retain_val;
}

void G45_EECONFIG_update_retain_val_to_eeprom(const bool to_retain_val) {
    g45_user_config.to_retain_val = to_retain_val;
    eeconfig_update_user_datablock(&to_retain_val, g45_get_offset(G45_FIELD_RETAIN_VAL_TOGGLE), sizeof(to_retain_val));
}

g45_user_config_field_e G45_EECONFIG_get_os_default_layer_from_mem() {
    const os_variant_t os = detected_host_os();
    switch (os) {
        case OS_UNSURE ... OS_IOS:
            return g45_user_config.os_default_layer[os];
        default:
            return G45_FIELD_LAYER0;
    }
}

void G45_EECONFIG_update_os_default_layer_to_eeprom(const g45_user_config_field_e field) {
    const os_variant_t os = detected_host_os();
    if ((sizeof(g45_user_config.os_default_layer) <= os) || (sizeof(g45_user_config.hsvm_layer) <= field)) {
        return;
    }

    g45_user_config.os_default_layer[os] = field;
    const g45_user_config_field_e os_field = G45_FIELD_OS_UNSURE + os;
    eeconfig_update_user_datablock(&field, g45_get_offset(os_field), sizeof(field));
}

void G45_EECONFIG_eeconfig_init_user_datablock(void) {
    G45_EECONFIG_update_all_data_to_user_datablock();
}

void G45_EECONFIG_keyboard_post_init_user(void) {
    G45_EECONFIG_read_all_data_from_user_datablock();
}

bool G45_EECONFIG_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case USR_RESET:
            if (record->event.pressed) {
                rgblight_blink_layer_repeat(G45_BLINK_RESET, 300, 3);
                eeconfig_init_user_datablock();
                G45_EECONFIG_update_all_data_to_user_datablock();

                set_single_default_layer(G45_FIELD_LAYER0);
            }
            return false;
        default:
            return true;
    }
}
