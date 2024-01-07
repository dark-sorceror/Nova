// LittlevGL Nova 12/9/2023
// tabview consisting of tabs --> button

#include "display/lv_core/lv_obj.h"
#include "display/lv_misc/lv_color.h"
#include "main.h"
#include "selector.h"

namespace selector {
    int auton;

    static lv_res_t btn_click_action(lv_obj_t * btn) {
        uint8_t id = lv_obj_get_free_num(btn);

        auton = id;

        return LV_RES_OK; /*Return OK if the button is not deleted*/
    }

    void init() {
        static lv_style_t buttonStyle;
        lv_style_copy(&buttonStyle, &lv_style_plain);
        buttonStyle.body.main_color = LV_COLOR_BLACK;
        buttonStyle.body.border.color = LV_COLOR_BLACK;
        buttonStyle.body.border.width = 2;
        buttonStyle.text.color = LV_COLOR_GREEN;

        lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
        lv_label_set_text(label, "Auton Selection");
        lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

        lv_obj_t * farSide = lv_btn_create(lv_scr_act(), NULL);
        lv_cont_set_fit(farSide, true, true);
        lv_obj_align(farSide, label, LV_ALIGN_OUT_TOP_LEFT, 0, 100);
        lv_obj_set_free_num(farSide, 1);   /*Set a unique number for the button*/
        lv_btn_set_action(farSide, LV_BTN_ACTION_CLICK, btn_click_action);
        label = lv_label_create(farSide, NULL);
        lv_label_set_text(label, "Far Side");
        lv_btn_set_style(farSide, LV_BTNM_STYLE_BG, &buttonStyle);

        lv_obj_t * closeSide = lv_btn_create(lv_scr_act(), NULL);
        lv_cont_set_fit(closeSide, true, true);
        lv_obj_align(closeSide, label, LV_ALIGN_OUT_TOP_MID, 0, 100);
        lv_obj_set_free_num(closeSide, 2);   /*Set a unique number for the button*/
        lv_btn_set_action(closeSide, LV_BTN_ACTION_CLICK, btn_click_action);
        label = lv_label_create(closeSide, NULL);
        lv_label_set_text(label, "Close Side");
        lv_btn_set_style(closeSide, LV_BTNM_STYLE_BG, &buttonStyle);

        lv_obj_t * skills = lv_btn_create(lv_scr_act(), NULL);
        lv_cont_set_fit(skills, true, true);
        lv_obj_align(skills, label, LV_ALIGN_OUT_TOP_RIGHT, 20, 100);
        lv_obj_set_free_num(skills, 3);   /*Set a unique number for the button*/
        lv_btn_set_action(skills, LV_BTN_ACTION_CLICK, btn_click_action);
        label = lv_label_create(skills, NULL);
        lv_label_set_text(label, "Skills");
        lv_btn_set_style(skills, LV_BTNM_STYLE_BG, &buttonStyle);
    }
}