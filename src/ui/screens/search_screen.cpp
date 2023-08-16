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
#include "search_screen.h"

#include "theme.h"
#include "../widgets/status_bar_widget.h"

namespace SearchScreen
{
#define ITEM_CNT 200

    lv_obj_t *search_screen;
    lv_obj_t *search_data_table;

    static void draw_event_cb(lv_event_t *e)
    {
        auto *obj = lv_event_get_target(e);
        auto *dsc = lv_event_get_draw_part_dsc(e);

        if (dsc->part == LV_PART_ITEMS)
        {
            bool chk = lv_table_has_cell_ctrl(obj, dsc->id, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);

            lv_draw_rect_dsc_t rect_dsc;
            lv_draw_rect_dsc_init(&rect_dsc);
            rect_dsc.bg_color = chk ? lv_theme_get_color_primary(obj) : lv_palette_lighten(LV_PALETTE_GREY, 2);
            rect_dsc.radius = LV_RADIUS_CIRCLE;

            lv_area_t sw_area;
            sw_area.x1 = dsc->draw_area->x2 - 50;
            sw_area.x2 = sw_area.x1 + 40;
            sw_area.y1 = dsc->draw_area->y1 + lv_area_get_height(dsc->draw_area) / 2 - 10;
            sw_area.y2 = sw_area.y1 + 20;
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &sw_area);

            rect_dsc.bg_color = lv_color_white();
            if (chk)
            {
                sw_area.x2 -= 2;
                sw_area.x1 = sw_area.x2 - 16;
            }
            else
            {
                sw_area.x1 += 2;
                sw_area.x2 = sw_area.x1 + 16;
            }
            sw_area.y1 += 2;
            sw_area.y2 -= 2;
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &sw_area);
        }
    }

    static void change_event_cb(lv_event_t *e)
    {
        lv_obj_t *obj = lv_event_get_target(e);
        uint16_t col;
        uint16_t row;
        lv_table_get_selected_cell(obj, &row, &col);
        bool chk = lv_table_has_cell_ctrl(obj, row, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
        if (chk)
            lv_table_clear_cell_ctrl(obj, row, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
        else
            lv_table_add_cell_ctrl(obj, row, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
    }

    void show()
    {
        search_screen = lv_obj_create(NULL);
        lv_obj_clear_flag(search_screen, LV_OBJ_FLAG_SCROLLABLE);

        search_data_table = lv_table_create(search_screen);
        lv_obj_set_size(search_data_table, SCREEN_WIDTH, SCREEN_HEIGHT);

        lv_table_set_col_width(search_data_table, 0, SCREEN_WIDTH - 3);
        lv_table_set_row_cnt(search_data_table, ITEM_CNT); /*Not required but avoids a lot of memory reallocation lv_table_set_set_value*/
        lv_table_set_col_cnt(search_data_table, 1);

        /*Don't make the cell pressed, we will draw something different in the event*/
        lv_obj_remove_style(search_data_table, NULL, LV_PART_ITEMS | LV_STATE_PRESSED);

        uint32_t i;
        for (i = 0; i < ITEM_CNT; i++)
        {
            lv_table_set_cell_value_fmt(search_data_table, i, 0, "Item\n%" LV_PRIu32, i + 1);
        }

        lv_obj_add_event_cb(search_data_table, draw_event_cb, LV_EVENT_DRAW_PART_END, NULL);
        lv_obj_add_event_cb(search_data_table, change_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

        lv_disp_load_scr(search_screen);
    }
}
