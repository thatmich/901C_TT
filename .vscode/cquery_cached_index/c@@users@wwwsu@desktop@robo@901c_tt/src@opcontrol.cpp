#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor frontL(1);
	pros::Motor backL(2);
	pros::Motor frontR(9);
	pros::Motor backR(10);
	int left_joystick;
	int right_joystick;
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	int left;
	int right;
	while (true) {
		left_joystick = controller.get_analog(ANALOG_LEFT_Y);
 		right_joystick = controller.get_analog(ANALOG_RIGHT_X);
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
										 if(abs(left_joystick)>= 120 && abs(right_joystick) >= 120){
								  				left = 1.6*(left_joystick + right_joystick);
								  				right = 1.6*(left_joystick - right_joystick);
								  			}
								  			else if(abs(left_joystick)>= 120){
								  				left = 1.6*left_joystick + 0.8*right_joystick;
								  				right = 1.6*left_joystick - 0.8*right_joystick;
								  			}
								  			else if(abs(left_joystick)>= 15 || abs(right_joystick) >= 15){
								  				left = 0.8*(left_joystick + right_joystick);
								  				right = 0.8*(left_joystick - right_joystick);
								  			}
								  			else{
								  				left = 0;
								  				right = 0;
								  			}

								  			frontL.move_velocity(left);
								  			frontR.move_velocity(right);
								  			backL.move_velocity(-left);
								  			backR.move_velocity(-right);
		pros::delay(20);
	}
}
