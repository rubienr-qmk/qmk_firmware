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

// ----- tap dance input / double tap input
#if defined(TAP_DANCE_ENABLE)
enum { TD_ADIA, TD_ODIA, TD_UDIA, TD_SS };
#endif // TAP_DANCE_ENABLE

// ----- combo input
#if defined(COMBO_ENABLE)

enum combo_events { CB_AE, CB_OE, CB_UE, CB_SZ, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ae_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM sz_combo[] = {KC_S, DE_Z, COMBO_END};

combo_t key_combos[] = {
    [CB_AE] = COMBO(ae_combo, DE_ADIA),
    [CB_OE] = COMBO(oe_combo, DE_ODIA),
    [CB_UE] = COMBO(ue_combo, DE_UDIA),
    [CB_SZ] = COMBO(sz_combo, DE_SS),
};
#endif // COMBO_ENABLE

// ----- utf8 ucis input
#if defined(UCIS_ENABLE)

enum custom_keycodes_t {
    UC_START = SAFE_RANGE,
    PR_EMOJI,
};

/*
function x() {
    # converts utf string to utf hex code
    # usage:
    # $x "¯\_(ツ)_/¯"
    # str: '¯\_(ツ)_/¯' -> hex:
    # 0xAF, 0x5C, 0x5F, 0x28, 0x30C4, 0x29, 0x5F, 0x2F, 0xAF,

    foo=$1
    echo "str: '$1' -> hex:"
    for (( i=0; i<${#foo}; i++ )); do
        hex=$(echo -en "${foo:$i:1}" | iconv -f utf8 -t ucs-4 | xxd -ps)
        to_upper=$(bash -c "hex=$hex"' ; echo -en ${hex^^}')
        no_zeroes=$(echo "obase=16; ibase=16; $to_upper" | bc)
        echo -en "0x$no_zeroes, ";
    done
}
 */
// clang-format off
const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop",    0x1F4A9), // 💩
    UCIS_SYM("grin",    0x1F600), // 😀
    UCIS_SYM("grin2",   0x1F601), // 😁
    UCIS_SYM("smile",   0x1F642), // 🙂
    UCIS_SYM("smile2",  0x1F60A), // 😊
    UCIS_SYM("smile3",  0x1F604), // 😄
    UCIS_SYM("smile4",  0x295, 0x298, 0x305, 0x35C, 0x298, 0x305, 0x29), // ʕʘ̅͜ʘ̅ʔ
    UCIS_SYM("rofl",    0x1F923), // 🤣
    UCIS_SYM("joy",     0x1F602), // 😂
    UCIS_SYM("kiss",    0x1F618), // 😘
    UCIS_SYM("heart",   0x1F60D), // 😘
    UCIS_SYM("sleep",   0x1F634), // 😴
    UCIS_SYM("tongue",  0x1F60B), // 😋
    UCIS_SYM("sunglass",0x1F60E), // 😎
    UCIS_SYM("look",    0xCA0, 0x5F, 0xCA0), // ಠ_ಠ
    UCIS_SYM("no",      0x1F648, 0x1F649, 0x1F64A), // monkey, no-see -hear -speak
    UCIS_SYM("shrug",   0xAF, 0x5C, 0x5F, 0x28, 0x30C4, 0x29, 0x5F, 0x2F, 0xAF), // ¯\_(ツ)_/¯
    UCIS_SYM("flip",    0x28, 0x256F, 0xFF9F, 0x2E, 0x20, 0xFF9F, 0xFF09, 0x256F, 0xFE35, 0x20, 0x253B, 0x2501, 0x253B), // (╯ﾟ. ﾟ）╯︵ ┻━┻
    UCIS_SYM("flip2",   0x28, 0x256F, 0x20, 0x360, 0xB0, 0x25DE, 0x20, 0xB0, 0xFF09, 0x256F, 0xFE35, 0x20, 0x253B, 0x2501, 0x253B), // (╯ ͠°◞ °）╯︵ ┻━┻
    UCIS_SYM("flip3",   0x28, 0x256F, 0x2035, 0x25A1, 0x2032, 0x29, 0x256F, 0xFE35, 0x2534, 0x2500, 0x2534), // (╯‵□′)╯︵┴─┴
    UCIS_SYM("flip4",   0x28, 0x30CE, 0xCA0, 0x76CA, 0xCA0, 0x29, 0x30CE, 0x5F61, 0x253B, 0x2501, 0x253B), // (ノಠ益ಠ)ノ彡┻━┻
    UCIS_SYM("ekury",   0x306), // ˘
    UCIS_SYM("dpunkt",  0x2D0) // ː
);
// clang-format on

void ucis_symbol_fallback(void) {
    send_unicode_string("💩");
}

#endif // UCIS_ENABLE

// void ucis_start_user(void) {}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool lsft_pressed = false, rsft_pressed = false;
    static bool lctl_pressed = false, rctl_pressed = false;
    static bool lalt_pressed = false, ralt_pressed = false;

    switch (keycode) {
            // ----- UTF input mode

        case UC_START:
            if (record->event.pressed) {
                // register_unicode(0x2328); // ⌨
                // ucis_start();
            } else {
                ucis_start();
            }
            break;

            // ----- print known emoji names

        case PR_EMOJI:
            if (!record->event.pressed) {
                for (size_t idx = 0; NULL != ucis_symbol_table[idx].mnemonic; idx++) {
                    send_string(ucis_symbol_table[idx].mnemonic);
                    send_char(' ');
                    wait_ms(UNICODE_TYPE_DELAY);
                    register_ucis(idx);
                    wait_ms(UNICODE_TYPE_DELAY);
                    send_char('\n');
                }
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
        case DE_ADIA:
        case DE_ODIA:
        case DE_UDIA:
            add_weak_mods(MOD_BIT(KC_LSFT)); // apply shift to next key
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
        case DE_SS:
            return true;

        default:
            return false; // deactivate caps-word
    }
}

// tap dance input / double tap input
#if defined(TAP_DANCE_ENABLE)

typedef struct td_user_data_t {
    const uint16_t kc_a;
    const uint16_t kc_o;
    const uint16_t kc_u;
    const uint16_t kc_s;
} td_user_data_t;
td_user_data_t td_user_data = {.kc_a = KC_A, .kc_o = KC_O, .kc_u = KC_U, .kc_s = KC_S};

void dance_uml_each(tap_dance_state_t *state, void *user_data) {
    if (NULL == user_data) return;
    const uint16_t key_code = *((uint16_t *)user_data);
    register_code(key_code);
    unregister_code(key_code);
}

void dance_uml_finished(tap_dance_state_t *state, void *user_data) {
    if (NULL == user_data) return;
    const uint16_t key_code = *((uint16_t *)user_data);

    if (state->count == 2) {
        switch (key_code) {
            case KC_A:
            case KC_O:
            case KC_U:
            case KC_S:
                register_code(KC_BSPC);
                unregister_code(KC_BSPC);
                break;
        }
        switch (key_code) {
            case KC_A:
                register_code(DE_ADIA);
                unregister_code(DE_ADIA);
                break;

            case KC_O:
                register_code(DE_ODIA);
                unregister_code(DE_ODIA);
                break;

            case KC_U:
                register_code(DE_UDIA);
                unregister_code(DE_UDIA);
                break;

            case KC_S:
                register_code(DE_SS);
                unregister_code(DE_SS);
                break;
        }
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ADIA] = {.fn = {dance_uml_each, dance_uml_finished, NULL}, .user_data = (void *)&td_user_data.kc_a},
    [TD_ODIA] = {.fn = {dance_uml_each, dance_uml_finished, NULL}, .user_data = (void *)&td_user_data.kc_o},
    [TD_UDIA] = {.fn = {dance_uml_each, dance_uml_finished, NULL}, .user_data = (void *)&td_user_data.kc_u},
    [TD_SS]   = {.fn = {dance_uml_each, dance_uml_finished, NULL}, .user_data = (void *)&td_user_data.kc_s},
};

#endif // TAP_DANCE_ENABLE

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        dprintf("set layer=%s\n", (!active ? "DE_BASE" : "US_BASE"));
        default_layer_set(1UL << (!active ? DE_BASE : US_BASE));
        return false;
    }
    return true;
}
