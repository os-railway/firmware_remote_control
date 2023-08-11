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
#include "status_bar_widget.h"

#include <lvgl.h>

#include "time_widget.h"

lv_obj_t *status_bar_widget;

void status_bar_widget_init()
{
    status_bar_widget = lv_obj_create(lv_layer_top());
    time_widget_init(10, 10);
}

void status_bar_widget_dispose()
{
    time_widget_dispose();
    lv_obj_del(status_bar_widget);
    status_bar_widget = NULL;
}