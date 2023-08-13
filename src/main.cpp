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

#include <esp32-hal-log.h>

#include "gfx/lv_setup.h"
#include "lv_i18n/lv_i18n.h"
#include "ui/screens/launch_screen.h"

void setup()
{
  esp_log_level_set("*", ESP_LOG_VERBOSE);

  lv_i18n_init(lv_i18n_language_pack);
  lv_i18n_set_locale("de-DE");

  lv_begin();

  lv_disp_t *dispp = lv_disp_get_default();
  lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_AMBER), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
  lv_disp_set_theme(dispp, theme);

  launch_screen_show();
}

void loop()
{
  lv_handler();
}
