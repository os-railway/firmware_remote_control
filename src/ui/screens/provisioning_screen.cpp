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
#include "provisioning_screen.h"

ProvisioningScreen::ProvisioningScreen()
{
    screen = lv_obj_create(NULL);

    lv_color_t bg_color = lv_palette_lighten(LV_PALETTE_LIGHT_BLUE, 5);
    lv_color_t fg_color = lv_palette_darken(LV_PALETTE_BLUE, 4);

    lv_obj_t *qr = lv_qrcode_create(screen, 150, fg_color, bg_color);

    const char *data = "{\"ver\":\"v2\",\"name\":\"OSRW_RC\",\"pop\":\"a1000318\",\"transport\":\"ble\"}";
    lv_qrcode_update(qr, data, strlen(data));
    lv_obj_center(qr);

    lv_obj_set_style_border_color(qr, bg_color, 0);
    lv_obj_set_style_border_width(qr, 5, 0);
}

void ProvisioningScreen::show()
{
    lv_disp_load_scr(screen);
}
