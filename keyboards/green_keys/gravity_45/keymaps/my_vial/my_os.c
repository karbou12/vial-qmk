#ifdef OS_DETECTION_ENABLE
#include "my_rgb.h"

void MY_OS_eeconfig_init_mem(void) {
    uint8_t* p = my_user_config.os_default_layer;
    for (int i = 0; i < ARRAY_SIZE(my_user_config.os_default_layer); i++, p++) {
        *p = 0;
    }
}

bool MY_OS_process_detected_host_os_user(os_variant_t detected_os) {
#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s arg_os:%u, func_os:%u, df:%u\n",
            __FUNCTION__, detected_os, detected_host_os(), MY_EECONFIG_get_os_default_layer_from_mem());
    uprintf("%s, eeconfig:%s, %u, vial:%lu\n", __FUNCTION__, eeconfig_is_user_datablock_valid() ? "valid" : "invalid", EECONFIG_USER_DATA_VERSION, VIAL_PROTOCOL_VERSION);
#endif

    set_single_persistent_default_layer(MY_EECONFIG_get_os_default_layer_from_mem());

    return true;
}

bool MY_OS_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_OS_DEFAULT_LAYER:
            if (record->event.pressed) {
                rgblight_blink_layer_repeat(MY_BLINK_DF, 200, 3);

                const my_user_config_field_e cur_layer = MY_EECONFIG_get_current_layer_field(layer_state);
                MY_EECONFIG_update_os_default_layer_to_eeprom(cur_layer);

                set_single_persistent_default_layer(cur_layer);
            }
            return false;
        default:
            return true;
    }
}

#endif
