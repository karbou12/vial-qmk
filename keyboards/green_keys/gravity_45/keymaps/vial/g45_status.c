// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "g45_status.h"

static bool g45_is_change_layer_key_pressed_on_non_default_layer = false;
static bool g45_is_user_reset_key_pressed_on_non_default_layer = false;

void G45_STATUS_set_change_layer_key_pressed_on_non_default_layer(const bool is_pressed) {
    g45_is_change_layer_key_pressed_on_non_default_layer = is_pressed;
}

void G45_STATUS_set_user_reset_key_pressed_on_non_default_layer(const bool is_pressed) {
    g45_is_user_reset_key_pressed_on_non_default_layer = is_pressed;
}

bool G45_STATUS_can_set_rgblight(void) {
    return g45_is_user_reset_key_pressed_on_non_default_layer ? false : true;
}

bool G45_STATUS_can_record_rgblight(void) {
    return (g45_is_change_layer_key_pressed_on_non_default_layer ||
            g45_is_user_reset_key_pressed_on_non_default_layer) ? false : true;
}

