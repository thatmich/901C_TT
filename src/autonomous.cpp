#include "main.h"
#include "configure/config.h"
#include "auton_functions/auton_functions.h"
#include "graphics/lvgl_functions.h"

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

  slewIncrease(12000);

  frontL.move_voltage(12000);
  frontR.move_voltage(12000);
  backL.move_voltage(12000);
  backR.move_voltage(12000);
  pros::delay(500);

  efrontL.reset();
  slewDecrease(0);
  printf("%f", efrontL.get());

  /*while(true)
  {

    //slewRate(12000);

    // printValues();

  }*/
  // tray.tare_position(); // Michio's PID Testing
  // tilterPID(720, 1);
  // pros::delay(1000);
  // printf("Tilter = %lf\n", tray.get_position());
  // printf("Velocity = %lf\n", tray.get_actual_velocity());

//  tilterPID(0, 4);
  // switch (autonNo){
  //   case 1:
  //   pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_HOLD);
  //   flipout();
  //   pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_BRAKE);
  //     rnjesus_red_unpro();
  //     break;
  //   case 2:
  //   pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_HOLD);
  //   flipout();
  //   pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_BRAKE);
  //     rnjesus_blue_unpro();
  //     break;
  //   case 3:
  //   pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_HOLD);
  //   flipout();
  //   pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_BRAKE);
  //     rnjesus_red_pro();
  //     break;
  //   case 4:
  //   pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_HOLD);
  //   pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_HOLD);
  //   flipout();
  //   pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_BRAKE);
  //   pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_BRAKE);
  //     rnjesus_blue_pro();
  //     break;
  //   case 5:
  //     one_point_lmao();
  //     break;
  //   case 6:
  //     break;
  //   case 7: // prog skills
  //     pushy();
  //     pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_HOLD);
  //     pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_HOLD);
  //     pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_HOLD);
  //     pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_HOLD);
  //
  //     pros::delay(100);
  //     flipout();
  //
  //     pros::delay(200);
  //     pros::c::motor_set_brake_mode(frontL_port, MOTOR_BRAKE_BRAKE);
  //     pros::c::motor_set_brake_mode(frontR_port, MOTOR_BRAKE_BRAKE);
  //     pros::c::motor_set_brake_mode(backL_port, MOTOR_BRAKE_BRAKE);
  //     pros::c::motor_set_brake_mode(backR_port, MOTOR_BRAKE_BRAKE);
  //     rnjesus_redskills();
  //     break;
  //
  // }
}
