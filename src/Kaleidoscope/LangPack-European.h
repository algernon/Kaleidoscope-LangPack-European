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

#pragma once

#include <Kaleidoscope.h>
#include <Kaleidoscope-Ranges.h>

namespace kaleidoscope {
namespace language {

enum {
  INTL_FIRST = ranges::KALEIDOSCOPE_SAFE_START,

  INTL_AACUTE = INTL_FIRST,
  INTL_AGRAVE,
  INTL_ARING,
  INTL_AOGONEK,
  INTL_AUMLAUT,

  INTL_CACUTE,
  INTL_CEDILLA,

  INTL_EACUTE,
  INTL_EGRAVE,
  INTL_EOGONEK,
  INTL_EUMLAUT,

  INTL_IACUTE,
  INTL_IGRAVE,
  INTL_IOGONEK,
  INTL_IUMLAUT,

  INTL_LSTROKE,

  INTL_NACUTE,
  INTL_ENE,

  INTL_OACUTE,
  INTL_ODACUTE,
  INTL_OGRAVE,
  INTL_OOGONEK,
  INTL_OUMLAUT,

  INTL_SACUTE,
  INTL_SS,

  INTL_UACUTE,
  INTL_UDACUTE,
  INTL_UGRAVE,
  INTL_UOGONEK,
  INTL_UUMLAUT,

  INTL_YUMLAUT,

  INTL_ZACUTE,
  INTL_ZODOT,

  INTL_LAST = INTL_ZODOT,
};

#define INTL(n) (Key){.raw = kaleidoscope::language::INTL_ ## n}

class European : public kaleidoscope::Plugin {
 public:
  European(void) {}

  Key compose_key = Key_RightAlt;

  EventHandlerResult onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t keyState);

#if KALEIDOSCOPE_ENABLE_V1_PLUGIN_API
 protected:
  void begin();
  static Key legacyEventHandler(Key mapped_key, byte row, byte col, uint8_t key_state);
#endif
};

}
}

extern kaleidoscope::language::European LangPack_EU;
