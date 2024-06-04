//----------------------------------------------------------------------------
// OS-Railway - Remote Control
// Copyright (C) 2023-2024 Peter Siegmund (https://mars3142.dev)
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
#include "launch_screen.h"

#include "theme.h"
#include "lv_i18n/lv_i18n.h"
#include "search_screen.h"

LV_IMG_DECLARE(os_railway_icon_lvgl);

namespace LaunchScreen
{
    lv_obj_t *screen;

    void timer_xcb(lv_timer_t *timer)
    {
        lv_timer_del(timer);
        SearchScreen::show();
    }

    void start_timer()
    {
        lv_timer_t *timer = lv_timer_create(timer_xcb, 2000, NULL);
    }

    void show()
    {
        screen = lv_obj_create(NULL);
        lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_bg_color(screen, backgroundColor, 0);

        auto *logo = lv_img_create(screen);
        lv_img_set_src(logo, &os_railway_icon_lvgl);
        lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0);

        auto *label = lv_label_create(screen);
        lv_label_set_text(label, _("appName"));
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -25);
        lv_disp_load_scr(screen);

        start_timer();
    }
}
