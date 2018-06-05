/* -*- mode: c++ -*-
 * Kaleidoscope-LangPack-European -- Support for select EU languages
 * Copyright (C) 2016, 2017, 2018  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include <Kaleidoscope-LangPack-European.h>
#include <Kaleidoscope-OneShot.h>

namespace kaleidoscope {
namespace language {

static void tap_key(Key key) {
  hid::pressKey(key);
  hid::sendKeyboardReport();
  hid::releaseKey(key);
  hid::sendKeyboardReport();
}

EventHandlerResult European::onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t keyState) {
  if (mapped_key.raw < INTL_FIRST || mapped_key.raw > INTL_LAST)
    return EventHandlerResult::OK;

  if (!keyToggledOn(keyState)) {
    return EventHandlerResult::EVENT_CONSUMED;
  }

  bool need_shift = hid::wasModifierKeyActive(Key_LeftShift) ||
                    ::OneShot.isModifierActive(Key_LeftShift);

  tap_key(compose_key);

  Key accent;
  uint8_t kc = 0;

  accent.flags = KEY_FLAGS;
  accent.keyCode = Key_Quote.keyCode;

  switch (mapped_key.raw) {
  case INTL_AACUTE:
    kc = Key_A.keyCode;
    break;
  case INTL_AUMLAUT:
    kc = Key_A.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case INTL_ARING:
    kc = Key_A.keyCode;
    accent = Key_O;
    break;
  case INTL_AGRAVE:
    kc = Key_A.keyCode;
    accent = Key_Backtick;
    break;

  case INTL_OACUTE:
    kc = Key_O.keyCode;
    break;
  case INTL_OUMLAUT:
    kc = Key_O.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case INTL_ODACUTE:
    kc = Key_O.keyCode;
    accent.raw = Key_Equals.raw;
    break;
  case INTL_OGRAVE:
    kc = Key_O.keyCode;
    accent = Key_Backtick;
    break;

  case INTL_EACUTE:
    kc = Key_E.keyCode;
    break;
  case INTL_EUMLAUT:
    kc = Key_E.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case INTL_EGRAVE:
    kc = Key_E.keyCode;
    accent = Key_Backtick;
    break;

  case INTL_UACUTE:
    kc = Key_U.keyCode;
    break;
  case INTL_UUMLAUT:
    kc = Key_U.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case INTL_UDACUTE:
    kc = Key_U.keyCode;
    accent.raw = Key_Equals.raw;
    break;
  case INTL_UGRAVE:
    kc = Key_U.keyCode;
    accent = Key_Backtick;
    break;

  case INTL_IACUTE:
    kc = Key_I.keyCode;
    break;
  case INTL_IUMLAUT:
    kc = Key_I.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case INTL_IGRAVE:
    kc = Key_I.keyCode;
    accent = Key_Backtick;
    break;

  case INTL_YUMLAUT:
    kc = Key_Y.keyCode;
    accent.flags |= SHIFT_HELD;
    break;

  case INTL_CEDILLA:
    kc = Key_C.keyCode;
    accent = Key_Period;
    break;

  case INTL_SS:
    kc = Key_S.keyCode;
    accent = Key_S;
    break;

  case INTL_ENE:
    kc = Key_N.keyCode;
    accent = Key_Backtick;
    accent.flags |= SHIFT_HELD;
    break;
  }

  if (accent.flags & SHIFT_HELD)
    hid::pressKey(Key_LeftShift);
  else
    hid::releaseKey(Key_LeftShift);

  tap_key(accent);

  if (need_shift)
    hid::pressKey(Key_LeftShift);
  else
    hid::releaseKey(Key_LeftShift);

  hid::sendKeyboardReport();

  mapped_key = {kc, KEY_FLAGS};

  return EventHandlerResult::OK;
}

// Legacy V1 API
#if KALEIDOSCOPE_ENABLE_V1_PLUGIN_API
void European::begin() {
  Kaleidoscope.useEventHandlerHook(legacyEventHandler);
}

Key European::legacyEventHandler(Key mapped_key, byte row, byte col, uint8_t key_state) {
  EventHandlerResult r = ::LangPack_EU.onKeyswitchEvent(mapped_key, row, col, key_state);
  if (r == EventHandlerResult::OK)
    return mapped_key;
  return Key_NoKey;
}
#endif

}
}

kaleidoscope::language::European LangPack_EU;
