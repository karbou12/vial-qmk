// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

typedef enum {
    G45_BLINK_RESET = 0,
    G45_BLINK_ON,
    G45_BLINK_OFF,
    G45_BLINK_DF
} g45_blink_layer_e;

extern const rgblight_segment_t * const g45_blink_layers[];
extern const rgblight_segment_t * const g45_rgb_layers[];

extern void G45_RGB_eeconfig_migrate_mem(const g45_user_config_u* bk, const uint32_t prev_ver);
extern void G45_RGB_eeconfig_init_mem(void);
extern void G45_RGB_keyboard_post_init_user(void);
extern layer_state_t G45_RGB_default_layer_state_set_user(layer_state_t state);
extern layer_state_t G45_RGB_layer_state_set_user(layer_state_t state);
extern bool G45_RGB_process_record_user(uint16_t keycode, keyrecord_t *record);
extern void G45_RGB_post_process_record_user(uint16_t keycode, keyrecord_t *record);
extern void G45_RGB_caps_word_set_user(bool active);
