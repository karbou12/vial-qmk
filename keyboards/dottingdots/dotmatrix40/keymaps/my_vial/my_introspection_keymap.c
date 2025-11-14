// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "my_tap_hold.c"
#include "my_key_override.c"
#include "my_rgb.c"

void keyboard_post_init_user() {
#ifndef USE_LOCAL_KEY_OVERRIDES
    MY_KO_keyboard_post_init_user();
#endif
    MY_RGB_keyboard_post_init_user();
}
