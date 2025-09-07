#include "my_eeconfig.c"
#include "my_tap_hold.c"
#include "my_rgb.c"

void eeconfig_init_user_datablock(void) {
#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s, def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif

    // init global memory
    MY_RGB_eeconfig_init_mem();

    // store global memory into eeprom user datablock
    MY_EECONFIG_eeconfig_init_user_datablock();

    // init rgblight
    MY_RGB_eeconfig_init_user_datablock();
}

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s, def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif

    // read eeprom user datablock into global memory
    MY_EECONFIG_keyboard_post_init_user();

    // init rgblight
    MY_RGB_keyboard_post_init_user();
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    layer_state_t ret_state = MY_RGB_default_layer_state_set_user(state);
    return ret_state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t ret_state = MY_RGB_layer_state_set_user(state);
    return ret_state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!MY_EECONFIG_process_record_user(keycode, record)) {
        return false;
    }
    else if (!MY_RGB_process_record_user(keycode, record)) {
        return false;
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    MY_RGB_post_process_record_user(keycode, record);
}

void caps_word_set_user(bool active) {
    MY_RGB_caps_word_set_user(active);
}
