/* Copyright 2022 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <keymap_german.h>
#include <keymap_us.h>

// clang-format off

enum layers{
    DE_BASE,
    US_BASE,
    DEUS_FN,
};

#include "init.c"
#include "input.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DE_BASE] = LAYOUT_iso_110(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_MUTE,  KC_PSCR,  _______,  RGB_MOD,  UC_START, PR_EMOJI, _______,  _______,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     DE_SS,    DE_ACUT,    KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     DE_Z,     KC_U,     KC_I,     KC_O,     KC_P,     DE_UDIA,  DE_PLUS,              KC_DEL,   KC_END,   KC_PGDN,  KC_P7,    KC_P8,    KC_P9,
        CW_TOGG,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     DE_ODIA,  DE_ADIA,  DE_HASH,    KC_ENT,                                 KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,  DE_LABK,  DE_Y,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     DE_COMM , DE_DOT,   DE_MINS,              KC_RSFT,            KC_UP,              KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_APP,   MO(DEUS_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,              KC_PDOT,  KC_PENT),

    [US_BASE] = LAYOUT_iso_110(
        _______,  _______,  _______,  _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  KC_MINS,  KC_EQL,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______,   _______,  KC_Y,     _______,  _______,  _______,  _______,  KC_LBRC,  KC_RBRC,              _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______,   _______,  _______,  _______,  _______,  _______,  KC_SCLN,  KC_QUOT,  KC_NUHS,    _______,                                _______,  _______,  _______,  _______,
        _______,  KC_NUBS,  KC_Z,     _______, _______,   _______,  _______,  _______,  _______,  KC_COMM,  KC_DOT,   KC_SLSH,              _______,            _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,            _______,  _______),

    [DEUS_FN] = LAYOUT_iso_110(
        _______,  KC_BRID,  KC_BRIU,  _______,  _______,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    RGB_TOG,  _______,  _______,  RGB_TOG,  _______,  _______,  _______,  QK_REBOOT,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,                                _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,            _______,  _______),


};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][1][2] = {
    [DE_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [US_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [DEUS_FN] = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) }
};
#endif
