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
#include "time_widget.h"

#include <string>
#include <time.h>

lv_obj_t *time_widget;
lv_timer_t *time_widget_timer;

void time_widget_update(lv_timer_t *timer)
{
    lv_obj_t *label = (lv_obj_t *)timer->user_data;

    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    std::string weekday[] = LV_CALENDAR_DEFAULT_DAY_NAMES;
    lv_label_set_text_fmt(label, "%s %02d:%02d:%02d\n%d-%02d-%02d", weekday[timeinfo.tm_wday].c_str(), timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
}

void time_widget_init(lv_coord_t x, lv_coord_t y)
{
    if (time_widget != NULL)
    {
        return;
    }

    time_widget = lv_obj_create(lv_layer_top());
    lv_obj_align(time_widget, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(time_widget, 200);
    lv_obj_set_style_bg_opa(time_widget, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_opa(time_widget, LV_OPA_TRANSP, 0);

    lv_obj_t *label = lv_label_create(time_widget);
    lv_obj_set_pos(label, -10, -10);

    time_widget_timer = lv_timer_create(time_widget_update, 1000, (void *)label);
    time_widget_update(time_widget_timer);
}

void time_widget_dispose()
{
    if (time_widget == NULL)
    {
        return;
    }

    lv_timer_del(time_widget_timer);
    time_widget_timer = NULL;

    lv_obj_del(time_widget);
    time_widget = NULL;
}
