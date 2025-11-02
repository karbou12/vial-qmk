// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum custum_keycodes {
#ifdef VIAL_ENABLE
    MY_RESET = QK_KB_0,
#else
    MY_RESET = SAFE_RANGE,
#endif
    MY_RGB_LAYER_TOG,
    MY_RGB_LAYER_SAME_VAL,
    MY_RGB_LAYER_HUE_UP,
    MY_RGB_LAYER_HUE_DOWN,
    MY_RGB_LAYER_SAT_UP,
    MY_RGB_LAYER_SAT_DOWN,
    MY_RGB_LAYER_VAL_UP,
    MY_RGB_LAYER_VAL_DOWN,
    MY_RGB_LAYER_SAVE,
    MY_OS_DEFAULT_LAYER,
};
