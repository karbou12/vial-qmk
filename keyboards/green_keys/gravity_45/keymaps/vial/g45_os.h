// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

extern void G45_OS_eeconfig_init_mem(void);
extern bool G45_OS_process_detected_host_os_user(os_variant_t detected_os);
extern bool G45_OS_process_record_user(uint16_t keycode, keyrecord_t *record);
extern void G45_OS_eeconfig_migrate_mem(const g45_user_config_u* bk, const uint32_t prev_ver);
