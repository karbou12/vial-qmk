// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "config.h"

typedef enum {
    MY_FIELD_LAYER0 = 0,
    MY_FIELD_LAYER1,
    MY_FIELD_LAYER2,
    MY_FIELD_LAYER3,
    MY_FIELD_LAYER4,
    MY_FIELD_LAYER5,
    MY_FIELD_LAYER6,
    MY_FIELD_LAYER7,
    MY_FIELD_LAYER8,
    MY_FIELD_LAYER_TOGGLE,
    MY_FIELD_RETAIN_VAL_TOGGLE,
    MY_FIELD_OS_UNSURE,
    MY_FIELD_OS_LINUX,
    MY_FIELD_OS_WINDOWS,
    MY_FIELD_OS_MACOS,
    MY_FIELD_OS_IOS,
    MY_FIELD_ALL
} my_user_config_field_e;

typedef struct {
    hsv_t hsv;
    uint8_t mode;
} my_hsvm_t;

typedef struct {
    my_hsvm_t hsvm_layer[DYNAMIC_KEYMAP_LAYER_COUNT]; // rgb
    bool is_rgb_per_layer; // rgb
    bool to_retain_val; // rgb
    my_user_config_field_e os_default_layer[OS_IOS + 1]; // os
} my_user_config_t;

extern my_user_config_t my_user_confg;

extern my_user_config_field_e MY_EECONFIG_get_current_layer_field(const layer_state_t state);

extern void MY_EECONFIG_read_all_data_from_user_datablock(void);
extern void MY_EECONFIG_update_all_data_to_user_datablock(void);

extern const my_hsvm_t* MY_EECONFIG_get_hsvm_layer_from_mem(const my_user_config_field_e field);
extern void MY_EECONFIG_update_hsvm_layer_to_eeprom(const my_user_config_field_e field, const my_hsvm_t* hsvm_layer);

extern bool MY_EECONFIG_get_rgb_per_layer_from_mem(void);
extern void MY_EECONFIG_update_rgb_per_layer_to_eeprom(const bool is_rgb_per_layer);

extern bool MY_EECONFIG_get_retain_val_from_mem(void);
extern void MY_EECONFIG_update_retain_val_to_eeprom(const bool to_retain_val);

extern my_user_config_field_e MY_EECONFIG_get_os_default_layer_from_mem(void);
extern void MY_EECONFIG_update_os_default_layer_to_eeprom(const my_user_config_field_e field);

// override func
extern bool MY_EECONFIG_process_record_user(uint16_t keycode, keyrecord_t *record);

#ifdef CONSOLE_ENABLE
extern void my_dump_eeconfig(const char* const func);
#define MY_DUMP_EECONFIG() my_dump_eeconfig(__FUNCTION__)
#else
#define MY_DUMP_EECONFIG()
#endif
