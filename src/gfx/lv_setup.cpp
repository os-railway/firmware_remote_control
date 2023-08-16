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
#include "gfx/lv_setup.h"

#include <lvgl.h>
#include <gfx/lgfx.h>

#include "lv_conf.h"

#define LV_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

LGFX tft;

struct Timer
{
    unsigned long time;
    long duration = 5000;
    bool active;
};

Timer screenTimer;

void lv_handler()
{
    static uint32_t previousUpdate = 0;
    static uint32_t interval = 0;

    if (millis() - previousUpdate > interval)
    {
        previousUpdate = millis();
        interval = lv_timer_handler(); // Update the UI
    }
}

void check_display_off()
{
    if (screenTimer.active && millis() - screenTimer.time > screenTimer.duration)
    {
        tft.setBrightness(0);
        screenTimer.active = false;
    }
}

void set_screen_timer(unsigned long time)
{
    tft.setBrightness(255);
    screenTimer.time = time;
    screenTimer.active = true;
}

void flush_cb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void touch_cb(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    uint16_t touchX, touchY;
    bool touched = tft.getTouch(&touchX, &touchY);
    if (touched)
    {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
        set_screen_timer(millis());
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}

void print_cb(const char *buf)
{
    ESP_LOGD("lv_log", "%s", buf);
}

void lv_begin()
{
    tft.init();
    tft.initDMA();
    tft.startWrite();
    tft.setRotation(1);

#if LV_LOG_PRINTF
    lv_log_register_print_cb(print_cb);
#endif

    lv_init();

    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t *buf1, *buf2;
    buf1 = (lv_color_t *)heap_caps_malloc(LV_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM);
    buf2 = (lv_color_t *)heap_caps_malloc(LV_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM);
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, LV_BUF_SIZE);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = flush_cb;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touch_cb;
    lv_indev_drv_register(&indev_drv);
}
