// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

typedef enum {
    G45_BLINK_RESET = 0,
    G45_BLINK_ON,
    G45_BLINK_OFF,
    G45_BLINK_DF
} g45_blink_layer_e;

extern void G45_RGB_eeconfig_migrate_mem(const g45_user_config_u* bk, const uint32_t prev_ver);
