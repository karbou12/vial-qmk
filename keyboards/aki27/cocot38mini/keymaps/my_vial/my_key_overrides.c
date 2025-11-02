#if defined(KEY_OVERRIDE_ENABLE) && defined(USE_LOCAL_KEY_OVERRIDES)

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

#endif
