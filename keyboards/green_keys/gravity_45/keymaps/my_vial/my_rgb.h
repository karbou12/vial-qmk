// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

typedef enum {
    MY_BLINK_RESET = 0,
    MY_BLINK_ON,
    MY_BLINK_OFF,
    MY_BLINK_DF
} my_blink_layer_e;

extern void MY_RGB_eeconfig_migrate_mem(const my_user_config_u* bk, const uint32_t prev_ver);
