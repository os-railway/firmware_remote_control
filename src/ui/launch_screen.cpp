#include "ui/launch_screen.h"

#include <lvgl.h>
#include "lv_i18n/lv_i18n.h"

void ui_LaunchScreen_open()
{
    auto ui_SplashScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SplashScreen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_SplashScreen, lv_color_make(0x78, 0x94, 0xa7), 0);

    LV_IMG_DECLARE(os_railway_icon_lvgl);
    auto *img = lv_img_create(ui_SplashScreen);
    lv_img_set_src(img, &os_railway_icon_lvgl);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    auto *label = lv_label_create(ui_SplashScreen);
    lv_label_set_text(label, _("appName"));
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -25);

    lv_disp_load_scr(ui_SplashScreen);
}
