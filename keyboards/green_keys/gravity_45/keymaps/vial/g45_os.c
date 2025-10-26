// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef OS_DETECTION_ENABLE
#include "g45_rgb.h"

void G45_OS_eeconfig_init_mem(void) {
    uint8_t* p = g45_user_config.os_default_layer;
    for (int i = 0; i < ARRAY_SIZE(g45_user_config.os_default_layer); i++, p++) {
        *p = 0;
    }
}

void G45_OS_eeconfig_migrate_mem(const g45_user_config_u* bk, const uint32_t prev_ver) {
    if (!bk || prev_ver < G45_BASE_FW_VER_OF_USER_CONFIG_V1) {
        return;
    }

    if (prev_ver < G45_BASE_FW_VER_OF_USER_CONFIG_V2) {
        G45_OS_eeconfig_init_mem();

        uint8_t* p = g45_user_config.os_default_layer;
        const uint8_t* bk_p = bk->v1.os_default_layer;
        for (int i = 0; i < ARRAY_SIZE(g45_user_config.os_default_layer); i++, p++, bk_p++) {
            *p = *bk_p;
        }
    }
}

bool G45_OS_process_detected_host_os_user(os_variant_t detected_os) {
    const g45_user_config_field_e cur_layer = G45_EECONFIG_get_current_layer_field(layer_state);
    const g45_user_config_field_e os_layer = G45_EECONFIG_get_os_default_layer_from_mem();

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s arg_os:%u, func_os:%u, df:%u, cur_layer:%u\n",
            __FUNCTION__, detected_os, detected_host_os(), os_layer, cur_layer);
#endif

    // if pdf may be set as non-zero, keep pdf. else, set os df.
    if (cur_layer == G45_FIELD_LAYER0 && os_layer != G45_FIELD_LAYER0) {
        set_single_default_layer(os_layer);
    }

    return true;
}

bool G45_OS_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case USR_OS_DEFAULT_LAYER:
            if (record->event.pressed) {
                rgblight_blink_layer_repeat(G45_BLINK_DF, 200, 3);

                const g45_user_config_field_e cur_layer = G45_EECONFIG_get_current_layer_field(layer_state);
                G45_EECONFIG_update_os_default_layer_to_eeprom(cur_layer);

                set_single_default_layer(cur_layer);
            }
            return false;
        default:
            return true;
    }
}

#endif
