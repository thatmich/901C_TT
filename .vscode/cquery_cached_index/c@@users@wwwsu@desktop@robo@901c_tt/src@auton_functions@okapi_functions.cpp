#include "../configure/config.h"
#include "auton_functions.h"

using namespace okapi;

const auto WHEEL_DIAMETER = 4_in;
const auto CHASSIS_WIDTH = 0_in;

auto chassis = ChassisControllerFactory::create(
  {-10, -9},
  {2, 1},
  AbstractMotor::gearset::green * 0.8,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);

auto lift_motor = AsyncControllerFactory::posIntegrated(lift_port);
auto tray_motor = AsyncControllerFactory::posIntegrated(tray_port);

void one_point_lmao(){
  chassis.setMaxVelocity(80);
  frontL.tare_position();
  frontR.tare_position();
  backL.tare_position();
  backR.tare_position();
  chassis.moveDistance(-50_cm);
  pros::delay(1000);
  chassis.moveDistance(50_cm);
}

void hohoho(){
  chassis.setMaxVelocity(80);
  frontL.tare_position();
  frontR.tare_position();
  backL.tare_position();
  backR.tare_position();
  chassis.moveDistance(-50_cm);
  pros::delay(1000);
  chassis.moveDistance(50_cm);
}

void flipout(){
  // lift up halfway -600d
  // tilter forwards -300
  lift_motor.setTarget(400);
  tray_motor.setTarget(200);
  tray_motor.waitUntilSettled();
  lift_motor.setTarget(600);
  lift_motor.waitUntilSettled();
  pros::delay(400);
  lift_motor.setTarget(0);
  tray_motor.setTarget(0);
  lift_motor.waitUntilSettled();

  // lift.move_velocity(100);
  // while(lift.get_position()<1200)
  //   {
  //     lift.move_velocity(100);
  //     pros::delay(50);
  //   };
  // tray.move_relative(200,-100);
  // pros::delay(500);
  // while(lift.get_position()<1600)
  //   {
  //     lift.move_velocity(100);
  //     pros::delay(50);
  //   };
  // lift.move_absolute(0, -100);
  // tray.move_absolute(0, 100);
}

void pushy(){
  chassis.setMaxVelocity(60);
  chassis.moveDistance(-8_in);
  chassis.waitUntilSettled();
  chassis.moveDistance(8.5_in);
  pros::delay(200);
}

void rnjesus_blue(){
  chassis.setMaxVelocity(80);
  frontL.tare_position();
  frontR.tare_position();
  backL.tare_position();
  backR.tare_position();
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in
  chassis.moveDistance(-44_in);
  intakeL.move_velocity(0); // moves in
  intakeR.move_velocity(0); // moves in
  chassis.moveDistance(28_in);
  chassis.waitUntilSettled();
  frontL.move_relative(400,80);
  frontR.move_relative(-400,80);
  backL.move_relative(400,80);
  backR.move_relative(-400,80);
  pros::delay(1000);
  chassis.moveDistance(-10.5_in);
  intakeL.move_relative(270,30);
  intakeR.move_relative(270,30);
  pros::delay(1000);
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
  tray_motor.setMaxVelocity(80);
  tray_motor.setTarget(1000);
  tray_motor.waitUntilSettled();
  chassis.moveDistance(-2.5_in);
  chassis.waitUntilSettled();
  tray_motor.setTarget(1200);
  tray_motor.waitUntilSettled();
  intakeL.move_velocity(30);
  intakeR.move_velocity(30);
  tray_motor.setTarget(400);
  pros::delay(1000);
  chassis.moveDistance(15_in);
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
}

void stack(){
  // while(tray_light.get_value()>2300){
  //   intakeL.move(20);
  //   intakeR.move(20);
  //   pros::delay(20);
  // }
  //intakeL.move_relative(200, 50);
  //intakeR.move_relative(200, 50);
  tray_motor.setMaxVelocity(100);
  tray_motor.setTarget(1000);
  tray_motor.waitUntilSettled();
  chassis.waitUntilSettled();
  tray_motor.setMaxVelocity(80);
  tray_motor.setTarget(1200);
  tray_motor.waitUntilSettled();
}

void run_for(int speed, int time){
  frontL.move_velocity(speed);
  frontR.move_velocity(speed);
  backL.move_velocity(speed);
  backR.move_velocity(speed);
  pros::delay(time);
  frontL.move_velocity(0);
  frontR.move_velocity(0);
  backL.move_velocity(0);
  backR.move_velocity(0);

}

void rnjesus_redskills(){
  chassis.setMaxVelocity(80);
  frontL.tare_position();
  frontR.tare_position();
  backL.tare_position();
  backR.tare_position();
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in
  chassis.moveDistance(-62_in);
  chassis.waitUntilSettled();
  chassis.setMaxVelocity(80);

  intakeL.move_velocity(0); // moves in
  intakeR.move_velocity(0); // moves in
  frontL.tare_position();
  frontR.tare_position();
  backL.tare_position();
  backR.tare_position();
  chassis.moveDistance(59_in);
  chassis.waitUntilSettled();
  run_for(50, 1000);


  chassis.setMaxVelocity(50);
  frontL.tare_position();
  frontR.tare_position();
  backL.tare_position();
  backR.tare_position();
  chassis.moveDistance(-24_in);
  chassis.waitUntilSettled();
  frontL.tare_position();
  frontR.tare_position();
  backL.tare_position();
  backR.tare_position();

  pros::delay(300);

  frontL.move_relative(-440,40);
  frontR.move_relative(440,40);
  backL.move_relative(-440,40);
  backR.move_relative(440,40);
  pros::delay(3000);
  intakeL.move_velocity(0); // moves in
  intakeR.move_velocity(0); // moves in
  run_for(-80, 1200);
  pros::delay(100);
  chassis.moveDistance(2.5_in);
  chassis.waitUntilSettled();
  stack();
  chassis.moveDistance(10_in);
  chassis.waitUntilSettled();
  tray_motor.setTarget(10);
  pros::delay(2000);
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
}


void rnjesus_red(){
  chassis.setMaxVelocity(100);
  frontL.tare_position();
  frontR.tare_position();
  backL.tare_position();
  backR.tare_position();
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in
  chassis.moveDistance(-50_in);
  pros::delay(100);
  intakeL.move_velocity(-50); // moves in
  intakeR.move_velocity(-50); // moves in
  chassis.moveDistance(34_in);
  chassis.waitUntilSettled();

  intakeL.move_velocity(0); // moves in
  intakeR.move_velocity(0); // moves in
  frontL.move_relative(-400,80);
  frontR.move_relative(400,80);
  backL.move_relative(-400,80);
  backR.move_relative(400,80);
  pros::delay(1000);
  chassis.moveDistance(-10.5_in);
  intakeL.move_relative(700,40);
  intakeR.move_relative(700,40);
  pros::delay(1000);
  tray_motor.setMaxVelocity(100);
  tray_motor.setTarget(1000);
  tray_motor.waitUntilSettled();
  chassis.moveDistance(-3.0_in);
  chassis.waitUntilSettled();
  tray_motor.setMaxVelocity(50);
  tray_motor.setTarget(1300);
  tray_motor.waitUntilSettled();
  pros::delay(100);
  intakeL.move_velocity(30);
  intakeR.move_velocity(30);

  pros::delay(700);
  tray_motor.setMaxVelocity(100);
  tray_motor.setTarget(500);
  pros::delay(1000);
  chassis.moveDistance(15_in);
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
}

void lift_task(void* param){
  lift_motor.setMaxVelocity(100);
  while(true){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
      lift_motor.setTarget(700);
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
    lift_motor.setTarget(900);
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
    lift_motor.setTarget(700);
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    lift.move_velocity(200); // up
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    lift.move_velocity(-120); // up
  }
  else{
    pros::c::motor_set_brake_mode(lift_port, MOTOR_BRAKE_HOLD);
    lift.move_velocity(0);
  }

  pros::delay(10);
}

}

void tray_task(void* param){
  tray_motor.setMaxVelocity(100);
  while(true){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) || controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) || controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
      tray_motor.setTarget(300);
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
    tray.move_velocity(200); // up
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    tray.move_velocity(-200); // up
  }
  else{
    pros::c::motor_set_brake_mode(tray_port, MOTOR_BRAKE_HOLD);
    tray.move_velocity(0);
  }

  pros::delay(10);
}

}
