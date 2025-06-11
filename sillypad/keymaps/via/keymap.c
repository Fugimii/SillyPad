// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "action.h"  // Required for keymap functions

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * ├───┼───┼───┼───┤
     * │SW0│SW1│   │   │ (virtual row for DIP switches)
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_5x4(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, KC_PPLS,
        KC_AUDIO_MUTE, KC_MEDIA_PLAY_PAUSE, KC_NO, KC_NO
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][2][2] = {
    [0] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
};
#endif

void simulate_keypress(uint8_t row, uint8_t col) {
    // Get active layer
    uint8_t layer = get_highest_layer(layer_state);
    
    // Create key position structure
    keypos_t pos = {.row = row, .col = col};
    
    // Get keycode using standard QMK function
    uint16_t keycode = keymap_key_to_keycode(layer, pos);
    
    if (keycode != KC_NO) {
        tap_code(keycode);  // Press and release
    }
}

// The rotary encoder switches are connected directly to the MCU, instead of through the matrix because im stupid.
// We pretend that the rotary encoder switches are DIP switches, and then simulate keypresses when they are used.
#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) { return false; }
    
    // Only trigger when dip switch is engaged (active == true)
    if (active) {
        switch (index) {
            case 0:
                simulate_keypress(4, 0);
                break;
            case 1:
                simulate_keypress(4, 1);
                break;
        }
    }
    return true;
}
#endif

#ifdef OLED_ENABLE
// Rotate OLED 180 degrees
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

// List of names for each layer
const char *layer_names[] = {
    [0] = "Default",
    [1] = "Coding",
    [2] = "Blender",
    [3] = "Fusion",
};

bool oled_task_user(void) {
    int l = get_highest_layer(layer_state);
    // if highest layer state is 0, it means it could be either
    // colemak or qwerty. need to set it to the default
    // layer state. if default is 0 then no change.
    // otherwise subtract one.
    if (l==0 && default_layer_state>0) {
        l = default_layer_state-1;
    }
    
    // Ensure l is within bounds of layer_names array
    if (l >= sizeof(layer_names)/sizeof(layer_names[0])) {
        l = 0; // Default to layer 0 if out of bounds
    }
    
    oled_write("Layer: ", false);
    oled_write_ln(layer_names[l], false);
    return false;
}
#endif