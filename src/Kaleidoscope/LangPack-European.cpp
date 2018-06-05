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

typedef enum {
  AA,
  AU,
  AR,
  AG,
  OA,
  OU,
  ODA,
  OG,
  EA,
  EU,
  EG,
  UA,
  UU,
  UDA,
  UG,
  IA,
  IU,
  IG,
  YU,
  CD,
  SHS,
  ENE,
} EUSymbol;

namespace kaleidoscope {
namespace language {

static void tap_key(Key key) {
  handleKeyswitchEvent(key, UNKNOWN_KEYSWITCH_LOCATION, IS_PRESSED | INJECTED);
  hid::sendKeyboardReport();
  handleKeyswitchEvent(key, UNKNOWN_KEYSWITCH_LOCATION, WAS_PRESSED | INJECTED);
  hid::sendKeyboardReport();
}

EventHandlerResult European::onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t keyState) {
  if (mapped_key.raw < INTL_FIRST || mapped_key.raw > INTL_LAST)
    return EventHandlerResult::OK;

  if (!keyToggledOn(keyState)) {
    return EventHandlerResult::EVENT_CONSUMED;
  }

  bool need_shift = hid::isModifierKeyActive(Key_LeftShift) ||
                    ::OneShot.isModifierActive(Key_LeftShift);

  tap_key(compose_key);

  EUSymbol symbol = (EUSymbol)(mapped_key.raw - INTL_FIRST);
  Key accent;
  uint8_t kc = 0;

  accent.flags = KEY_FLAGS;
  accent.keyCode = Key_Quote.keyCode;

  switch (symbol) {
  case AA:
    kc = Key_A.keyCode;
    break;
  case AU:
    kc = Key_A.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case AR:
    kc = Key_A.keyCode;
    accent = Key_O;
    break;
  case AG:
    kc = Key_A.keyCode;
    accent = Key_Backtick;
    break;

  case OA:
    kc = Key_O.keyCode;
    break;
  case OU:
    kc = Key_O.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case ODA:
    kc = Key_O.keyCode;
    accent.raw = Key_Equals.raw;
    break;
  case OG:
    kc = Key_O.keyCode;
    accent = Key_Backtick;
    break;

  case EA:
    kc = Key_E.keyCode;
    break;
  case EU:
    kc = Key_E.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case EG:
    kc = Key_E.keyCode;
    accent = Key_Backtick;
    break;

  case UA:
    kc = Key_U.keyCode;
    break;
  case UU:
    kc = Key_U.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case UDA:
    kc = Key_U.keyCode;
    accent.raw = Key_Equals.raw;
    break;
  case UG:
    kc = Key_U.keyCode;
    accent = Key_Backtick;
    break;

  case IA:
    kc = Key_I.keyCode;
    break;
  case IU:
    kc = Key_I.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case IG:
    kc = Key_I.keyCode;
    accent = Key_Backtick;
    break;

  case YU:
    kc = Key_Y.keyCode;
    accent.flags |= SHIFT_HELD;
    break;

  case CD:
    kc = Key_C.keyCode;
    accent = Key_Period;
    break;

  case SHS:
    kc = Key_S.keyCode;
    accent = Key_S;
    break;

  case ENE:
    kc = Key_N.keyCode;
    accent = Key_Backtick;
    accent.flags |= SHIFT_HELD;
    break;
  }

  if (accent.flags & SHIFT_HELD)
    handleKeyswitchEvent(Key_LeftShift, UNKNOWN_KEYSWITCH_LOCATION, IS_PRESSED | INJECTED);
  else
    handleKeyswitchEvent(Key_LeftShift, UNKNOWN_KEYSWITCH_LOCATION, WAS_PRESSED | INJECTED);
  hid::sendKeyboardReport();

  tap_key(accent);

  if (need_shift)
    handleKeyswitchEvent(Key_LeftShift, UNKNOWN_KEYSWITCH_LOCATION, IS_PRESSED | INJECTED);
  else
    handleKeyswitchEvent(Key_LeftShift, UNKNOWN_KEYSWITCH_LOCATION, WAS_PRESSED | INJECTED);

  mapped_key = kc;

  hid::sendKeyboardReport();

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
