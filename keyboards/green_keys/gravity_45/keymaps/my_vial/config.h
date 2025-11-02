// Copyright 2025 takashicompany (@takashicompany)
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 9
#define VIAL_KEYBOARD_UID {0x6B, 0x7B, 0xD1, 0x10, 0x4E, 0x90, 0xAE, 0x6F}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {1, 11}

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 3000

#ifndef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#endif

#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_RETAIN_VAL
#define RGBLIGHT_LAYER_BLINK

#define EECONFIG_USER_DATA_SIZE 43 // keep the largest size ever.

#define MY_FW_VER_MAJOR 1
#define MY_FW_VER_MINOR 0
#define MY_FW_VER_PATCH 0

#define MY_FW_VER_MAJOR_OFFSET 8
#define MY_FW_VER_MINOR_OFFSET 4

#define MY_CONCAT_VERSION(M, m, p) ((M << MY_FW_VER_MAJOR_OFFSET) | (m << MY_FW_VER_MINOR_OFFSET) | p)
#define FVS(x) MY_FW_VER_ ## x
#define EECONFIG_USER_DATA_VERSION MY_CONCAT_VERSION(FVS(MAJOR), FVS(MINOR), FVS(PATCH))
