// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef OS_DETECTION_ENABLE
#include "my_rgb.h"

void MY_OS_eeconfig_init_mem(void) {
    uint8_t* p = my_user_config.os_default_layer;
    for (int i = 0; i < ARRAY_SIZE(my_user_config.os_default_layer); i++, p++) {
        *p = 0;
    }
}

bool MY_OS_process_detected_host_os_user(os_variant_t detected_os) {
    const my_user_config_field_e cur_layer = MY_EECONFIG_get_current_layer_field(layer_state);
    const my_user_config_field_e os_layer = MY_EECONFIG_get_os_default_layer_from_mem();

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s arg_os:%u, func_os:%u, df:%u, cur_layer:%u\n",
            __FUNCTION__, detected_os, detected_host_os(), os_layer, cur_layer);
    uprintf("%s, eeconfig:%s, %u, vial:%lu\n", __FUNCTION__, eeconfig_is_user_datablock_valid() ? "valid" : "invalid", EECONFIG_USER_DATA_VERSION, VIAL_PROTOCOL_VERSION);
#endif

    // if pdf may be set as non-zero, keep pdf. else, set os df.
    if (cur_layer == MY_FIELD_LAYER0 && os_layer != MY_FIELD_LAYER0) {
        set_single_default_layer(os_layer);
    }

    return true;
}

bool MY_OS_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case USR_OS_DEFAULT_LAYER:
            if (record->event.pressed) {
                rgblight_blink_layer_repeat(MY_BLINK_DF, 200, 3);

                const my_user_config_field_e cur_layer = MY_EECONFIG_get_current_layer_field(layer_state);
                MY_EECONFIG_update_os_default_layer_to_eeprom(cur_layer);

                set_single_default_layer(cur_layer);
            }
            return false;
        default:
            return true;
    }
}

#endif
