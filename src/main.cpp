//----------------------------------------------------------------------------
// OS-Railway - Remote Control
// Copyright (C) 2023 Peter Siegmund (https://mars3142.dev)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//----------------------------------------------------------------------------
#include <Arduino.h>

#include "gfx/lv_setup.h"
#include "lv_i18n/lv_i18n.h"
#include "ui/launch_screen.h"

void setup()
{
  lv_i18n_init(lv_i18n_language_pack);
  lv_i18n_set_locale("de-DE");

  lv_begin();

  LaunchScreen launchScreen;
  launchScreen.show();
}

void loop()
{
  lv_handler();
}
