// LittlevGL Nova 12/9/2023
// tabview consisting of tabs --> button

#include "main.h"
#include "selector.h"

namespace selector {
    #define DEFAULT 1 //!important
    #define AUTONS "Close Side", "Far Side"

    const char * btnmMap[] = {AUTONS};

    int auton;
    int autonCount;

    lv_obj_t * tabView;
    lv_obj_t * blueAllianceButton;
    lv_obj_t * redAllianceButton;

    static lv_res_t initBlueAlliance(lv_obj_t * btnm, const char * txt) {
        for (int i = 0; i < autonCount; i++) {
            if (strcmp(txt, btnmMap[i]) == 0) {
                auton = i + 1;
            }
        }

        return LV_RES_OK;
    }

    static lv_res_t initRedAlliance(lv_obj_t * btnm, const char * txt) {
        for (int i = 0; i < autonCount; i++) {
            if (strcmp(txt, btnmMap[i]) == 0) {
                auton = -(i + 1);
            }
        }

        return LV_RES_OK;
    }

    int tabWatcher() {
        int activeTab = lv_tabview_get_tab_act(tabView);

        while (1) {
            int currentTab = lv_tabview_get_tab_act(tabView);

            if (currentTab != activeTab) {
                activeTab = currentTab;

                if (activeTab == 0) {
                    if (auton == 0) auton = 1;
                    auton = abs(auton);
                    lv_btnm_set_toggle(redAllianceButton, true, abs(auton) - 1);
                } else if (activeTab == 1) {
                    if (auton == 0) auton = -1;
                    auton = -abs(auton);
                    lv_btnm_set_toggle(blueAllianceButton, true, abs(auton) - 1);
                } else {
                    auton = 0;
                }
            }

            pros::delay(20);
        }
    }

    void init(const char **autons) {
        int i = 0;
        do {
            memcpy(&btnmMap[i], &autons[i], sizeof(&autons));
            i++;
        } while(strcmp(autons[i], "") != 0);

        autonCount = i;
        auton = DEFAULT;

        static lv_style_t tabViewStyle;
        lv_style_copy(&tabViewStyle, &lv_style_plain);
        tabViewStyle.body.main_color = LV_COLOR_BLACK;
        tabViewStyle.text.color = LV_COLOR_WHITE;
        tabViewStyle.body.border.color = LV_COLOR_WHITE;
        tabViewStyle.body.border.width = 2;

        lv_obj_t * tabView = lv_tabview_create(lv_scr_act(), NULL);
        lv_tabview_set_style(tabView, LV_TABVIEW_STYLE_BG, &tabViewStyle);

        lv_obj_t * blueAllianceTab = lv_tabview_add_tab(tabView, "Blue");
        lv_obj_t * redAllianceTab = lv_tabview_add_tab(tabView, "Red");

        static lv_style_t blueButtonStyle;
        lv_style_copy(&blueButtonStyle, &lv_style_plain);
        blueButtonStyle.body.main_color = LV_COLOR_BLACK;
        blueButtonStyle.body.border.color = LV_COLOR_BLUE;
        blueButtonStyle.body.border.width = 2;
        blueButtonStyle.text.color = LV_COLOR_BLUE;

        static lv_style_t redButtonStyle;
        lv_style_copy(&redButtonStyle, &lv_style_plain);
        redButtonStyle.body.main_color = LV_COLOR_BLACK;
        redButtonStyle.body.border.color = LV_COLOR_RED;
        redButtonStyle.body.border.width = 2;
        redButtonStyle.text.color = LV_COLOR_RED;

        lv_obj_t * blueAllianceButtons = lv_btnm_create(blueAllianceTab, NULL);
        lv_btnm_set_map(blueAllianceButtons, btnmMap);
        lv_btnm_set_action(blueAllianceButtons, initBlueAlliance);
        lv_obj_set_size(blueAllianceButtons, 450, 50);
        lv_obj_set_pos(blueAllianceButtons, 0, 100);
        lv_obj_align(blueAllianceButtons, NULL, LV_ALIGN_CENTER, 0, 0);
        lv_btnm_set_style(blueAllianceButtons, LV_BTNM_STYLE_BG, &blueButtonStyle);

        lv_obj_t * redAllianceButtons = lv_btnm_create(redAllianceTab, NULL);
        lv_btnm_set_map(redAllianceButtons, btnmMap);
        lv_btnm_set_action(redAllianceButtons, initRedAlliance);
        lv_obj_set_size(redAllianceButtons, 450, 50);
        lv_obj_set_pos(redAllianceButtons, 0, 100);
        lv_obj_align(redAllianceButtons, NULL, LV_ALIGN_CENTER, 0, 0);
        lv_btnm_set_style(redAllianceButtons, LV_BTNM_STYLE_BG, &redButtonStyle);

        pros::Task tabWatcher_task(tabWatcher);
    }
}