#include "main.h"

#include <cmath>
#include "configure/config.h" // motor ports
#include "auton_functions/auton_functions.h"
#include "graphics/lvgl_functions.h"

void opcontrol() {
	int left_joystick;
	int right_joystick;
	int throttle;
	int turn;
	bool shift;
	bool r1;
	bool r2;
	bool l2;
	int right;
	int left;
	bool flipped = false;
	if(autonNo == 6 || autonNo == 5){
		flipout(); flipped = true;
	}

/* ---------- DECLARE TASKS -------------*/
	std::string param1("lift");
	std::string param2("tray");
	pros::Task task1(lift_task,&param1);
	pros::Task task2(tray_task,&param2);

	/* Print time and velocity */
	printf("Time Velocity");
	printf("\n");

	/* ---------- MAIN LOOP -------------*/

	while (true) {

		//Won's boosted printing velocity values
		printValues();

		/* ---------- DRIVE CODE -------------*/
		// declares joystick values
		left_joystick = controller.get_analog(ANALOG_LEFT_Y);
		right_joystick = controller.get_analog(ANALOG_RIGHT_X);
		shift = controller.get_digital(DIGITAL_L1);
		r1 = controller.get_digital(DIGITAL_R1);
		r2 = controller.get_digital(DIGITAL_R2);
		l2 = controller.get_digital(DIGITAL_L2);

		// declares motor stop type
		//pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_COAST);
		//pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_COAST);
		pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_COAST);
		pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_COAST);

		// revamped driver control, power of 2. see
		// https://www.desmos.com/calculator/vxnfti5dbk for drive graph

		// throttle is left y, turn is right x
		throttle = -1.5* pow(left_joystick/127, 2);
		turn = -1.5* pow(right_joystick/127, 2);
		left = throttle + turn;
		right = throttle - turn;

		// if too high, set to 200 rpm
		// if accidentally pressed (less than 800), don't move
		// if(left > 12000){
		// 	left = 12000;
		// }
		// else if(left < -12000){
		// 	left = -12000;
		// }
		// else if(abs(left) > 800){
		// 	left = 0;
		// }
		// if(right > 12000){
		// 	right = 12000;
		// }
		// else if(right < -12000){
		// 	right = -12000;
		// }
		// else if(abs(right) > 800){
		// 	right = 0;
		// }
		//
		// // assign values
		// frontL.move_voltage(left);
		// backL.move_voltage(left);
		// frontR.move_voltage(right);
		// backR.move_voltage(right);

		// if both joysticks are between 120 to 127, move forward and
		// turn at maximum speed
		if(abs(left_joystick)>= 120 && abs(right_joystick) >= 120){
			left = 1.6*(-left_joystick - right_joystick);
			right = 1.6*(-left_joystick + right_joystick);
		}

		// if only left joysticks is between 120 to 127, move forward at max speed,
		// turn at half speed
		// even if right joystick i
		else if(abs(left_joystick)>= 120){
			left = 1.6*(-left_joystick) - 0.8*right_joystick;
			right = 1.6*(-left_joystick) + 0.8*right_joystick;
		}

		// if only left joysticks is between 120 to 127, move forward at max speed,
		// turn at half speed
		else if(abs(left_joystick)>= 30 || abs(right_joystick) >= 30){
			left = 0.8*(-left_joystick - right_joystick);
			right = 0.8*(-left_joystick + right_joystick);
		}
		// move very slow when between 10 and 30
		else if(abs(left_joystick)>= 10 || abs(right_joystick) >= 10){
			left = 0.5*(-left_joystick - right_joystick);
			right = 0.5*(-left_joystick + right_joystick);
		}
		else{
			left = 0;
			right = 0;
		}

		pros::c::motor_set_brake_mode(lift_port, MOTOR_BRAKE_HOLD);
		pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_COAST);
		pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_COAST);


			if(shift && r1){

	      pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_HOLD);
	      pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_HOLD);
				 intakeL.move_velocity(80); // moves out
				 intakeR.move_velocity(80); // moves out
			}
			else if(r1){
				pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_HOLD);
	      pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_HOLD);
				intakeL.move_velocity(-200); // moves in
				intakeR.move_velocity(-200); // moves in
			}
			else if(controller.get_digital(DIGITAL_B)){
				pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_HOLD);
	      pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_HOLD);
				intakeL.move_velocity(80); // moves out
				intakeR.move_velocity(80); // moves out
			}
			else if(!stacking){
				intakeL.move_velocity(0); // stops
				intakeR.move_velocity(0); // stops
			}

		// assign left and right values to the motors

		frontL.move_velocity(left);
		frontR.move_velocity(right);
		backL.move_velocity(left);
		backR.move_velocity(right);


		// delay to prevent running this while loop too much
		pros::delay(20);
	}
}
