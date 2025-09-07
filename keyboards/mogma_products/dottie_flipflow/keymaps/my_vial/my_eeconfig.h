#pragma once
#include "config.h"

typedef struct {
    hsv_t hsv;
    uint8_t mode;
} my_hsvm_t;

typedef struct {
    my_hsvm_t hsvm_layer[DYNAMIC_KEYMAP_LAYER_COUNT]; // rgb
    bool is_rgb_per_layer; // rgb
    bool to_use_same_val; // rgb
} my_user_config_t;

typedef enum {
    MY_FIELD_LAYER0 = 0,
    MY_FIELD_LAYER1,
    MY_FIELD_LAYER2,
    MY_FIELD_LAYER3,
    MY_FIELD_LAYER4,
    MY_FIELD_LAYER5,
    MY_FIELD_LAYER6,
    MY_FIELD_LAYER7,
    MY_FIELD_LAYER_TOGGLE,
    MY_FIELD_SAME_VAL,
    MY_FIELD_ALL
} my_user_config_field_e;

extern my_user_config_t my_user_confg;

extern void MY_EECONFIG_read_all_data_from_user_datablock(void);
extern void MY_EECONFIG_update_all_data_to_user_datablock(void);

extern const my_hsvm_t* MY_EECONFIG_get_hsvm_layer_from_mem(const my_user_config_field_e field);
extern void MY_EECONFIG_update_hsvm_layer_to_eeprom(const my_user_config_field_e field, const my_hsvm_t* hsvm_layer);

extern bool MY_EECONFIG_get_rgb_per_layer_from_mem(void);
extern void MY_EECONFIG_update_rgb_per_layer_to_eeprom(const bool is_rgb_per_layer);

extern bool MY_EECONFIG_get_use_same_val_from_mem(void);
extern void MY_EECONFIG_update_use_same_val_to_eeprom(const bool to_use_same_val);

// override func
extern bool MY_EECONFIG_process_record_user(uint16_t keycode, keyrecord_t *record);

#ifdef CONSOLE_ENABLE
extern void my_dump_eeconfig(const char* const func);
#define MY_DUMP_EECONFIG() my_dump_eeconfig(__FUNCTION__)
#else
#define MY_DUMP_EECONFIG()
#endif
