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
  intakeL.move_velocity(30);
  intakeR.move_velocity(30);
  pros::delay(1000);
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
  tray_motor.setMaxVelocity(80);
  tray_motor.setTarget(1400);
  tray_motor.waitUntilSettled();
  intakeL.move_velocity(30);
  intakeR.move_velocity(30);
  tray_motor.setTarget(400);
  pros::delay(400);
  chassis.moveDistance(15_in);
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
}

void rnjesus_red(){
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
  frontL.move_relative(-400,80);
  frontR.move_relative(400,80);
  backL.move_relative(-400,80);
  backR.move_relative(400,80);
  pros::delay(1000);
  chassis.moveDistance(-10.5_in);
  intakeL.move_velocity(30);
  intakeR.move_velocity(30);
  pros::delay(1000);
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
  tray_motor.setMaxVelocity(80);
  tray_motor.setTarget(1400);
  tray_motor.waitUntilSettled();
  intakeL.move_velocity(30);
  intakeR.move_velocity(30);
  tray_motor.setTarget(400);
  pros::delay(400);
  chassis.moveDistance(15_in);
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
}
