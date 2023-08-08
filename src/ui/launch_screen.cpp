#include "ui/launch_screen.h"

#include <lvgl.h>

lv_obj_t *ui_SplashScreen;

void ui_LaunchScreen_open()
{
    // Create a screen
    ui_SplashScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SplashScreen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_SplashScreen, lv_color_make(0x78, 0x94, 0xa7), 0);

    // Create a label
    lv_obj_t *label = lv_label_create(ui_SplashScreen);
    lv_label_set_text(label, "Hello world!");

    // Align the label to the center
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0);

    lv_disp_load_scr(ui_SplashScreen);
}
