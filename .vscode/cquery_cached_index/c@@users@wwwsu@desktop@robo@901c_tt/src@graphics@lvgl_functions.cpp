#include "main.h"
#include "lvgl_functions.h"
#include "../configure/config.h"

lv_obj_t * scr = lv_obj_create(NULL,NULL);
lv_obj_t * main_label =  lv_label_create(scr, NULL);

int autonNo = 1;

void setup(){
  lv_scr_load(scr);
  lv_label_set_recolor(main_label, true);
  lv_label_set_text(main_label, "#ff0000 Red Unprotected# #ffffff Auton#");
  lv_obj_align(main_label, NULL, LV_ALIGN_CENTER, 0, 0);
}


void switch_auton(){
  autonNo++;
  switch (autonNo){
    case 1:
      lv_label_set_text(main_label, "#ff0000 Red Unprotected# #ffffff Auton#");
      break;
    case 2:
      lv_label_set_text(main_label, "#0000ff Blue Unprotected# #ffffff Auton#");
      break;
    case 3:
      lv_label_set_text(main_label, "#ff0000 Red Protected# #ffffff Auton#");
      break;
    case 4:
      lv_label_set_text(main_label, "#0000ff Blue Protected# #ffffff Auton#");
      break;
    case 5:
      lv_label_set_text(main_label, "1 Point Push Forwards");
      break;
    case 6:
      lv_label_set_text(main_label, "Driver Skills");
      break;
    case 7:
      lv_label_set_text(main_label, "Programming Skills");
      break;
    case 8:
      lv_label_set_text(main_label, "#ff0000 Red Unprotected# #ffffff Auton#");
      autonNo = 1;
      break;

  }
}

void limit_detection_task(void *param){
  while(true){
    if(auton_limit.get_new_press() == 1){
      switch_auton();
    }
    pros::delay(50);
  }
}
