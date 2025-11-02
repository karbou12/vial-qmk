#include "my_eeconfig.h"
#include "my_keycodes.h"
#include "my_rgb.h"

my_user_config_t my_user_config = {0};

#ifdef CONSOLE_ENABLE
void my_dump_eeconfig(const char* const func) {
    my_hsvm_t* p = my_user_config.hsvm_layer;
    uprintf("------------------------------------------------------------\n");
    uprintf("%s DUMP EEPROM USER DATA. size:%u, defined size:%u\n", func, sizeof(my_user_config), EECONFIG_USER_DATA_SIZE);
    for (int i = 0; i < ARRAY_SIZE(my_user_config.hsvm_layer); i++, p++) {
        uprintf("id:%u, hue:%u, sat:%u, val:%u, mode:%u\n", i, p->hsv.h, p->hsv.s, p->hsv.v, p->mode);
    }
    uprintf("is_rgb_per_layer:%s\n", my_user_config.is_rgb_per_layer ? "true" : "false");
    uprintf("to_use_same_val:%s\n", my_user_config.to_use_same_val ? "true" : "false");

    my_user_config_field_e* p_os = my_user_config.os_default_layer;
    for (int i = 0; i < ARRAY_SIZE(my_user_config.os_default_layer); i++, p_os++) {
        uprintf("id:%u, default layer:%u\n", i, *p_os);
    }
}
#endif

uint32_t my_get_offset(const my_user_config_field_e field) {
    switch (field) {
        case MY_FIELD_LAYER0 ... MY_FIELD_LAYER7:
            return sizeof(my_hsvm_t) * field;
        case MY_FIELD_LAYER_TOGGLE ... MY_FIELD_SAME_VAL:
            return sizeof(my_hsvm_t) * ARRAY_SIZE(my_user_config.hsvm_layer) +
                   sizeof(bool) * (field - MY_FIELD_LAYER7 - 1);
        case MY_FIELD_OS_UNSURE ... MY_FIELD_OS_IOS:
            return sizeof(my_hsvm_t) * ARRAY_SIZE(my_user_config.hsvm_layer) +
                   sizeof(bool) * (MY_FIELD_OS_UNSURE - MY_FIELD_LAYER7 - 1) +
                   sizeof(my_user_config_field_e) * (field - MY_FIELD_OS_UNSURE);
        default :
            return 0;
    }
}

my_user_config_field_e MY_EECONFIG_get_current_layer_field(const layer_state_t state) {
    const uint8_t layer = get_highest_layer(state);
    return (layer == MY_FIELD_LAYER0) ? get_highest_layer(default_layer_state) : layer;
}

void MY_EECONFIG_read_all_data_from_user_datablock(void) {
    eeconfig_read_user_datablock(&my_user_config, 0, sizeof(my_user_config));
}
void MY_EECONFIG_update_all_data_to_user_datablock(void) {
    eeconfig_update_user_datablock(&my_user_config, 0, sizeof(my_user_config));
}

const my_hsvm_t* MY_EECONFIG_get_hsvm_layer_from_mem(const my_user_config_field_e field) {
    if (sizeof(my_user_config.hsvm_layer) <= field) {
        return NULL;
    }
    return &my_user_config.hsvm_layer[field];
}

void MY_EECONFIG_update_hsvm_layer_to_eeprom(const my_user_config_field_e field, const my_hsvm_t* hsvm_layer) {
    if (sizeof(my_user_config.hsvm_layer) <= field) {
        return;
    }
    my_user_config.hsvm_layer[field] = *hsvm_layer;
    eeconfig_update_user_datablock(hsvm_layer, my_get_offset(field), sizeof(my_hsvm_t));
}

bool MY_EECONFIG_get_rgb_per_layer_from_mem(void) {
    return my_user_config.is_rgb_per_layer;
}

void MY_EECONFIG_update_rgb_per_layer_to_eeprom(const bool is_rgb_per_layer) {
    my_user_config.is_rgb_per_layer = is_rgb_per_layer;
    eeconfig_update_user_datablock(&is_rgb_per_layer, my_get_offset(MY_FIELD_LAYER_TOGGLE), sizeof(is_rgb_per_layer));
}

bool MY_EECONFIG_get_use_same_val_from_mem(void) {
    return my_user_config.to_use_same_val;
}

void MY_EECONFIG_update_use_same_val_to_eeprom(const bool to_use_same_val) {
    my_user_config.to_use_same_val = to_use_same_val;
    eeconfig_update_user_datablock(&to_use_same_val, my_get_offset(MY_FIELD_SAME_VAL), sizeof(to_use_same_val));
}

my_user_config_field_e MY_EECONFIG_get_os_default_layer_from_mem() {
    const os_variant_t os = detected_host_os();
    switch (os) {
        case OS_UNSURE ... OS_IOS:
            return my_user_config.os_default_layer[os];
        default:
            return MY_FIELD_LAYER0;
    }
}

void MY_EECONFIG_update_os_default_layer_to_eeprom(const my_user_config_field_e field) {
    const os_variant_t os = detected_host_os();
    if ((sizeof(my_user_config.os_default_layer) <= os) || (sizeof(my_user_config.hsvm_layer) <= field)) {
        return;
    }

    my_user_config.os_default_layer[os] = field;
    const my_user_config_field_e os_field = MY_FIELD_OS_UNSURE + os;
    eeconfig_update_user_datablock(&field, my_get_offset(os_field), sizeof(field));
}

void MY_EECONFIG_eeconfig_init_user_datablock(void) {
    MY_EECONFIG_update_all_data_to_user_datablock();
}

void MY_EECONFIG_keyboard_post_init_user(void) {
    MY_EECONFIG_read_all_data_from_user_datablock();
}

bool MY_EECONFIG_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_RESET:
            if (record->event.pressed) {
                rgblight_blink_layer_repeat(MY_BLINK_RESET, 300, 3);
                eeconfig_init_user_datablock();
                MY_EECONFIG_update_all_data_to_user_datablock();
            }
            return false;
        default:
            return true;
    }
}
