/* Copyright 2023 @ rubienr (github.com/rubienr)
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

/*
// tap dance input / double tap input

enum {
    TD_CLL,
    TD_CLR,
    TD_TG_L,
    TD_TG_R,
};
*/

/*
// combo input

enum combo_events {
    CB_UE,
    CB_OE,
    CB_AE,
    CB_SZ,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ae_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM sz_combo[] = {KC_S, KC_Z, COMBO_END};
combo_t key_combos[] = {
    COMBO(ae_combo, DE_ADIA),
    COMBO(oe_combo, DE_ODIA),
    COMBO(ue_combo, DE_UDIA),
    COMBO(sz_combo, DE_SS),
};
*/

// custom key codes

enum custom_keycodes_t {
    CK_UCIS = SAFE_RANGE,
};

// utf8 ucis input
const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop"        , 0x1F4A9),                // 💩
    UCIS_SYM("rofl"        , 0x1F923),                // 🤣
    UCIS_SYM("look"        , 0xCA0, 0x5F, 0xCA0), // ಠ_ಠ
    UCIS_SYM("extrakurz"   , 0x0306),               // ​˘
    UCIS_SYM("doppelpunkt" , 0x02D0),                 // ​ ː​
    UCIS_SYM("sr" , 0x005c),                 // ​ ː​
    UCIS_SYM("srug"        , 0x00af, 0x005c, 0x005f, 0x0028, 0x30c4, 0x0029, 0x005f, 0x002f, 0x00af) // ¯\_(ツ)_/¯
);

void ucis_symbol_fallback (void) {
    send_unicode_string("💩");
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool lsft_pressed = false, rsft_pressed = false;
    static bool lctl_pressed = false, rctl_pressed = false;
    static bool lalt_pressed = false, ralt_pressed = false;
    static bool a_pressed = false, o_pressed = false, u_pressed = false;
    static bool s_pressed = false, e_pressed = false, z_pressed = false;

    switch (keycode)
    {
        // ----- UTF input mode

        case CK_UCIS:
            if (!record->event.pressed) ucis_start();
            break;

        // ----- umlauts

        case DE_A:
            a_pressed = record->event.pressed;
            break;
        case DE_O:
            o_pressed = record->event.pressed;
            break;
        case DE_U:
            u_pressed = record->event.pressed;
            break;
        case DE_S:
            s_pressed = record->event.pressed;
            break;
        case DE_E: // umlaut: ae, oe, ue --> ä, ö, ü; i.e. press 'a' and then press 'e' then release both is more convenient that "a+e" combo
            e_pressed = record->event.pressed;
            if (e_pressed) {
                if (a_pressed) {
                    unregister_code(DE_E);
                    register_code(KC_BSPC);
                    unregister_code(KC_BSPC);
                    register_code(DE_ADIA);
                    unregister_code(DE_ADIA);
                    return false;
                }
                if (o_pressed) {
                    unregister_code(DE_E);
                    register_code(KC_BSPC);
                    unregister_code(KC_BSPC);
                    register_code(DE_ODIA);
                    unregister_code(DE_ODIA);
                    return false;
                }
                if (u_pressed) {
                    unregister_code(DE_E);
                    register_code(KC_BSPC);
                    unregister_code(KC_BSPC);
                    register_code(DE_UDIA);
                    unregister_code(DE_UDIA);
                    return false;
                }
            }
            break;

        case DE_Z: // sz -> ß
            z_pressed = record->event.pressed;
            if (s_pressed && z_pressed) {
                unregister_code(DE_Z);
                register_code(KC_BSPC);
                unregister_code(KC_BSPC);
                register_code(DE_SS);
                unregister_code(DE_SS);
                return false;
            }
            break;

        // ----- parenthesis and brackets ({[]})

        case KC_LSFT: // rsft + lsft --> (
            lsft_pressed = record->event.pressed;
            if (lsft_pressed && rsft_pressed) {
                unregister_code16(KC_LSFT);
                unregister_code16(KC_RSFT);
                uprintf("(\n");
                register_code16(DE_LPRN);
                unregister_code16(DE_LPRN);
                return false;
            }
            break;
        case KC_RSFT: // lsft + rsft --> )
            rsft_pressed = record->event.pressed;
            if (lsft_pressed && rsft_pressed) {
                unregister_code16(KC_RSFT);
                unregister_code16(KC_LSFT);
                uprintf(")\n");
                register_code16(DE_RPRN);
                unregister_code16(DE_RPRN);
                return false;
            }
            break;

        case KC_LCTL: // rsft + lctl --> [
            lctl_pressed = record->event.pressed;
            if (rsft_pressed && lctl_pressed) {
                unregister_code(KC_LCTL);
                unregister_code(KC_RSFT);
                register_code16(DE_LBRC);
                unregister_code16(DE_LBRC);
                return false;
            }
            break;
        case KC_RCTL: // lsft + rclt --> ]
            rctl_pressed = record->event.pressed;
            if (lsft_pressed && rctl_pressed) {
                unregister_code(KC_RCTL);
                unregister_code(KC_LSFT);
                register_code16(DE_RBRC);
                unregister_code16(DE_RBRC);
                return false;
            }
            break;

        case KC_LALT: // rsft + lalt --> {
            lalt_pressed = record->event.pressed;
            if (rsft_pressed && lalt_pressed) {
                unregister_code(KC_LALT);
                unregister_code(KC_RSFT);
                register_code16(DE_LCBR);
                unregister_code16(DE_LCBR);
                return false;
            }
            break;
        case KC_RALT: // lsft + ralt --> }
            ralt_pressed = record->event.pressed;
            if (lsft_pressed && ralt_pressed) {
                unregister_code(KC_RALT);
                unregister_code(KC_LSFT);
                register_code16(DE_RCBR);
                unregister_code16(DE_RCBR);
                return false;
            }
            break;
    }
    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // keycodes that continue caps-word with shift applied
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // apply shift to next key
            return true;

        // keycodes that continue caps-word without shift applied
        case KC_1 ... KC_0:
        case KC_P1 ... KC_P0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case DE_MINS:
        case KC_LSFT:
        case KC_RSFT:
            return true;

        default:
            return false;  // deactivate caps-word
    }
}

/*
// tap dance input / double tap input

void dance_sftl_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_LSFT); }
    else {register_code(KC_CAPS); }
}

void dance_sftl_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_LSFT); }
    else { unregister_code(KC_CAPS); }
}

void dance_sftr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_RSFT); }
    else { register_code(KC_CAPS); }
}

void dance_sftr_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_RSFT); }
    else { unregister_code(KC_CAPS); }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_RSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sftl_finished, dance_sftl_reset),
    [TD_LSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sftr_finished, dance_sftr_reset),
};
*/
