#include "lvgl_functions.h"
#include "../configure/config.h"

static lv_res_t btn_click_action(lv_obj_t * btn);
static lv_res_t auton_btn_click_action(lv_obj_t * btn);
static lv_res_t confirm_btn_click_action(lv_obj_t * btn);
static lv_res_t settings_btn_click_action(lv_obj_t * btn);
static lv_res_t config_btn_click_action(lv_obj_t * btn);
//static lv_res_t roller_select_action(lv_obj_t * id);
static lv_res_t mbox_apply_action(lv_obj_t * mbox, const char * txt);
static lv_res_t ddlist_action(lv_obj_t * ddlist);
static lv_res_t change_ports_action1(lv_obj_t * btn);
static lv_res_t config_confirm_btn_click_action(lv_obj_t * btn);

int ports[] = {frontL_port, frontR_port, backL_port, backR_port,
  puncher_port, angler_port, intake_port, flipper_port};
int current_screen = 1;
int current_auton = 3;
int previous_auton = current_auton;
int to_set_auton;
int motor_to_change;

char auton_indicator[14] = "Current Auton";
char red1[20] = "Back, w/ Park";
char red2[20] = "Back Greed";
char red3[20] = "Front Nopark";
char red4[20] = "NO TOUCH";
char red5[20] = "None";
char red6[20] = "None";
char blue1[20] = "Back, w/ Park";
char blue2[20] = "Back Greed";
char blue3[22] = "Front Nopark";
char blue4[22] = "NO TOUCH";
char blue5[20] = "None";
char blue6[20] = "None";
char prog1[15] = "Skills:yerite";
char prog2[13] = "Skills: 99pt";
char prog3[13] = "Skills: meh";


void const_buttons(){
  /* ------ Back Button ------*/
  lv_obj_t * back_text = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(back_text, SYMBOL_LEFT);
  lv_obj_align(back_text, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 20, -20);

  lv_obj_t * back_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(back_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(back_button, 30);        /*Set a fix height*/
  lv_obj_set_width(back_button, 30);        /*Set a fix height*/
  lv_obj_align(back_button, back_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(back_button, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(back_button, LV_BTN_ACTION_CLICK, btn_click_action);

  /* ------ Main Button ------*/
  lv_obj_t * main_text = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(main_text, SYMBOL_HOME);
  lv_obj_align(main_text, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 55, -20);

  lv_obj_t * main_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(main_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(main_button, 30);        /*Set a fix height*/
  lv_obj_set_width(main_button, 30);        /*Set a fix height*/
  lv_obj_align(main_button, main_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(main_button, 2);   /*Set a unique number for the button*/
  lv_btn_set_action(main_button, LV_BTN_ACTION_CLICK, btn_click_action);

}

void home_menu_obj(){
  current_screen = 1;
  lv_obj_t * home_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(home_scr);

  /* ---------- Styles ----------*/
  static lv_style_t style1;
  lv_style_copy(&style1, &lv_style_plain);
  style1.text.color = LV_COLOR_WHITE;
  style1.text.font = &lv_font_dejavu_20;

  static lv_style_t red_style;
  lv_style_copy(&red_style, &lv_style_plain);
  red_style.text.color = LV_COLOR_RED;
  red_style.text.font = &lv_font_dejavu_20;

  static lv_style_t blue_style;
  lv_style_copy(&blue_style, &lv_style_plain);
  blue_style.text.color = LV_COLOR_BLUE;
  blue_style.text.font = &lv_font_dejavu_20;

  /* ------ Description Label ------*/
  lv_obj_t * label1 =  lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(label1, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);
  lv_label_set_text(label1, "Current Auton:");

  lv_obj_t * auton_label =  lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(auton_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 50);
  lv_label_set_text(auton_label, "Current Auton:");
  switch(current_auton){
    case 0:
      lv_label_set_style(auton_label, &style1);
      lv_label_set_text(auton_label, "15pt");
      break;
    case 1:
    lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red1);
      break;
    case 2:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red2);
      break;
    case 3:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red3);
      break;
    case 4:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red4);
      break;
    case 5:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red5);
      break;
    case 6:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red6);
      break;
    case 7:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue1);
      break;
    case 8:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue2);
      break;
    case 9:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue3);
      break;
    case 10:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue4);
      break;
    case 11:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue5);
      break;
    case 12:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue6);
      break;
    case 13:
      lv_label_set_style(auton_label, &style1);
      lv_label_set_text(auton_label, prog1);
      break;
    case 14:
      lv_label_set_style(auton_label, &style1);
      lv_label_set_text(auton_label, prog2);
      break;
    case 15:
      lv_label_set_style(auton_label, &style1);
      lv_label_set_text(auton_label, prog3);
      break;
    default:
      lv_label_set_text(auton_label, "Error 1");
      break;

  }


  /* ------ Settings Button ------*/
  lv_obj_t * setting_icon = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(setting_icon, SYMBOL_SETTINGS);
  lv_obj_align(setting_icon, label1, LV_ALIGN_CENTER, 190, 125);

  lv_obj_t * setting_text = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(setting_text, &style1);
  lv_label_set_text(setting_text, "Settings");
  lv_obj_align(setting_text, setting_icon, LV_ALIGN_CENTER, 0, 55);

  lv_obj_t * setting_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(setting_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(setting_button, 80);        /*Set a fix height*/
  lv_obj_set_width(setting_button, 80);        /*Set a fix height*/
  lv_obj_align(setting_button, setting_icon, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(setting_button, 5);   /*Set a unique number for the button*/
  lv_btn_set_action(setting_button, LV_BTN_ACTION_CLICK, btn_click_action);


  /* ------ Debug Button ------*/
  lv_obj_t * debug_icon = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(debug_icon, SYMBOL_CHARGE);
  lv_obj_align(debug_icon, label1, LV_ALIGN_CENTER, 300, 15);

  lv_obj_t * debug_text = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(debug_text, &style1);
  lv_label_set_text(debug_text, "Debug");
  lv_obj_align(debug_text, debug_icon, LV_ALIGN_CENTER, 0, 55);

  lv_obj_t * debug_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(debug_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(debug_button, 80);        /*Set a fix height*/
  lv_obj_set_width(debug_button, 80);        /*Set a fix height*/
  lv_obj_align(debug_button, debug_icon, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(debug_button, 4);   /*Set a unique number for the button*/
  lv_btn_set_action(debug_button, LV_BTN_ACTION_CLICK, btn_click_action);

  /* ------ Selector Button ------*/
  lv_obj_t * selector_icon = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(selector_icon, SYMBOL_LIST);
  lv_obj_align(selector_icon, label1, LV_ALIGN_CENTER, 190, 15);

  lv_obj_t * selector_text = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(selector_text, &style1);
  lv_label_set_text(selector_text, "Selector");
  lv_obj_align(selector_text, selector_icon, LV_ALIGN_CENTER, 0, 55);

  lv_obj_t * selector_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(selector_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(selector_button, 80);        /*Set a fix height*/
  lv_obj_set_width(selector_button, 80);        /*Set a fix height*/
  lv_obj_align(selector_button, selector_icon, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(selector_button, 3);   /*Set a unique number for the button*/
  lv_btn_set_action(selector_button, LV_BTN_ACTION_CLICK, btn_click_action);

  /* ------ SD Button ------*/
  lv_obj_t * sd_icon = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(sd_icon, SYMBOL_IMAGE);
  lv_obj_align(sd_icon, label1, LV_ALIGN_CENTER, 300, 125);

  lv_obj_t * sd_text = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(sd_text, &style1);
  lv_label_set_text(sd_text, "SD Card");
  lv_obj_align(sd_text, sd_icon, LV_ALIGN_CENTER, 0, 55);

  lv_obj_t * sd_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(sd_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(sd_button, 80);        /*Set a fix height*/
  lv_obj_set_width(sd_button, 80);        /*Set a fix height*/
  lv_obj_align(sd_button, sd_icon, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(sd_button, 6);   /*Set a unique number for the button*/
  lv_btn_set_action(sd_button, LV_BTN_ACTION_CLICK, btn_click_action);
}

void selector_menu_obj(){
  current_screen = 2;
  lv_obj_t * selector_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(selector_scr);

  /* ---------- Styles ----------*/
  static lv_style_t style1;
  lv_style_copy(&style1, &lv_style_plain);
  style1.text.color = LV_COLOR_WHITE;
  style1.text.font = &lv_font_dejavu_20;

  static lv_style_t red_style;
  lv_style_copy(&red_style, &lv_style_plain);
  red_style.text.color = LV_COLOR_RED;
  red_style.text.font = &lv_font_dejavu_20;

  static lv_style_t blue_style;
  lv_style_copy(&blue_style, &lv_style_plain);
  blue_style.text.color = LV_COLOR_BLUE;
  blue_style.text.font = &lv_font_dejavu_20;

  /* ------ Description Label ------*/
  lv_obj_t * signifier_label =  lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(signifier_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);
  lv_label_set_text(signifier_label, "Current Auton:");

  lv_obj_t * auton_label =  lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(auton_label, NULL, LV_ALIGN_IN_TOP_LEFT, 150, 20);
  switch(current_auton){
    case 0:
      lv_label_set_style(auton_label, &style1);
      lv_label_set_text(auton_label, "15pt");
      break;
    case 1:
    lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red1);
      break;
    case 2:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red2);
      break;
    case 3:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red3);
      break;
    case 4:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red4);
      break;
    case 5:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red5);
      break;
    case 6:
      lv_label_set_style(auton_label, &red_style);
      lv_label_set_text(auton_label, red6);
      break;
    case 7:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue1);
      break;
    case 8:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue2);
      break;
    case 9:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue3);
      break;
    case 10:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue4);
      break;
    case 11:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue5);
      break;
    case 12:
      lv_label_set_style(auton_label, &blue_style);
      lv_label_set_text(auton_label, blue6);
      break;
    case 13:
      lv_label_set_style(auton_label, &style1);
      lv_label_set_text(auton_label, prog1);
      break;
    case 14:
      lv_label_set_style(auton_label, &style1);
      lv_label_set_text(auton_label, prog2);
      break;
    case 15:
      lv_label_set_style(auton_label, &style1);
      lv_label_set_text(auton_label, prog3);
      break;
    default:
      lv_label_set_text(auton_label, "Error 1");
      break;
    }
  /* ------ Skills button ------*/
  lv_obj_t * skills_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(skills_text, "Programming Skills");
  lv_obj_align(skills_text, NULL, LV_ALIGN_CENTER, 0, 35);

  lv_obj_t * skills_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(skills_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(skills_button, 70);        /*Set a fix height*/
  lv_obj_set_width(skills_button, 400);        /*Set a fix height*/
  lv_obj_align(skills_button, skills_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(skills_button, 7);   /*Set a unique number for the button*/
  lv_btn_set_action(skills_button, LV_BTN_ACTION_CLICK, btn_click_action);

  /* ------ Red button ------*/
  static lv_style_t style2;
  lv_style_copy(&style2, &lv_style_plain);
  style2.text.color = LV_COLOR_RED;
  style2.text.font = &lv_font_dejavu_20;

  lv_obj_t * red_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(red_text, &style2);
  lv_label_set_text(red_text, "Red");
  lv_obj_align(red_text, NULL, LV_ALIGN_CENTER, -110, -40);

  lv_obj_t * red_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(red_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(red_button, 70);        /*Set a fix height*/
  lv_obj_set_width(red_button, 180);        /*Set a fix height*/
  lv_obj_align(red_button, red_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(red_button, 8);   /*Set a unique number for the button*/
  lv_btn_set_action(red_button, LV_BTN_ACTION_CLICK, btn_click_action);

  /* ------ Blue button ------*/
  static lv_style_t style3;
  lv_style_copy(&style3, &lv_style_plain);
  style3.text.color = LV_COLOR_BLUE;
  style3.text.font = &lv_font_dejavu_20;

  lv_obj_t * blue_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(blue_text, &style3);
  lv_label_set_text(blue_text, "Blue");
  lv_obj_align(blue_text, NULL, LV_ALIGN_CENTER, 110, -40);

  lv_obj_t * blue_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(blue_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(blue_button, 70);        /*Set a fix height*/
  lv_obj_set_width(blue_button, 180);        /*Set a fix height*/
  lv_obj_align(blue_button, blue_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(blue_button, 9);   /*Set a unique number for the button*/
  lv_btn_set_action(blue_button, LV_BTN_ACTION_CLICK, btn_click_action);
}


void debug_menu_obj(int sort){

  /* ---- SORT TYPES ---- */
  /* 1 ----------- Motors */
  /* 2 --------- Velocity */
  /* 3 ---------- Degrees */
  /* 4 ----------- Torque */
  /* 5 ------------ Power */
  /* 6 ---------- Voltage */
  /* 7 ------- Efficiency */
  /* 8 ------ Temperature */
  /* -------------------- */

  current_screen = 3;
  lv_obj_t * debug_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(debug_scr);

  /* ------ Description Label ------*/
  lv_obj_t * debug_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(debug_label, "Debug Menu. Sort by:");
  lv_obj_align(debug_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);


  lv_obj_t * ddl1 = lv_ddlist_create(lv_scr_act(), NULL);

  lv_ddlist_set_options(ddl1, "Motors and Sensors\n"
                              "Velocity\n"
                              "Degrees\n"
                              "Torque\n"
                              "Power\n"
                              "Voltage\n"
                              "Efficiency\n"
                              "Temperature\n");

  lv_obj_align(ddl1, NULL, LV_ALIGN_IN_TOP_RIGHT, -30, 10);
  lv_obj_set_free_num(ddl1, 1);               /*Set a unique ID*/
  lv_ddlist_set_action(ddl1, ddlist_action);  /*Set a function to call when anew option is chosen*/

  /*Create a style*/
  static lv_style_t style_sb;
  lv_style_copy(&style_sb, &lv_style_pretty);
  style_sb.body.shadow.width = 4; /*Enable the shadow*/
  style_sb.text.color = LV_COLOR_MAKE(0x10, 0x20, 0x50);

}

void setting_menu_obj(){
  current_screen = 4;
  lv_obj_t * selector_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(selector_scr);
  /* ------ Description Label ------*/
  lv_obj_t * current_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(current_label, "Settings: Menu");
  lv_obj_align(current_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

  /* ------ three button ------*/
  lv_obj_t * three_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(three_text, "Three");
  lv_obj_align(three_text, NULL, LV_ALIGN_CENTER, -110, 35);

  lv_obj_t * three_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(three_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(three_button, 70);        /*Set a fix height*/
  lv_obj_set_width(three_button, 180);        /*Set a fix height*/
  lv_obj_align(three_button, three_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(three_button, 6);   /*Set a unique number for the button*/
  lv_btn_set_action(three_button, LV_BTN_ACTION_CLICK, btn_click_action);

  /* ------ Config button ------*/
  lv_obj_t * config_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(config_text, "Config");
  lv_obj_align(config_text, NULL, LV_ALIGN_CENTER, -110, -40);

  lv_obj_t * config_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(config_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(config_button, 70);        /*Set a fix height*/
  lv_obj_set_width(config_button, 180);        /*Set a fix height*/
  lv_obj_align(config_button, config_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(config_button, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(config_button, LV_BTN_ACTION_CLICK, settings_btn_click_action);

  lv_obj_t * four_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(four_text, "Four");
  lv_obj_align(four_text, NULL, LV_ALIGN_CENTER, 110, 35);

  lv_obj_t * four_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(four_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(four_button, 70);        /*Set a fix height*/
  lv_obj_set_width(four_button, 180);        /*Set a fix height*/
  lv_obj_align(four_button, four_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(four_button, 6);   /*Set a unique number for the button*/
  lv_btn_set_action(four_button, LV_BTN_ACTION_CLICK, btn_click_action);

  /* ------ two button ------*/
  lv_obj_t * two_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(two_text, "Two");
  lv_obj_align(two_text, NULL, LV_ALIGN_CENTER, 110, -40);

  lv_obj_t * two_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(two_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(two_button, 70);        /*Set a fix height*/
  lv_obj_set_width(two_button, 180);        /*Set a fix height*/
  lv_obj_align(two_button, two_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(two_button, 10);   /*Set a unique number for the button*/
  lv_btn_set_action(two_button, LV_BTN_ACTION_CLICK, btn_click_action);
}

//RED MENU
void red_menu_obj(){
  current_screen = 7;
  lv_obj_t * red_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(red_scr);
  /* ------ Description Label ------*/
  lv_obj_t * auton_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(auton_label, "Red Menu");
  lv_obj_align(auton_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

  /* ------ Styles ------*/
  static lv_style_t style1; // red
  lv_style_copy(&style1, &lv_style_plain);
  style1.text.color = LV_COLOR_RED;
  style1.text.font = &lv_font_dejavu_20;

  static lv_style_t style2; // white
  lv_style_copy(&style2, &lv_style_plain);
  style2.text.color = LV_COLOR_WHITE;
  style2.text.font = &lv_font_dejavu_20;


  /* ------ 1 button ------*/

  lv_obj_t * red1_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(red1_text, &style1);
  lv_label_set_text(red1_text, red1);
  lv_obj_align(red1_text, NULL, LV_ALIGN_CENTER, -160, -40);

  lv_obj_t * red1_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(red1_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(red1_button, 50);        /*Set a fix height*/
  lv_obj_set_width(red1_button, 150);        /*Set a fix height*/
  lv_obj_align(red1_button, red1_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(red1_button, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(red1_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 2 button ------*/
  lv_obj_t * red2_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(red2_text, &style2);
  lv_label_set_text(red2_text, red2);
  lv_obj_align(red2_text, NULL, LV_ALIGN_CENTER, 0, -40);

  lv_obj_t * red2_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(red2_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(red2_button, 50);        /*Set a fix height*/
  lv_obj_set_width(red2_button, 150);        /*Set a fix height*/
  lv_obj_align(red2_button, red2_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(red2_button, 2);   /*Set a unique number for the button*/
  lv_btn_set_action(red2_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 3 button ------*/
  lv_obj_t * red3_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(red3_text, &style1);
  lv_label_set_text(red3_text, red3);
  lv_obj_align(red3_text, NULL, LV_ALIGN_CENTER, 160, -40);

  lv_obj_t * red3_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(red3_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(red3_button, 50);        /*Set a fix height*/
  lv_obj_set_width(red3_button, 150);        /*Set a fix height*/
  lv_obj_align(red3_button, red3_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(red3_button, 3);   /*Set a unique number for the button*/
  lv_btn_set_action(red3_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 4 button ------*/

  lv_obj_t * red4_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(red4_text, &style2);
  lv_label_set_text(red4_text, red4);
  lv_obj_align(red4_text, NULL, LV_ALIGN_CENTER, -160, 20);

  lv_obj_t * red4_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(red4_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(red4_button, 50);        /*Set a fix height*/
  lv_obj_set_width(red4_button, 150);        /*Set a fix height*/
  lv_obj_align(red4_button, red4_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(red4_button, 4);   /*Set a unique number for the button*/
  lv_btn_set_action(red4_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 5 button ------*/
  lv_obj_t * red5_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(red5_text, &style1);
  lv_label_set_text(red5_text, red5);
  lv_obj_align(red5_text, NULL, LV_ALIGN_CENTER, 0, 20);

  lv_obj_t * red5_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(red5_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(red5_button, 50);        /*Set a fix height*/
  lv_obj_set_width(red5_button, 150);        /*Set a fix height*/
  lv_obj_align(red5_button, red5_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(red5_button, 5);   /*Set a unique number for the button*/
  lv_btn_set_action(red5_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 6 button ------*/
  lv_obj_t * red6_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(red6_text, &style2);
  lv_label_set_text(red6_text, red6);
  lv_obj_align(red6_text, NULL, LV_ALIGN_CENTER, 160, 20);

  lv_obj_t * red6_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(red6_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(red6_button, 50);        /*Set a fix height*/
  lv_obj_set_width(red6_button, 150);        /*Set a fix height*/
  lv_obj_align(red6_button, red6_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(red6_button, 6);   /*Set a unique number for the button*/
  lv_btn_set_action(red6_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

}

//BLUE MENU
void blue_menu_obj(){
  current_screen = 8;
  lv_obj_t * blue_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(blue_scr);
  /* ------ Description Label ------*/
  lv_obj_t * auton_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(auton_label, "Blue Menu");
  lv_obj_align(auton_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

  /* ------ Styles ------*/
  static lv_style_t style1; // blue
  lv_style_copy(&style1, &lv_style_plain);
  style1.text.color = LV_COLOR_BLUE;
  style1.text.font = &lv_font_dejavu_20;

  static lv_style_t style2; // white
  lv_style_copy(&style2, &lv_style_plain);
  style2.text.color = LV_COLOR_WHITE;
  style2.text.font = &lv_font_dejavu_20;


  /* ------ 1 button ------*/

  lv_obj_t * blue1_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(blue1_text, &style1);
  lv_label_set_text(blue1_text, blue1);
  lv_obj_align(blue1_text, NULL, LV_ALIGN_CENTER, -160, -40);

  lv_obj_t * blue1_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(blue1_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(blue1_button, 50);        /*Set a fix height*/
  lv_obj_set_width(blue1_button, 150);        /*Set a fix height*/
  lv_obj_align(blue1_button, blue1_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(blue1_button, 7);   /*Set a unique number for the button*/
  lv_btn_set_action(blue1_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 2 button ------*/
  lv_obj_t * blue2_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(blue2_text, &style2);
  lv_label_set_text(blue2_text, blue2);
  lv_obj_align(blue2_text, NULL, LV_ALIGN_CENTER, 0, -40);

  lv_obj_t * blue2_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(blue2_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(blue2_button, 50);        /*Set a fix height*/
  lv_obj_set_width(blue2_button, 150);        /*Set a fix height*/
  lv_obj_align(blue2_button, blue2_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(blue2_button, 8);   /*Set a unique number for the button*/
  lv_btn_set_action(blue2_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 3 button ------*/
  lv_obj_t * blue3_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(blue3_text, &style1);
  lv_label_set_text(blue3_text, blue3);
  lv_obj_align(blue3_text, NULL, LV_ALIGN_CENTER, 160, -40);

  lv_obj_t * blue3_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(blue3_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(blue3_button, 50);        /*Set a fix height*/
  lv_obj_set_width(blue3_button, 150);        /*Set a fix height*/
  lv_obj_align(blue3_button, blue3_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(blue3_button, 9);   /*Set a unique number for the button*/
  lv_btn_set_action(blue3_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 4 button ------*/

  lv_obj_t * blue4_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(blue4_text, &style2);
  lv_label_set_text(blue4_text, blue4);
  lv_obj_align(blue4_text, NULL, LV_ALIGN_CENTER, -160, 20);

  lv_obj_t * blue4_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(blue4_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(blue4_button, 50);        /*Set a fix height*/
  lv_obj_set_width(blue4_button, 150);        /*Set a fix height*/
  lv_obj_align(blue4_button, blue4_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(blue4_button, 10);   /*Set a unique number for the button*/
  lv_btn_set_action(blue4_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 5 button ------*/
  lv_obj_t * blue5_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(blue5_text, &style1);
  lv_label_set_text(blue5_text, blue5);
  lv_obj_align(blue5_text, NULL, LV_ALIGN_CENTER, 0, 20);

  lv_obj_t * blue5_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(blue5_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(blue5_button, 50);        /*Set a fix height*/
  lv_obj_set_width(blue5_button, 150);        /*Set a fix height*/
  lv_obj_align(blue5_button, blue5_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(blue5_button, 11);   /*Set a unique number for the button*/
  lv_btn_set_action(blue5_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 6 button ------*/
  lv_obj_t * blue6_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(blue6_text, &style2);
  lv_label_set_text(blue6_text, blue6);
  lv_obj_align(blue6_text, NULL, LV_ALIGN_CENTER, 160, 20);

  lv_obj_t * blue6_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(blue6_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(blue6_button, 50);        /*Set a fix height*/
  lv_obj_set_width(blue6_button, 150);        /*Set a fix height*/
  lv_obj_align(blue6_button, blue6_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(blue6_button, 12);   /*Set a unique number for the button*/
  lv_btn_set_action(blue6_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

}

// PROG SKILLS MENU
void prog_skills_obj(){
  current_screen = 10;
  lv_obj_t * prog_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(prog_scr);
  /* ------ Description Label ------*/
  lv_obj_t * auton_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(auton_label, "Programming Skills Menu");
  lv_obj_align(auton_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

  /* ------ Styles ------*/
  static lv_style_t style1; // white
  lv_style_copy(&style1, &lv_style_plain);
  style1.text.color = LV_COLOR_WHITE;
  style1.text.font = &lv_font_dejavu_20;

  /* ------ 1 button ------*/

  lv_obj_t * prog1_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(prog1_text, &style1);
  lv_label_set_text(prog1_text, prog1);
  lv_obj_align(prog1_text, NULL, LV_ALIGN_CENTER, -160, -40);

  lv_obj_t * prog1_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(prog1_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(prog1_button, 50);        /*Set a fix height*/
  lv_obj_set_width(prog1_button, 150);        /*Set a fix height*/
  lv_obj_align(prog1_button, prog1_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(prog1_button, 13);   /*Set a unique number for the button*/
  lv_btn_set_action(prog1_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 2 button ------*/
  lv_obj_t * prog2_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(prog2_text, &style1);
  lv_label_set_text(prog2_text, prog2);
  lv_obj_align(prog2_text, NULL, LV_ALIGN_CENTER, 0, -40);

  lv_obj_t * prog2_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(prog2_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(prog2_button, 50);        /*Set a fix height*/
  lv_obj_set_width(prog2_button, 150);        /*Set a fix height*/
  lv_obj_align(prog2_button, prog2_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(prog2_button, 14);   /*Set a unique number for the button*/
  lv_btn_set_action(prog2_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);

  /* ------ 3 button ------*/
  lv_obj_t * prog3_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(prog3_text, &style1);
  lv_label_set_text(prog3_text, prog3);
  lv_obj_align(prog3_text, NULL, LV_ALIGN_CENTER, 160, -40);

  lv_obj_t * prog3_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(prog3_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(prog3_button, 50);        /*Set a fix height*/
  lv_obj_set_width(prog3_button, 150);        /*Set a fix height*/
  lv_obj_align(prog3_button, prog3_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(prog3_button, 15);   /*Set a unique number for the button*/
  lv_btn_set_action(prog3_button, LV_BTN_ACTION_CLICK, auton_btn_click_action);
}

void confirm_menu_obj(int set_auton){
  current_screen = 9;
  lv_obj_t * confirm_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(confirm_scr);

  /* ------ Styles ------*/
  static lv_style_t blue_style; // blue
  lv_style_copy(&blue_style, &lv_style_plain);
  blue_style.text.color = LV_COLOR_BLUE;
  blue_style.text.font = &lv_font_dejavu_20;

  static lv_style_t red_style; // red
  lv_style_copy(&red_style, &lv_style_plain);
  red_style.text.color = LV_COLOR_RED;
  red_style.text.font = &lv_font_dejavu_20;

  static lv_style_t style2; // white
  lv_style_copy(&style2, &lv_style_plain);
  style2.text.color = LV_COLOR_WHITE;
  style2.text.font = &lv_font_dejavu_20;

  static lv_style_t green_style; // greem
  lv_style_copy(&green_style, &lv_style_plain);
  green_style.text.color = LV_COLOR_GREEN;
  green_style.text.font = &lv_font_dejavu_20;

  /* ------ Description Label ------*/
  lv_obj_t * confirm_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(confirm_label, "Confirm?");
  lv_obj_align(confirm_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

  lv_obj_t * selected_auton_label =  lv_label_create(lv_scr_act(), NULL);
  switch(set_auton){
    case 1:
      lv_label_set_style(selected_auton_label, &red_style);
      lv_label_set_text(selected_auton_label, red1);
      break;
    case 2:
      lv_label_set_style(selected_auton_label, &red_style);
      lv_label_set_text(selected_auton_label, red2);
      break;
    case 3:
      lv_label_set_style(selected_auton_label, &red_style);
      lv_label_set_text(selected_auton_label, red3);
      break;
    case 4:
      lv_label_set_style(selected_auton_label, &red_style);
      lv_label_set_text(selected_auton_label, red4);
      break;
    case 5:
      lv_label_set_style(selected_auton_label, &red_style);
      lv_label_set_text(selected_auton_label, red5);
      break;
    case 6:
      lv_label_set_style(selected_auton_label, &red_style);
      lv_label_set_text(selected_auton_label, red6);
      break;
    case 7:
      lv_label_set_style(selected_auton_label, &blue_style);
      lv_label_set_text(selected_auton_label, blue1);
      break;
    case 8:
      lv_label_set_style(selected_auton_label, &blue_style);
      lv_label_set_text(selected_auton_label, blue2);
      break;
    case 9:
      lv_label_set_style(selected_auton_label, &blue_style);
      lv_label_set_text(selected_auton_label, blue3);
      break;
    case 10:
      lv_label_set_style(selected_auton_label, &blue_style);
      lv_label_set_text(selected_auton_label, blue4);
      break;
    case 11:
      lv_label_set_style(selected_auton_label, &blue_style);
      lv_label_set_text(selected_auton_label, blue5);
      break;
    case 12:
      lv_label_set_style(selected_auton_label, &blue_style);
      lv_label_set_text(selected_auton_label, blue6);
      break;
    case 13:
      lv_label_set_style(selected_auton_label, &style2);
      lv_label_set_text(selected_auton_label, prog1);
      break;
    case 14:
      lv_label_set_style(selected_auton_label, &style2);
      lv_label_set_text(selected_auton_label, prog2);
      break;
    case 15:
      lv_label_set_style(selected_auton_label, &style2);
      lv_label_set_text(selected_auton_label, prog3);
      break;
    }
  lv_obj_align(selected_auton_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 50);

  /* ------ YES button ------*/

  lv_obj_t * yes_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(yes_text, &green_style);
  lv_label_set_text(yes_text, "Yes");
  lv_obj_align(yes_text, NULL, LV_ALIGN_CENTER, -50, 40);

  lv_obj_t * yes_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(yes_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(yes_button, 75);        /*Set a fix height*/
  lv_obj_set_width(yes_button, 100);        /*Set a fix width*/
  lv_obj_align(yes_button, yes_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(yes_button, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(yes_button, LV_BTN_ACTION_CLICK, confirm_btn_click_action);

  /* ------ NO button ------*/
  lv_obj_t * no_text =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(no_text, &red_style);
  lv_label_set_text(no_text, "No");
  lv_obj_align(no_text, NULL, LV_ALIGN_CENTER, 80, 40);

  lv_obj_t * no_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(no_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(no_button, 75);        /*Set a fix height*/
  lv_obj_set_width(no_button, 100);        /*Set a fix height*/
  lv_obj_align(no_button, no_text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(no_button, 0);   /*Set a unique number for the button*/
  lv_btn_set_action(no_button, LV_BTN_ACTION_CLICK, confirm_btn_click_action);
}

void config_menu_obj(){
  current_screen = 11;
  lv_obj_t * confirm_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(confirm_scr);

  /*------- Styles -------*/
  static lv_style_t style2; // white
  lv_style_copy(&style2, &lv_style_plain);
  style2.text.color = LV_COLOR_WHITE;
  style2.text.font = &lv_font_dejavu_20;

  lv_obj_t * config_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(config_label, "Configure Ports");
  lv_obj_align(config_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

  /*------- Motors -------*/
  lv_obj_t * frontL_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(frontL_label, "frontL");
  lv_obj_align(frontL_label, NULL, LV_ALIGN_CENTER, -195, -60);

  char frontL_port_no[2];
  sprintf(frontL_port_no, "%d", frontL_port);
  const char * frontL_port_number = frontL_port_no;
  lv_obj_t * frontL_port_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(frontL_port_label, frontL_port_number);
  lv_obj_align(frontL_port_label, NULL, LV_ALIGN_CENTER, -120, -60);

  lv_obj_t * frontL_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(frontL_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(frontL_button, 35);        /*Set a fix height*/
  lv_obj_set_width(frontL_button, 50);        /*Set a fix height*/
  lv_obj_align(frontL_button, frontL_port_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(frontL_button, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(frontL_button, LV_BTN_ACTION_CLICK, config_btn_click_action);


  lv_obj_t * frontR_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(frontR_label, "frontR");
  lv_obj_align(frontR_label, NULL, LV_ALIGN_CENTER, -195, -20);

  char frontR_port_no[2];
  sprintf(frontR_port_no, "%d", frontR_port);
  const char * frontR_port_number = frontR_port_no;
  lv_obj_t * frontR_port_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(frontR_port_label, frontR_port_number);
  lv_obj_align(frontR_port_label, NULL, LV_ALIGN_CENTER, -120, -20);

  lv_obj_t * frontR_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(frontR_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(frontR_button, 35);        /*Set a fix height*/
  lv_obj_set_width(frontR_button, 50);        /*Set a fix height*/
  lv_obj_align(frontR_button, frontR_port_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(frontR_button, 2);   /*Set a unique number for the button*/
  lv_btn_set_action(frontR_button, LV_BTN_ACTION_CLICK, config_btn_click_action);


  lv_obj_t * backL_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(backL_label, "backL");
  lv_obj_align(backL_label, NULL, LV_ALIGN_CENTER, -195, 20);

  char backL_port_no[2];
  sprintf(backL_port_no, "%d", backL_port);
  const char * backL_port_number = backL_port_no;
  lv_obj_t * backL_port_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(backL_port_label, backL_port_number);
  lv_obj_align(backL_port_label, NULL, LV_ALIGN_CENTER, -120, 20);

  lv_obj_t * backL_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(backL_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(backL_button, 35);        /*Set a fix height*/
  lv_obj_set_width(backL_button, 50);        /*Set a fix height*/
  lv_obj_align(backL_button, backL_port_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(backL_button, 3);   /*Set a unique number for the button*/
  lv_btn_set_action(backL_button, LV_BTN_ACTION_CLICK, config_btn_click_action);


  lv_obj_t * backR_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(backR_label, "backR");
  lv_obj_align(backR_label, NULL, LV_ALIGN_CENTER, -195, 60);

  char backR_port_no[2];
  sprintf(backR_port_no, "%d", backR_port);
  const char * backR_port_number = backR_port_no;
  lv_obj_t * backR_port_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(backR_port_label, backR_port_number);
  lv_obj_align(backR_port_label, NULL, LV_ALIGN_CENTER, -120, 60);

  lv_obj_t * backR_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(backR_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(backR_button, 35);        /*Set a fix height*/
  lv_obj_set_width(backR_button, 50);        /*Set a fix height*/
  lv_obj_align(backR_button, backR_port_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(backR_button, 4);   /*Set a unique number for the button*/
  lv_btn_set_action(backR_button, LV_BTN_ACTION_CLICK, config_btn_click_action);

  lv_obj_t * puncher_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(puncher_label, "puncher");
  lv_obj_align(puncher_label, NULL, LV_ALIGN_CENTER, 20, -60);

  char puncher_port_no[2];
  sprintf(puncher_port_no, "%d", puncher_port);
  const char * puncher_port_number = puncher_port_no;
  lv_obj_t * puncher_port_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(puncher_port_label, puncher_port_number);
  lv_obj_align(puncher_port_label, NULL, LV_ALIGN_CENTER, 90, -60);

  lv_obj_t * puncher_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(puncher_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(puncher_button, 35);        /*Set a fix height*/
  lv_obj_set_width(puncher_button, 50);        /*Set a fix height*/
  lv_obj_align(puncher_button, puncher_port_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(puncher_button, 5);   /*Set a unique number for the button*/
  lv_btn_set_action(puncher_button, LV_BTN_ACTION_CLICK, config_btn_click_action);

  lv_obj_t * intake_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(intake_label, "intake");
  lv_obj_align(intake_label, NULL, LV_ALIGN_CENTER, 20, 20);
  char intake_port_no[2];
  sprintf(intake_port_no, "%d", intake_port);
  const char * intake_port_number = intake_port_no;
  lv_obj_t * intake_port_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(intake_port_label, intake_port_number);
  lv_obj_align(intake_port_label, NULL, LV_ALIGN_CENTER, 90, 20);

  lv_obj_t * intake_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(intake_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(intake_button, 35);        /*Set a fix height*/
  lv_obj_set_width(intake_button, 50);        /*Set a fix height*/
  lv_obj_align(intake_button, intake_port_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(intake_button, 7);   /*Set a unique number for the button*/
  lv_btn_set_action(intake_button, LV_BTN_ACTION_CLICK, config_btn_click_action);

  lv_obj_t * angler_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(angler_label, "angler");
  lv_obj_align(angler_label, NULL, LV_ALIGN_CENTER, 20, -20);

  char angler_port_no[2];
  sprintf(angler_port_no, "%d", angler_port);
  const char * angler_port_number = angler_port_no;
  lv_obj_t * angler_port_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(angler_port_label, angler_port_number);
  lv_obj_align(angler_port_label, NULL, LV_ALIGN_CENTER, 90, -20);

  lv_obj_t * angler_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(angler_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(angler_button, 35);        /*Set a fix height*/
  lv_obj_set_width(angler_button, 50);        /*Set a fix height*/
  lv_obj_align(angler_button, angler_port_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(angler_button, 6);   /*Set a unique number for the button*/
  lv_btn_set_action(angler_button, LV_BTN_ACTION_CLICK, config_btn_click_action);

  lv_obj_t * flipper_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(flipper_label, "flipper");
  lv_obj_align(flipper_label, NULL, LV_ALIGN_CENTER, 20, 60);

  char flipper_port_no[2];
  sprintf(flipper_port_no, "%d", flipper_port);
  const char * flipper_port_number = flipper_port_no;
  lv_obj_t * flipper_port_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(flipper_port_label, flipper_port_number);
  lv_obj_align(flipper_port_label, NULL, LV_ALIGN_CENTER, 90, 60);

  lv_obj_t * flipper_button = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(flipper_button, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(flipper_button, 35);        /*Set a fix height*/
  lv_obj_set_width(flipper_button, 50);        /*Set a fix height*/
  lv_obj_align(flipper_button, flipper_port_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(flipper_button, 8);   /*Set a unique number for the button*/
  lv_btn_set_action(flipper_button, LV_BTN_ACTION_CLICK, config_btn_click_action);
}



void home_menu(){
  home_menu_obj();
  const_buttons();
}

void selector_menu(){
  selector_menu_obj();
  const_buttons();
}

void debug_menu(int sort_Type){
  debug_menu_obj(sort_Type);
  const_buttons();
}

void setting_menu(){
  setting_menu_obj();
  const_buttons();
}


void red_menu(){
  red_menu_obj();
  const_buttons();
}

void blue_menu(){
  blue_menu_obj();
  const_buttons();
}

void prog_menu(){
  prog_skills_obj();
  const_buttons();
}

void config_menu(){
  config_menu_obj();
  const_buttons();
}

//page change
static lv_res_t btn_click_action(lv_obj_t * btn){
  uint8_t id = lv_obj_get_free_num(btn);
  switch(id){
    case 1:
      if(current_screen == 1){
        break;
      }
      else if(current_screen == 2 || current_screen == 3 || current_screen == 4 ||
        current_screen == 5){
        home_menu();
      }
      else if(current_screen == 7 || current_screen == 8 || current_screen == 10){
        selector_menu();
      }
      else if(current_screen == 11){
        setting_menu();
      }
      else if(current_screen == 12){
        config_menu();
      }
      else if(current_screen == 13){
        config_menu();
      }

      break;

    case 2:
      home_menu();
      break;

    case 3:
      selector_menu();
      break;

    case 4:
      debug_menu(1);
      break;

    case 5:
      setting_menu();
      break;

    case 6: //SD CARD
      break;

    case 7: // skills menu
      prog_menu();
      break;

    case 8:
      red_menu();
      break;

    case 9:
      blue_menu();
      break;
}
  return LV_RES_OK; /*Return OK if the button is not deleted*/
}



void warning_test(int i){
  /* ------ Styles ------*/
  static lv_style_t blue_style; // blue
  lv_style_copy(&blue_style, &lv_style_plain);
  blue_style.text.color = LV_COLOR_BLUE;
  blue_style.text.font = &lv_font_dejavu_20;

  static lv_style_t red_style; // red
  lv_style_copy(&red_style, &lv_style_plain);
  red_style.text.color = LV_COLOR_RED;
  red_style.text.font = &lv_font_dejavu_20;

  static lv_style_t style2; // white
  lv_style_copy(&style2, &lv_style_plain);
  style2.text.color = LV_COLOR_WHITE;
  style2.text.font = &lv_font_dejavu_20;

  static lv_style_t green_style; // greem
  lv_style_copy(&green_style, &lv_style_plain);
  green_style.text.color = LV_COLOR_GREEN;
  green_style.text.font = &lv_font_dejavu_20;

  bool port_conflict;
  std::cout << "-" << std::endl;
  for(int a = 0; a < 8; a++){
    std::cout << ports[a] << std::endl;
    if(ports[a] == i){
      port_conflict = true;
      break;
    }
    else{
      port_conflict = false;
    }
  }
  if(port_conflict){
    lv_obj_t * warning = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(warning, "This port is already something else. Please go back.");
      lv_obj_align(warning, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 100);
    }
    else{
      char set_text[30];
      lv_obj_t * set = lv_label_create(lv_scr_act(), NULL);
      sprintf(set_text, "Change port %d to port %d?", motor_to_change, i);
      lv_label_set_text(set, set_text);
      lv_obj_align(set, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 100);

      /* ------ YES button ------*/

      lv_obj_t * yes_text =  lv_label_create(lv_scr_act(), NULL);
      lv_label_set_style(yes_text, &green_style);
      lv_label_set_text(yes_text, "Yes");
      lv_obj_align(yes_text, NULL, LV_ALIGN_CENTER, -50, 40);

      lv_obj_t * yes_button = lv_btn_create(lv_scr_act(), NULL);
      lv_cont_set_fit(yes_button, false, false); /*Enable resizing horizontally and vertically*/
      lv_obj_set_height(yes_button, 75);        /*Set a fix height*/
      lv_obj_set_width(yes_button, 100);        /*Set a fix width*/
      lv_obj_align(yes_button, yes_text, LV_ALIGN_CENTER, 0, 0);
      lv_obj_set_free_num(yes_button, 1);   /*Set a unique number for the button*/
      lv_btn_set_action(yes_button, LV_BTN_ACTION_CLICK, config_confirm_btn_click_action);

      /* ------ NO button ------*/
      lv_obj_t * no_text =  lv_label_create(lv_scr_act(), NULL);
      lv_label_set_style(no_text, &red_style);
      lv_label_set_text(no_text, "No");
      lv_obj_align(no_text, NULL, LV_ALIGN_CENTER, 80, 40);

      lv_obj_t * no_button = lv_btn_create(lv_scr_act(), NULL);
      lv_cont_set_fit(no_button, false, false); /*Enable resizing horizontally and vertically*/
      lv_obj_set_height(no_button, 75);        /*Set a fix height*/
      lv_obj_set_width(no_button, 100);        /*Set a fix height*/
      lv_obj_align(no_button, no_text, LV_ALIGN_CENTER, 0, 0);
      lv_obj_set_free_num(no_button, 0);   /*Set a unique number for the button*/
      lv_btn_set_action(no_button, LV_BTN_ACTION_CLICK, config_confirm_btn_click_action);

  }
}


static lv_res_t change_ports_action1(lv_obj_t * btn)
{
  uint8_t id = lv_obj_get_free_num(btn);
  current_screen = 13;
  lv_obj_t * port_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(port_scr);
  const_buttons();


  lv_obj_t * port_con_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(port_con_label, "Confirm:");
  lv_obj_align(port_con_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

  lv_obj_t * port_label =  lv_label_create(lv_scr_act(), NULL);
  char text[8];
  sprintf(text, "Port: %d", id);

  lv_label_set_text(port_label, text);
  lv_obj_align(port_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 70);
  warning_test(id);
    return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}


static lv_res_t change_ports_action2(lv_obj_t * btn)
{
  uint8_t id = lv_obj_get_free_num(btn);
  current_screen = 13;
  lv_obj_t * port_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(port_scr);
  const_buttons();


  lv_obj_t * port_con_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(port_con_label, "Confirm:");
  lv_obj_align(port_con_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

  lv_obj_t * port_label =  lv_label_create(lv_scr_act(), NULL);
  char text[8];
  sprintf(text, "Port: %d", id);

  lv_label_set_text(port_label, text);
  lv_obj_align(port_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 70);
  warning_test(id);
    return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}


static lv_res_t change_ports_action3(lv_obj_t * btn)
{
  uint8_t id = lv_obj_get_free_num(btn);
  current_screen = 13;
  lv_obj_t * port_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(port_scr);
  const_buttons();


  lv_obj_t * port_con_label =  lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(port_con_label, "Confirm:");
  lv_obj_align(port_con_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

  lv_obj_t * port_label =  lv_label_create(lv_scr_act(), NULL);
  char text[8];
  sprintf(text, "Port: %d", id);

  lv_label_set_text(port_label, text);
  lv_obj_align(port_label, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 70);
  warning_test(id);
    return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static lv_res_t auton_btn_click_action(lv_obj_t * btn){
  uint8_t id = lv_obj_get_free_num(btn);
  previous_auton = current_auton;
  to_set_auton = id;
  confirm_menu_obj(id);
  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t confirm_btn_click_action(lv_obj_t * btn){
  uint8_t id = lv_obj_get_free_num(btn);
  if(id == 1){
    current_auton = to_set_auton;
    previous_auton = current_auton;
    home_menu();
  }
  else if(id == 0){
    current_auton = previous_auton;
    if(1 <= to_set_auton && to_set_auton <= 6){
      red_menu();
    }
    else if(7 <= to_set_auton && to_set_auton <= 12){
      blue_menu();
    }
    else if(13 <= to_set_auton && to_set_auton <= 15){
      prog_menu();
    }
    /*else{
      prog stuff();
    }*/
  }
  return LV_RES_OK; /*Return OK if the button is not deleted*/
}
//CHANGE HERE
static lv_res_t config_confirm_btn_click_action(lv_obj_t * btn){
  uint8_t id = lv_obj_get_free_num(btn);
  if(id == 1){

  }
  else if(id == 0){

  }
  config_menu();
  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t settings_btn_click_action(lv_obj_t * btn){
  uint8_t id = lv_obj_get_free_num(btn);
  switch(id){
    case 1:
    config_menu();
      break;//config
  }
  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t ddlist_action(lv_obj_t * ddlist)
{
    uint8_t id = lv_obj_get_free_num(ddlist);

    char sel_str[32];
    lv_ddlist_get_selected_str(ddlist, sel_str);

    return LV_RES_OK; /*Return OK if the drop down list is not deleted*/
}


static lv_res_t config_btn_click_action(lv_obj_t * btn){
  uint8_t motor_no = lv_obj_get_free_num(btn);
  motor_to_change = 1; // readPorts(motor_no - 1);
  current_screen = 12;
  lv_obj_t * config_btnm_scr = lv_obj_create(NULL, NULL);
  lv_scr_load(config_btnm_scr);
  const_buttons();
  int ypos = 30;
  int xpos = 60;

for(int i = 1; i <= 7; i++){
  lv_obj_t * port1 = lv_label_create(lv_scr_act(), NULL);
  char portName[2];
  sprintf(portName, "%d", i);
  lv_label_set_text(port1, portName);
  lv_obj_align(port1, NULL, LV_ALIGN_IN_TOP_LEFT, xpos, ypos);

  /*Create a normal button*/
  lv_obj_t * btnport1 = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(btnport1, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(btnport1, 50);
  lv_obj_set_width(btnport1, 50);
  lv_obj_align(btnport1, port1, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(btnport1, i);   /*Set a unique number for the button*/
  lv_btn_set_action(btnport1, LV_BTN_ACTION_CLICK, change_ports_action1);

  xpos = xpos + 60;
}
xpos = 60;
ypos = 90;
for(int i = 8; i <= 14; i++){
  lv_obj_t * port2 = lv_label_create(lv_scr_act(), NULL);
  char portName[2];
  sprintf(portName, "%d", i);
  lv_label_set_text(port2, portName);
  lv_obj_align(port2, NULL, LV_ALIGN_IN_TOP_LEFT, xpos, ypos);

  /*Create a normal button*/
  lv_obj_t * btnport2 = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(btnport2, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(btnport2, 50);
  lv_obj_set_width(btnport2, 50);
  lv_obj_align(btnport2, port2, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(btnport2, i);   /*Set a unique number for the button*/
  lv_btn_set_action(btnport2, LV_BTN_ACTION_CLICK, change_ports_action2);

  xpos = xpos + 60;
}

xpos = 60;
ypos = 150;
for(int i = 15; i <= 21; i++){
  lv_obj_t * port3 = lv_label_create(lv_scr_act(), NULL);
  char portName[2];
  sprintf(portName, "%d", i);
  lv_label_set_text(port3, portName);
  lv_obj_align(port3, NULL, LV_ALIGN_IN_TOP_LEFT, xpos, ypos);

  /*Create a normal button*/
  lv_obj_t * btnport3 = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(btnport3, false, false); /*Enable resizing horizontally and vertically*/
  lv_obj_set_height(btnport3, 50);
  lv_obj_set_width(btnport3, 50);
  lv_obj_align(btnport3, port3, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(btnport3, i);   /*Set a unique number for the button*/
  lv_btn_set_action(btnport3, LV_BTN_ACTION_CLICK, change_ports_action3);

  xpos = xpos + 60;
}

  return LV_RES_OK; /*Return OK if the button is not deleted*/
  }
