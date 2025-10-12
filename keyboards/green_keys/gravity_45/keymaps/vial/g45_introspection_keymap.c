// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "g45_eeconfig.c"
#include "g45_rgb.c"
#include "g45_os.c"

void eeconfig_init_user_datablock(void) {
#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s, def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif

    // init global memory
    G45_RGB_eeconfig_init_mem();
    G45_OS_eeconfig_init_mem();

    G45_DUMP_EECONFIG();

    // store global memory into eeprom user datablock
    G45_EECONFIG_eeconfig_init_user_datablock();

    // init rgblight
    G45_RGB_eeconfig_init_user_datablock();
    G45_DUMP_EECONFIG();
}

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s, def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
    uprintf("%s, eeconfig:%s, %u, vial:%lu\n", __FUNCTION__, eeconfig_is_user_datablock_valid() ? "valid" : "invalid", EECONFIG_USER_DATA_VERSION, VIAL_PROTOCOL_VERSION);
#endif

    G45_DUMP_EECONFIG();

    if (!eeconfig_is_user_datablock_valid()) {
        eeconfig_init_user_datablock();
    }

    // read eeprom user datablock into global memory
    G45_EECONFIG_keyboard_post_init_user();

    G45_DUMP_EECONFIG();

    // init rgblight
    G45_RGB_keyboard_post_init_user();

    G45_DUMP_EECONFIG();
}

bool process_detected_host_os_user(os_variant_t detected_os) {
    if (!G45_OS_process_detected_host_os_user(detected_os)) {
        return false;
    }
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    layer_state_t ret_state = G45_RGB_default_layer_state_set_user(state);
    return ret_state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t ret_state = G45_RGB_layer_state_set_user(state);
    return ret_state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!G45_EECONFIG_process_record_user(keycode, record)) {
        return false;
    } else if (!G45_RGB_process_record_user(keycode, record)) {
        return false;
    } else if (!G45_OS_process_record_user(keycode, record)) {
        return false;
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    G45_RGB_post_process_record_user(keycode, record);
}

void caps_word_set_user(bool active) {
    G45_RGB_caps_word_set_user(active);
}
