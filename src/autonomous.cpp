#include "main.h"
#include "configure/config.h"
#include "auton_functions/auton_functions.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  //one_point_lmao();
  pushy();
  pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_HOLD);
  pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_HOLD);
  pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_HOLD);
  pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_HOLD);
  flipout();
  pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_BRAKE);
  pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_BRAKE);
  pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_BRAKE);
  pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_BRAKE);
  rnjesus_redskills();
}
