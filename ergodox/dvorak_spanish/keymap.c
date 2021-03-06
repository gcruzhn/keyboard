#include "ez.h"
#include "debug.h"
#include "action_layer.h"

/******************************************************************************************
 * SPANISH DVORAK LAYOUT (see http://djelibeibi.unex.es/dvorak/)
 * Layer 1: auxiliary keys
 * Layer 2: navigation keys (left hand only layer)
 * Layer 3: full qwerty layout
 ******************************************************************************************
 * IMPORTANT: Software layout must be set to SPANISH QWERTY to work properly
 *****************************************************************************************/
/* TAP_DANCE_ENABLE=yes */

// LAYERS
#define BASE    0 // dvorak layout (default)
#define AUX     1 // auxiliary keys
#define NAV     2 // navigation layout
#define QWERTY  3 // qwerty layout

// MACROS
#define OBRACE 0 // key { or shift
#define CBRACE 1 // key } or shift
#define OBRACK 2 // key [ or left alt
#define CBRACK 3 // key ] or left alt
#define MRALT   4 // key left or RALT
#define CAPS   5 // caps lock

// LEDS
#define USB_LED_NUM_LOCK    0
#define USB_LED_CAPS_LOCK   2
#define USB_LED_SCROLL_LOCK 2
#define USB_LED_COMPOSE     3
#define USB_LED_KANA        4

// TIMERS
#define KEY_TAP_FAST 85
#define KEY_TAP_SLOW 90

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base layer
 * Keys with double values (like Esc/Ctrl) correspond to the 'tapped' key and the 'held' key, respectively
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   \    |   1  |   2  |   3  |   4  |   5  |  <>  |           |   ¡  |   6  |   7  |   8  |   9  |   0  |   '    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | F1/~L1 |   .  |   ,  |   Ñ  |   P  |   Y  | L2   |           |  L1  |   F  |   G  |   C  |   H  |   L  |ALL_T/+ |
 * |--------+------+------+------+------+------|      |           | ~L1  |------+------+------+------+------+--------|
 * |Esc/Ctrl|   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   R  |   T  |   N  |   S  |'/RCtrl |
 * |--------+------+------+------+------+------| DEL  |           | ALT  |------+------+------+------+------+--------|
 * | {/LSft |   -  |   Q  |   J  |   K  |   X  |      |           | TAB  |   B  |   M  |   W  |   V  |   Z  | }/RSft |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |[/LALT| HOME |PGDOWN|PUP/SA|END/⌘ |                                       |LEFT/⌘|DWN/SA|  UP  |RIGHT |]/LALT|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |F5/CAG|F6/~L1|       |F7/~L1|F8/CAG|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |F4/CA |       |F11/CA|        |      |
 *                                 | ENTER| TAB  |------|       |------|  BSPC  | SPACE|
 *                                 |      |      |  F3  |       |F12/RALT|      |      |
 *                                 `--------------------'       `----------------------'
 *  CAG = CTRL-ALT-GUI
 *   CA = CTRL-ALT
 *   SA = SHIFT-ALT
 *
 */
[BASE] = KEYMAP(
        // left hand
        KC_GRAVE,       KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_NONUS_BSLASH,
        LT(AUX, KC_F1), KC_DOT, KC_COMM,KC_SCLN,KC_P,   KC_Y,   TG(NAV),
        CTL_T(KC_ESC),  KC_A,   KC_O,   KC_E,   KC_U,   KC_I,
        M(OBRACE),      KC_SLSH,KC_Q,   KC_J,   KC_K,   KC_X,   MEH_T(KC_DEL),
        M(OBRACK),      KC_HOME,KC_PGDN,MT(MOD_LALT | MOD_LSFT, KC_PGUP),MT(MOD_LGUI,KC_END),
                                                           LCAG_T(KC_F5),  LT(AUX, KC_F6),
                                                           MT(MOD_LALT | MOD_LCTL, KC_F4),
                                                           KC_ENT,KC_TAB,KC_F3,
        // right hand
                    KC_EQL,    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,
                    KC_FN1,    KC_F,   KC_G,   KC_C,   KC_H,   KC_L,   ALL_T(KC_RBRACKET),
                               KC_D,   KC_R,   KC_T,   KC_N,   KC_S,   CTL_T(KC_QUOTE),
                 LALT(KC_TAB), KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   M(CBRACE),
                                       MT(MOD_LGUI,KC_LEFT),MT(MOD_LALT | MOD_LSFT, KC_DOWN),KC_UP,  KC_RGHT,M(CBRACK),
        LT(AUX, KC_F7), LCAG_T(KC_F8),
        MT(MOD_LALT | MOD_LCTL, KC_F11),
        M(MRALT),KC_BSPC, KC_SPC
    ),
/* Keymap 1: Aux layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   F12  |  F1  |  F2  |  F3  |  F4  |  F5  | SLEEP            | PWR  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  <   |  >   |      |      |      |  L3  |           |TRANS |      |   7  |   8  |   9  |   *  |  `^    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |CAPSLOCK|      |      |      |      |      |------|           |------|      |   4  |   5  |   6  |   +  |   Ç    |
 * |--------+------+------+------+------+------|  L3  |           |PSCR  |------+------+------+------+------+--------|
 * |  CTRL-S|CTRL-Z|CTRL-X|CTRL-C|CTRL-V|      |      |           |      |      |   1  |   2  |   3  |   /  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LGUI-S|LGUI-Z|LGUI-X|LGUI-C|LGUI-V|                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      | Play |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | VolUp|      |      |
 *                                 | BSPC |      |------|       |------| Prev | Next |
 *                                 |      |      |      |       | VolDn|      |      |
 *                                 `--------------------'       `--------------------'
 */
[AUX] = KEYMAP(
       // left hand
       KC_F12 , KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_SLEP,
       KC_TRNS, KC_NONUS_BSLASH, LSFT(KC_NONUS_BSLASH), KC_NO, KC_NO, KC_NO, KC_TRNS,
       M(CAPS)  , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       LCTL(KC_S), LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO, TG(QWERTY),
       LGUI(KC_S), LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V),
                                                            KC_NO  , KC_TRNS,
                                                                       KC_NO,
                                                KC_BSPC, KC_NO, KC_NO,
       // right hand
            KC_PWR,  KC_F6,   KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,
            KC_TRNS, KC_NO,   KC_7,   KC_8,   KC_9,    KC_PAST, KC_LBRACKET,
                     KC_NO,   KC_4,   KC_5,   KC_6,    KC_PPLS, KC_BSLASH,
            KC_PSCR, KC_NO,   KC_1,   KC_2,   KC_3,    KC_PSLS, KC_NO,
                              KC_NO  ,KC_DOT, KC_0,    KC_PEQL, KC_NO,
       KC_TRNS, KC_MPLY,
       KC_VOLU,
       KC_VOLD, KC_MPRV, KC_MNXT
),
/* Keymap 2: Navigation layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  F11   |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |CTRL-0  |  <   |  >   |   q  | MsUp |      |TRANS |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  ESC   | SPACE|   .  |MsLeft|MsDown|MsRght|------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|TRANS |           |      |------+------+------+------+------+--------|
 * | CTRL-+ | LEFT | DOWN |  UP  |RIGHT | ENTER|      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |CTRL--| HOME |PGDOWN| PGUP | END  |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | BACK | FWD  |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |VolUp |       |      |      |      |
 *                                 | Lclk | Rclk |------|       |------|      |      |
 *                                 |      |      |VolDn |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NAV] = KEYMAP(
       // left hand
        KC_F11  , KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_NO,
       LCTL(KC_0), KC_NONUS_BSLASH, LSFT(KC_NONUS_BSLASH), LALT(KC_F4),  KC_MS_U, KC_NO, KC_TRNS,
       KC_ESC  , KC_SPC, KC_DOT, KC_MS_L, KC_MS_D, KC_MS_R,
       LCTL(KC_RBRACKET), KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT, KC_ENT, KC_NO,
       LCTL(KC_SLSH), KC_HOME,KC_PGDN,KC_PGUP,KC_END,
                                                 LALT(KC_LEFT), LALT(KC_RIGHT),
                                                                       KC_VOLU,
                                                     KC_BTN1, KC_BTN2, KC_VOLD,
       // right hand
            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
                    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
                            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_NO, KC_NO
),
/* Keymap 3: QWERTY layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   \    |   1  |   2  |   3  |   4  |   5  |  <>  |           |   ¡  |   6  |   7  |   8  |   9  |   0  |   '    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TRANS |   Q  |   W  |   E  |   R  |   T  |TRANS |           | TRANS|   Y  |   U  |   I  |   O  |   P  |ALL_T/+ |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Esc/Ctrl|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ñ  |'/RCtrl |
 * |--------+------+------+------+------+------|TRANS |           | RALT |------+------+------+------+------+--------|
 * | {/LSft |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   -  | }/RSft |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |[/LALT| HOME |PGDOWN| PGUP | END  |                                       | LEFT | DOWN |  UP  |RIGHT |]/LALT|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |F5/CAG| TRANS|       | TRANS|F8/CAG|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |F4/CA |       |F11/CA|        |      |
 *                                 | ENTER| TAB  |------|       |------|  BSPC  | SPACE|
 *                                 |      |      | TRANS|       |F12/SA|        |      |
 *                                 `--------------------'       `----------------------'
 *  CAG = CTRL-ALT-GUI
 *   CA = CTRL-ALT
 *   SA = SHIFT-ALT
 *
 */
[QWERTY] = KEYMAP(
        // left hand
        KC_GRAVE,       KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_NONUS_BSLASH,
        KC_TRNS,        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_TRNS,
        CTL_T(KC_ESC),  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        M(OBRACE),      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_TRNS,
        M(OBRACK),      KC_HOME,KC_PGDN,KC_PGUP,KC_END,
                                                                  LCAG_T(KC_F5),  KC_TRNS,
                                                           MT(MOD_LALT | MOD_LCTL, KC_F4),
                                                                    KC_ENT,KC_TAB,KC_NO,
        // right hand
                    KC_EQL,    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,
                    KC_TRNS,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   ALL_T(KC_RBRACKET),
                               KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,CTL_T(KC_QUOTE),
                    KC_RALT,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,M(CBRACE),
                                       KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,M(CBRACK),
        KC_TRNS, LCAG_T(KC_F8),
        MT(MOD_LALT | MOD_LCTL, KC_F11),
        M(MRALT),KC_BSPC, KC_SPC
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(AUX)                // FN1 - Momentary Layer 1 (Aux)
};

static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case OBRACE: {
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
                if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
                    register_code(KC_RALT);
                    register_code(KC_QUOTE);
                    unregister_code(KC_QUOTE);
                    unregister_code(KC_RALT);
                }
            }
            break;
        }
        case CBRACE: {
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_RSFT);
            } else { 
                unregister_code(KC_RSFT);
                if (timer_elapsed(key_timer) < KEY_TAP_SLOW) { 
                    register_code(KC_RALT); 
                    register_code(KC_BSLS); 
                    unregister_code(KC_BSLS); 
                    unregister_code(KC_RALT); 
                }
            }
            break;
        }
        case OBRACK: {
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LALT);
            } else { 
                unregister_code(KC_LALT);
                if (timer_elapsed(key_timer) < KEY_TAP_SLOW) { 
                    register_code(KC_RALT); 
                    register_code(KC_LBRACKET); 
                    unregister_code(KC_LBRACKET); 
                    unregister_code(KC_RALT); 
                }
            }
            break;
        }
        case CBRACK: {
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LALT);
            } else { 
                unregister_code(KC_LALT);
                if (timer_elapsed(key_timer) < KEY_TAP_SLOW) { 
                    register_code(KC_RALT); 
                    register_code(KC_RBRACKET); 
                    unregister_code(KC_RBRACKET); 
                    unregister_code(KC_RALT); 
                }
            }
            break;
        }
        case MRALT: {
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_RALT);
            } else { 
                unregister_code(KC_RALT);
                if (timer_elapsed(key_timer) < KEY_TAP_SLOW) { 
                    register_code(KC_F12); 
                    unregister_code(KC_F12); 
                }
            }
            break;
        }
        case CAPS: {
            if (record->event.pressed) {
                register_code(KC_CAPSLOCK);
            } else { 
                unregister_code(KC_CAPSLOCK);
            }
            break;
        }
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
        case 1:
            ergodox_right_led_3_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }
    
    // Turn the caps lock led on
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        ergodox_right_led_1_on();
    }

}

