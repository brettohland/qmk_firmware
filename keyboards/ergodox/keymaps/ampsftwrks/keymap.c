// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define GAME 2 // Gaming layer with arrow keys

// Tap Dance Declarations
// https://github.com/qmk/qmk_firmware/wiki#tap-dance-a-single-key-can-do-3-5-or-100-different-things

enum {
  TD_BUILD_TEST = 0,
  TD_NEKO_FACE
};

enum {
  MC_NEKO_FACE = 0,
  MC_NEKO_FACE_SLACK,
  MC_OSX_EMOJI_PICKER
};
// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {

  // Tap once in Xcode to Build, twice to Test (⌘ + B -> ⌘ + U)
  [TD_BUILD_TEST] = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_B), LGUI(KC_U)),
  [TD_NEKO_FACE] = ACTION_TAP_DANCE_DOUBLE(M(0), M(1))

};

// Main Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer.
 *
 * Standard keyboard layout.
 * TDBT: Sends ⌘ + B when pressed once, and ⌘ + U when pressed a second time. (Build and Test in Xcode).
 * Space Cadet Shift Keys: Shift on hold, parens on tap.
 * CTL/Tab: Tab on tap, Control on hold.
 * CTL/': ' on tap, Control on hold.
 * HYPR: All modifiers.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  |  TG1 |           | EMOJ |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   Q  |   W  |   E  |   R  |   T  |  \   |           |  ⛔️  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |CTL/TAB |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |  CTL/' |
 * |--------+------+------+------+------+------|  `   |           | HYPR |------+------+------+------+------+--------|
 * |LShift( |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |RShift) |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |  ⛔️  | ⌥ +⌘ |  ⌥   |  ⌘   |                                       | ⌘ +B | ⌘ +R | ⌘ +U | NEKO | Wake |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | ⌘ +, |  F7  |       | PLAY | NEXT |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |  ⛔️  |       | PREV |        |      |
 *                                 |  ⌫   |  ⌘   |------|       |------|   ⏎    |  ⎵   |
 *                                 |      |      | MO1  |       | MO1  |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*

// Layer 0
[BASE] = KEYMAP(
        // Left Hand
        KC_ESCAPE,     KC_1,   KC_2,          KC_3,    KC_4,     KC_5,      TG(SYMB),
        KC_TAB,        KC_Q,   KC_W,          KC_E,    KC_R,     KC_T,      KC_BSLASH,
        CTL_T(KC_TAB), KC_A,   KC_S,          KC_D,    KC_F,     KC_G,
        KC_LSFT,       KC_Z,   KC_X,          KC_C,    KC_V,     KC_B,      KC_GRAVE,
        KC_LCTL,       KC_NO,  LALT(KC_LGUI), KC_LALT, KC_LGUI,
                                                            LGUI(KC_COMMA), KC_F7,
                                                                            KC_NO,
                                                        KC_BSPACE, KC_LGUI, MO(SYMB),
        
        // Right Hand
        TD(TD_BUILD_TEST), KC_6,       KC_7,        KC_8,       KC_9,    KC_0,      KC_MINUS,
        KC_NO,             KC_Y,       KC_U,        KC_I,       KC_O,    KC_P,      KC_BSLASH,
                           KC_H,       KC_J,        KC_K,       KC_L,    KC_SCOLON, CTL_T(KC_QUOTE),
        ALL_T(KC_NO),      KC_N,       KC_M,        KC_COMMA,   KC_DOT,  KC_SLASH,  KC_RSFT,
                           LGUI(KC_B),  LGUI(KC_R), LGUI(KC_U), M(0),   KC_WAKE,
        KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_NEXT_TRACK,
        KC_MEDIA_PREV_TRACK,
        MO(SYMB),KC_ENTER,KC_SPACE
),

/* Keymap 1: Symbol Layer
 * Left hand has symbols accessible but largely disabled many of the keys (to stop accidental input)
 * Right hand has other symbols as well as Vim movement keys available.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RESET  |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |      |           |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |   ⛔️   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  ⛔️  |  ⛔️  |  (   |   )  |  ⛔️  |  ⛔️  |           |  ⛔️  |  -   |   =  |  `   |  +   |  ⛔️  |   ⛔️   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  {   |   }  |  [   |   ]  |   *  |------|           |------| Left | Down |  Up  | Right|   -  |   ⛔️   |
 * |--------+------+------+------+------+------|  ⛔️  |           |  ⛔️  |------+------+------+------+------+--------|
 * |        |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |      |           |      |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |  ⛔️  |  ⛔️  |  ⛔️  |  ⛔️  |                                       |  ⛔️  |  ⛔️. |  ⛔️  |  ⛔️  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  TG2 |  ⛔️  |       |  ⛔️  |  ⛔️  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ⛔️  |       |  ⛔️  |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
//
// SYMBOLS
[SYMB] = KEYMAP(
       // Left hand
       RESET,   KC_NO,    KC_NO,    KC_NO,       KC_NO,       KC_NO,     KC_TRNS,
       KC_NO,   KC_NO,    KC_LPRN,  KC_RPRN,       KC_NO,       KC_NO,     KC_NO,
       KC_TRNS, KC_LCBR,  KC_RCBR,  KC_LBRACKET, KC_RBRACKET, KC_ASTR, KC_LSHIFT,
       KC_TRNS, KC_NO,    KC_NO,    KC_NO,       KC_NO,       KC_NO,
       KC_TRNS, KC_NO,    KC_NO,    KC_NO,       KC_NO,
                                                                      TG(2), KC_NO,
                                                                             KC_NO,
                                                         KC_TRNS, KC_TRNS, KC_TRNS,
       
       // Right hand
       KC_NO,   KC_NO,    KC_NO,    KC_NO,       KC_NO,       KC_NO,     KC_NO,
       KC_NO,   KC_MINUS, KC_EQUAL, KC_GRAVE,    KC_KP_PLUS,  KC_NO,     KC_NO,
                KC_LEFT,  KC_DOWN,  KC_UP,       KC_RIGHT,    KC_MINUS,  KC_NO,
       KC_NO,   KC_NO,    KC_NO,    KC_NO,       KC_NO,       KC_NO,     KC_TRNS,
       KC_NO,   KC_NO,    KC_NO,    KC_NO,       KC_NO,
       KC_NO,   KC_NO,
       KC_NO,   
       KC_TRNS,KC_TRNS,KC_TRNS
       
),

/* Keymap 2: Gaming Layer
 * Makes the entire left hand board transparent to Layer 0
 * Makes the right hand keyboard suitable for player 2 or arrow keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      | Left | Down | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|  N   |  M   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
//
// SYMBOLS
[GAME] = KEYMAP(
       // Left hand
       // Entire layer is transparent to the default layer.
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       
       // Right hand
       // Entierly disabled except for the arrow keys and two thumb buttons
       KC_NO,   KC_NO,    KC_NO,    KC_NO,       KC_NO,       KC_NO,     KC_NO,
       KC_NO,   KC_NO,    KC_NO,    KC_UP,       KC_NO,       KC_NO,     KC_NO,
                KC_NO,    KC_LEFT,  KC_DOWN,     KC_RIGHT,    KC_NO,     KC_NO,
       KC_NO,   KC_NO,    KC_NO,    KC_NO,       KC_NO,       KC_NO,     KC_NO,
       KC_NO,   KC_NO,    KC_NO,    KC_NO,       KC_NO,
       KC_NO,   KC_NO,
       KC_NO,   
       KC_TRNS, KC_N, KC_M
       
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case MC_NEKO_FACE:
      if (record->event.pressed) {
        return MACRO( D(LSFT), T(DOT), T(SCLN), U(LSFT), T(3), END  ); // this sends the string >:3
      }         
      break;

    case MC_NEKO_FACE_SLACK:
      if (record->event.pressed) {
        return MACRO( T(GRAVE), D(LSFT), T(DOT), T(SCLN), U(LSFT), T(3), T(GRAVE), END  ); // this sends the string `>:3`
      }
      break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};

