// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "config.h"

typedef enum {
    G45_FIELD_LAYER0 = 0,
    G45_FIELD_LAYER1,
    G45_FIELD_LAYER2,
    G45_FIELD_LAYER3,
    G45_FIELD_LAYER4,
    G45_FIELD_LAYER5,
    G45_FIELD_LAYER6,
    G45_FIELD_LAYER7,
    G45_FIELD_LAYER8,
    G45_FIELD_FLAGS,
    G45_FIELD_OS_UNSURE,
    G45_FIELD_OS_LINUX,
    G45_FIELD_OS_WINDOWS,
    G45_FIELD_OS_MACOS,
    G45_FIELD_OS_IOS,
    G45_FIELD_ALL
} g45_user_config_field_e;

typedef struct {
    hsv_t hsv;
    uint8_t mode;
} g45_hsvm_t;

typedef struct {
    g45_hsvm_t hsvm_layer[DYNAMIC_KEYMAP_LAYER_COUNT]; // rgb
    bool is_rgb_per_layer; // rgb
    bool to_retain_val; // rgb
    g45_user_config_field_e os_default_layer[OS_IOS + 1]; // os
} g45_user_config_t_v1;
#define G45_BASE_FW_VER_OF_USER_CONFIG_V1 G45_CONCAT_VERSION(0, 0, 5)

typedef struct {
    g45_hsvm_t hsvm_layer[DYNAMIC_KEYMAP_LAYER_COUNT]; // rgb
    union {
        uint8_t flag_raw;
        struct {
            bool is_rgb_per_layer : 1; // rgb
            bool is_auto_save_rgb : 1; //rgb
            bool to_retain_val : 1; // rgb
            uint8_t dummy : 5;
        } flags;
    };
    g45_user_config_field_e os_default_layer[OS_IOS + 1]; // os
} g45_user_config_t_v2;
#define G45_BASE_FW_VER_OF_USER_CONFIG_V2 G45_CONCAT_VERSION(1, 0, 0)

typedef union {
    g45_user_config_t_v2 v2;
    g45_user_config_t_v1 v1;
} g45_user_config_u;

#define G45_USER_CONFIG_VERSION 2
#define G45_USER_CONFIG_V_CONCAT(n) g45_user_config_t_v ## n
#define G45_USER_CONFIG_V(n)  G45_USER_CONFIG_V_CONCAT(n)
#define g45_user_config_t G45_USER_CONFIG_V(G45_USER_CONFIG_VERSION)

extern g45_user_config_t g45_user_confg;

extern g45_user_config_field_e G45_EECONFIG_get_current_layer_field(const layer_state_t state);

extern const g45_hsvm_t* G45_EECONFIG_get_hsvm_layer_from_mem(const g45_user_config_field_e field);
extern void G45_EECONFIG_update_hsvm_layer_to_eeprom(const g45_user_config_field_e field, const g45_hsvm_t* hsvm_layer);

extern bool G45_EECONFIG_get_rgb_per_layer_from_mem(void);
extern void G45_EECONFIG_update_rgb_per_layer_to_eeprom(const bool is_rgb_per_layer);

extern bool G45_EECONFIG_get_auto_save_rgb_from_mem(void);
extern void G45_EECONFIG_update_auto_save_rgb_to_eeprom(const bool is_rgb_per_layer);

extern bool G45_EECONFIG_get_retain_val_from_mem(void);
extern void G45_EECONFIG_update_retain_val_to_eeprom(const bool to_retain_val);

extern g45_user_config_field_e G45_EECONFIG_get_os_default_layer_from_mem(void);
extern void G45_EECONFIG_update_os_default_layer_to_eeprom(const g45_user_config_field_e field);

// override func
extern void G45_EECONFIG_eeconfig_init_user_datablock(void);
extern void G45_EECONFIG_keyboard_post_init_user(void);
extern bool G45_EECONFIG_process_record_user(uint16_t keycode, keyrecord_t *record);
extern bool G45_EECONFIG_migrate_user_datablock(void);

#ifdef CONSOLE_ENABLE
extern void g45_dump_eeconfig(const char* const func);
#define G45_DUMP_EECONFIG() g45_dump_eeconfig(__FUNCTION__)
#else
#define G45_DUMP_EECONFIG()
#endif
