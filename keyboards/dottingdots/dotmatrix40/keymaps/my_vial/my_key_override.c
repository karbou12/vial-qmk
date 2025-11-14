// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef KEY_OVERRIDE_ENABLE

#define ko_make_with_negmods(trigger_mods, trigger_key, replacement_key, negative_mask) \
    ko_make_with_layers_and_negmods(trigger_mods, trigger_key, replacement_key, ~0, negative_mask)

const key_override_t wheel_left_override  = ko_make_with_negmods(MOD_BIT(KC_LSFT), MS_WHLU, MS_WHLL, MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
const key_override_t wheel_right_override = ko_make_with_negmods(MOD_BIT(KC_LSFT), MS_WHLD, MS_WHLR, MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));

const key_override_t arrow_left_override  = ko_make_with_negmods(MOD_BIT(KC_LALT), MS_WHLD, KC_LEFT, MOD_BIT(KC_LCTL));
const key_override_t arrow_right_override = ko_make_with_negmods(MOD_BIT(KC_LALT), MS_WHLU, KC_RGHT, MOD_BIT(KC_LCTL));

const key_override_t arrow_up_override    = ko_make_basic(MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL), MS_WHLD, KC_UP);
const key_override_t arrow_down_override  = ko_make_basic(MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL), MS_WHLU, KC_DOWN);

const key_override_t app_prev_override    = ko_make_basic(MOD_BIT(KC_LGUI), MS_WHLD, LSG(KC_TAB));
const key_override_t app_next_override    = ko_make_basic(MOD_BIT(KC_LGUI), MS_WHLU, LGUI(KC_TAB));

const key_override_t tab_prev_override    = ko_make_with_negmods(MOD_BIT(KC_LCTL), MS_WHLD, LSFT(LCTL(KC_TAB)), MOD_BIT(KC_LALT));
const key_override_t tab_next_override    = ko_make_with_negmods(MOD_BIT(KC_LCTL), MS_WHLU, LCTL(KC_TAB),   MOD_BIT(KC_LALT));

const key_override_t *key_overrides[] = {
    &wheel_left_override,
    &wheel_right_override,
    &arrow_left_override,
    &arrow_right_override,
    &arrow_up_override,
    &arrow_down_override,
    &app_prev_override,
    &app_next_override,
    &tab_prev_override,
    &tab_next_override,
};
const uint16_t key_overrides_raw_size = ARRAY_SIZE(key_overrides);

#ifndef USE_LOCAL_KEY_OVERRIDES

static bool is_init_or_default_key_override(const vial_key_override_entry_t *entry) {
    vial_key_override_entry_t init_entry = { 0 };
    if (memcmp(&init_entry, entry, sizeof(vial_key_override_entry_t)) == 0) {
        return true;
    }

    init_entry.layers = ~0;
    init_entry.options = ko_options_default;

    return (memcmp(&init_entry, entry, sizeof(vial_key_override_entry_t)) == 0) ? true : false;
}

void MY_KO_keyboard_post_init_user(void) {
    // check already key_override is there
    {
        vial_key_override_entry_t entry = {0};
        if (dynamic_keymap_get_key_override(0, &entry) < 0) {
            return;
        }

        if (!is_init_or_default_key_override(&entry)) {
            return;
        }
    }

    for (uint8_t i = 0; i < key_overrides_raw_size; i++) {
        vial_key_override_entry_t entry = {0};
        entry.trigger = key_overrides[i]->trigger;
        entry.replacement = key_overrides[i]->replacement;
        entry.layers = key_overrides[i]->layers;
        entry.trigger_mods = key_overrides[i]->trigger_mods;
        entry.negative_mod_mask = key_overrides[i]->negative_mod_mask;
        entry.suppressed_mods = key_overrides[i]->suppressed_mods;
        entry.options = key_overrides[i]->options;
        entry.options |= vial_ko_enabled;

        // set to eeprom
        dynamic_keymap_set_key_override(i, &entry);
    }

    vial_init();
}
#endif

#endif

