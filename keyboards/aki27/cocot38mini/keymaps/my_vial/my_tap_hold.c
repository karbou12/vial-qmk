#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RCTL_T(KC_SCLN):
        case LGUI_T(KC_TAB):
        case LGUI_T(KC_BSPC):
        case LCTL_T(KC_TAB):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
    return false;
}

#endif

char chordal_hold_handedness(keypos_t key) {
    if (key.row == 3 && key.col == 4) { // center key
        return '*';
    }

    return (key.col < MATRIX_COLS / 2) ? 'L' : 'R';
}
