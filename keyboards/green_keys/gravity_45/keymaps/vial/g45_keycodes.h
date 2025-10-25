// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum custum_keycodes {
#ifdef VIAL_ENABLE
    USR_RESET = QK_KB_0,
#else
    USR_RESET = SAFE_RANGE,
#endif
    USR_RGB_LAYER_TOG,
    USR_RGB_RETAIN_VAL_TOG,
    USR_RGB_LAYER_HUE_UP,
    USR_RGB_LAYER_HUE_DOWN,
    USR_RGB_LAYER_SAT_UP,
    USR_RGB_LAYER_SAT_DOWN,
    USR_RGB_LAYER_VAL_UP,
    USR_RGB_LAYER_VAL_DOWN,
    USR_RGB_AUTO_SAVE_TOG,
    USR_OS_DEFAULT_LAYER,
};
