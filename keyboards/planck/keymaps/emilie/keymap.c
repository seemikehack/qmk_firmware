#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_colemak.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum planck_layers {
  _COLEMAK,
  _SWCOLE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN
};

enum planck_keycodes {
  COLEMAK = SAFE_RANGE,
  SWCOLE,
  BKLT
};

enum tap_dance_action_names {
  LLCK = 0,
  RLCK,
  FLCK,
  CLCK
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  FN  | Ctrl | GUI  | Alt  |Lower |Space | Bksp |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_ESC,   KC_Q,    KC_W,    KC_F,    KC_P,       KC_G,    KC_J,    KC_L,       KC_U,    KC_Y,    KC_SCLN, KC_DEL},
  {KC_TAB,   KC_A,    KC_R,    KC_S,    KC_T,       KC_D,    KC_H,    KC_N,       KC_E,    KC_I,    KC_O,    KC_QUOT},
  {TD(CLCK), KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,    KC_K,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {TD(FLCK), KC_LCTL, KC_LGUI, KC_LALT, TD(LLCK),   KC_SPC,  KC_BSPC, TD(RLCK),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

[_SWCOLE] = { /* Software Colemak */
  {_______, CM_Q,    CM_W,    CM_F,    CM_P,    CM_G,    CM_J,    CM_L,    CM_U,    CM_Y,    CM_SCLN, _______},
  {_______, CM_A,    CM_R,    CM_S,    CM_T,    CM_D,    CM_H,    CM_N,    CM_E,    CM_I,    CM_O,    _______},
  {_______, CM_Z,    CM_X,    CM_C,    CM_V,    CM_B,    CM_K,    CM_M,    CM_COMM, CM_DOT,  CM_SLSH, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {_______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {_______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |MidiOn|MidOff|Colemk|SwCole|      | Reset|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Backlt|      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, MI_ON,   MI_OFF,  COLEMAK, SWCOLE,  _______, RESET},
  {_______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______},
  {BKLT,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Function layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = {
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = {
  {NOTE_B5, 20},
  {NOTE_B6, 8},
  {NOTE_DS6, 20},
  {NOTE_B6, 8}
};

float tone_qwerty[][2]  = SONG(QWERTY_SOUND);
float tone_colemak[][2] = SONG(COLEMAK_SOUND);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
float music_scale[][2]  = SONG(MUSIC_SCALE_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void lock_low(void) {
  layer_move(_LOWER);
  // TODO flash LEDs
}

void lock_rai(void) {
  layer_move(_RAISE);
  // TODO flash LEDs
}

void lock_fn(void) {
  layer_move(_FN);
  // TODO flash LEDs
}

void low_press(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_on(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
}

void low_done(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    lock_low();
  }
}

void low_reset(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_off(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
}

void rai_press(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_on(_RAISE);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
}

void rai_done(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    lock_rai();
  }
}

void rai_reset(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_off(_RAISE);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
}

void fn_press(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_on(_FN);
  }
}

void fn_done(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    lock_fn();
  }
}

void fn_reset(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_off(_FN);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [LLCK] = ACTION_TAP_DANCE_FN_ADVANCED(low_press, low_done, low_reset),
  [RLCK] = ACTION_TAP_DANCE_FN_ADVANCED(rai_press, rai_done, rai_reset),
  [FLCK] = ACTION_TAP_DANCE_FN_ADVANCED(fn_press, fn_done, fn_reset),
  [CLCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
    case SWCOLE:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_SWCOLE);
      }
      return false;
    case BKLT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
    }
    return true;
};

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    startup_user();
  #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
  _delay_ms(20); // gets rid of tick
  PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
  PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
