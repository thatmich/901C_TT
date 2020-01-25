#include "../configure/config.h"
#include "auton_functions.h"

using namespace okapi;

const auto WHEEL_DIAMETER = 4_in;
const auto CHASSIS_WIDTH = 17_in;

auto chassis = ChassisControllerFactory::create(
  {-10, -9},
  {2, 1},
  AbstractMotor::gearset::green * 0.8,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);


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


bool stacking;

auto lift_motor = AsyncControllerFactory::posIntegrated(lift_port);
auto tray_motor = AsyncControllerFactory::posIntegrated(tray_port);

void flipout(){
  lift_motor.setTarget(400);
  tray_motor.setMaxVelocity(100);
  tray_motor.setTarget(200);
  tray_motor.waitUntilSettled();
  lift_motor.setTarget(600);
  lift_motor.waitUntilSettled();
  pros::delay(400);
  tray_motor.setMaxVelocity(60);
  lift_motor.setTarget(0);
  tray_motor.setTarget(0);
  lift_motor.waitUntilSettled();
  lift.move_velocity(-100);
  pros::delay(200);
  lift.move_velocity(0);
}

void tare(){
  frontL.tare_position();
  frontR.tare_position();
  backL.tare_position();
  backR.tare_position();
}



void stack(void *param){
  stacking = true;
  int thing = 0;
  intakeR.move_velocity(0);
  intakeL.move_velocity(0);
  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_COAST);
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_COAST);
  tray_motor.setMaxVelocity(100);
  tray_motor.setTarget(1100);
  while(stacking){
    tray_motor.waitUntilSettled();
    thing ++;
    if(thing >= 2000){

      tray_motor.setTarget(tray.get_position());
      stacking = false;
    }
  }
  stacking = false;
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


void pushy(){
  run_for(-50, 1000);
  run_for(50, 1200);
}

void red_unpro(){
  // setup
  // move forward is negative, move backwards is positive
  chassis.setMaxVelocity(80);
  tare();
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_HOLD);
  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_HOLD);

  // move forwards
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in
  chassis.moveDistance(-52_in);
  chassis.waitUntilSettled();

  pros::delay(200); // delay for last cube to get sucked in

  // stops intakes
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);

  // goes back
  chassis.setMaxVelocity(80);
  tare();
  chassis.moveDistance(28_in);
  chassis.waitUntilSettled();

  tare();
  chassis.turnAngle(125_deg); // turn to stack
  chassis.waitUntilSettled();

  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_COAST);
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_COAST);
  intakeL.move_relative(300, 100);
  intakeR.move_relative(300, 100);

  chassis.moveDistance(-12.5_in); // move forwards to align stack
  chassis.waitUntilSettled();

  tray_motor.setMaxVelocity(80);
  tray_motor.setTarget(1200);
  tray_motor.waitUntilSettled();
  run_for(-40,1000);
  pros::delay(200);
  tare();
  tray_motor.setTarget(1050);
  pros::delay(300);
  chassis.moveDistance(11_in);
  tray_motor.setTarget(10);
  tray_motor.waitUntilSettled();
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
}

void rnjesus_blue_unpro(){
  // setup
  // move forward is negative, move backwards is positive
  chassis.setMaxVelocity(80);
  tare();
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_HOLD);
  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_HOLD);

  // move forwards
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in
  chassis.moveDistance(-52_in);
  chassis.waitUntilSettled();

  pros::delay(200); // delay for last cube to get sucked in

  // stops intakes
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);

  // goes back
  chassis.setMaxVelocity(80);
  tare();
  chassis.moveDistance(28_in);
  chassis.waitUntilSettled();

  tare();
  chassis.turnAngle(-127_deg); // turn to stack
  chassis.waitUntilSettled();

  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_COAST);
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_COAST);
  intakeL.move_relative(300, 100);
  intakeR.move_relative(300, 100);

  run_for(300, 60);
  chassis.moveDistance(3.5_in); // move forwards to align stack
  chassis.waitUntilSettled();

  tray_motor.setMaxVelocity(80);
  tray_motor.setTarget(1200);
  tray_motor.waitUntilSettled();
  run_for(-40,2000);
  pros::delay(200);
  tare();
  tray_motor.setTarget(1150);
  pros::delay(300);
  chassis.moveDistance(11_in);
  tray_motor.setTarget(10);
  tray_motor.waitUntilSettled();
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
}

void rnjesus_blue_pro(){
  // setup
  // move forward is negative, move backwards is positive
  chassis.setMaxVelocity(80);
  tare();
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_HOLD);
  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_HOLD);

  // move forwards
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in
  chassis.moveDistance(-46_in);
  chassis.waitUntilSettled();

  pros::delay(200); // delay for last cube to get sucked in
  tare();
  intakeL.move_velocity(0); // moves in
  intakeR.move_velocity(0); // moves in
  chassis.turnAngle(125_deg); // turn to stack
  chassis.waitUntilSettled();

  chassis.moveDistance(-25_in);
  chassis.waitUntilSettled();
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in

  chassis.turnAngle(8_deg); // turn to stack
  chassis.waitUntilSettled();
  pros::delay(200);
  chassis.moveDistance(-19.5_in);
  chassis.waitUntilSettled();

  intakeL.move_velocity(0); // moves in
  intakeR.move_velocity(0); // moves in


  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_COAST);
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_COAST);
  intakeL.move_relative(600, 100);
  intakeR.move_relative(600, 100);


  tray_motor.setMaxVelocity(80);
  tray_motor.setTarget(1200);
  tray_motor.waitUntilSettled();
  run_for(-40,200);
  pros::delay(500);
  chassis.moveDistance(11_in);
  tray_motor.setTarget(10);
  tray_motor.waitUntilSettled();
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
}

void rnjesus_red_pro(){
  // setup
  // move forward is negative, move backwards is positive
  chassis.setMaxVelocity(80);
  tare();
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_HOLD);
  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_HOLD);

  // move forwards
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in
  chassis.moveDistance(-46_in);
  chassis.waitUntilSettled();

  pros::delay(200); // delay for last cube to get sucked in
  tare();
  intakeL.move_velocity(0); // moves in
  intakeR.move_velocity(0); // moves in
  chassis.turnAngle(-125_deg); // turn to stack
  chassis.waitUntilSettled();

  chassis.moveDistance(-25_in);
  chassis.waitUntilSettled();
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in

  chassis.turnAngle(-8_deg); // turn to stack
  chassis.waitUntilSettled();
  pros::delay(200);
  chassis.moveDistance(-19.5_in);
  chassis.waitUntilSettled();

  intakeL.move_velocity(0); // moves in
  intakeR.move_velocity(0); // moves in


  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_COAST);
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_COAST);
  intakeL.move_relative(600, 100);
  intakeR.move_relative(600, 100);


  tray_motor.setMaxVelocity(80);
  tray_motor.setTarget(1200);
  tray_motor.waitUntilSettled();
  run_for(-40,200);
  pros::delay(500);
  chassis.moveDistance(11_in);
  tray_motor.setTarget(10);
  tray_motor.waitUntilSettled();
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
}

void rnjesus_redskills(){
  // setup
  // move forward is negative, move backwards is positive
  chassis.setMaxVelocity(80);
  tare();
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_HOLD);
  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_HOLD);

  // move forwards
  intakeL.move_velocity(-200); // moves in
  intakeR.move_velocity(-200); // moves in
  chassis.moveDistance(-48_in);
  chassis.waitUntilSettled();

  pros::delay(200); // delay for last cube to get sucked in

  // stops intakes
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);

  // goes back
  chassis.setMaxVelocity(80);
  tare();
  chassis.moveDistance(44_in);
  chassis.waitUntilSettled();
  run_for(100, 500);


  chassis.setMaxVelocity(50);
  tare();
  chassis.moveDistance(-24_in);
  chassis.waitUntilSettled();

  pros::delay(50); // delay for a bit

  tare();
  chassis.turnAngle(125_deg); // turn to stack
  chassis.waitUntilSettled();

  pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_COAST);
  pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_COAST);
  intakeL.move_relative(300, 100);
  intakeR.move_relative(300, 100);

  chassis.moveDistance(-12.5_in); // move forwards to align stack
  chassis.waitUntilSettled();

  tray_motor.setMaxVelocity(80);
  tray_motor.setTarget(1200);
  tray_motor.waitUntilSettled();
  run_for(-40,1000);
  pros::delay(200);
  tare();
  tray_motor.setTarget(1050);
  pros::delay(300);
  chassis.moveDistance(9_in);
  tray_motor.setTarget(10);
  tray_motor.waitUntilSettled();
  chassis.waitUntilSettled();
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);


  // after stacking
  chassis.moveDistance(8_in);
  chassis.waitUntilSettled();
  chassis.turnAngle(140_deg);
  chassis.waitUntilSettled();
  intakeL.move_velocity(-100);
  intakeR.move_velocity(-100);
  chassis.moveDistance(-18_in);
  chassis.waitUntilSettled();
  run_for(-50, 600);
  pros::delay(1000); // wait for intake
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
  chassis.moveDistance(4_in);
  chassis.waitUntilSettled();
  intakeL.move_velocity(100);
  intakeR.move_velocity(100);
  pros::delay(400);
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);


  lift_motor.setMaxVelocity(200);
  lift_motor.setTarget(1100);
  tray_motor.setMaxVelocity(200);
  tray_motor.setTarget(550);
  lift_motor.waitUntilSettled();
  tray_motor.waitUntilSettled();
  chassis.moveDistance(-9_in);
  intakeL.move_velocity(80);
  intakeR.move_velocity(80);
  pros::delay(1000);
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
  chassis.setMaxVelocity(20);
  chassis.moveDistance(4_in);
  chassis.waitUntilSettled();


  lift_motor.setTarget(500);
  lift_motor.waitUntilSettled();
  lift_motor.setTarget(0);
  tray_motor.setTarget(0);
  lift_motor.waitUntilSettled();
  lift.move_velocity(-100);
  pros::delay(200);
  lift.move_velocity(0);
  chassis.setMaxVelocity(80);
  chassis.moveDistance(20_in);
  chassis.waitUntilSettled();
  chassis.turnAngle(90_deg);
  chassis.waitUntilSettled();


  intakeL.move_velocity(-100);
  intakeR.move_velocity(-100);
  chassis.moveDistance(-30_in);
  chassis.waitUntilSettled();
  run_for(-50, 600);
  pros::delay(1000); // wait for intake
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
  chassis.moveDistance(4_in);
  chassis.waitUntilSettled();
  intakeL.move_velocity(100);
  intakeR.move_velocity(100);
  pros::delay(400);
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);


  lift_motor.setMaxVelocity(200);
  lift_motor.setTarget(800);
  tray_motor.setMaxVelocity(200);
  tray_motor.setTarget(550);
  lift_motor.waitUntilSettled();
  tray_motor.waitUntilSettled();
  chassis.moveDistance(-9_in);
  intakeL.move_velocity(80);
  intakeR.move_velocity(80);
  pros::delay(1000);
  intakeL.move_velocity(0);
  intakeR.move_velocity(0);
  chassis.setMaxVelocity(20);
  chassis.moveDistance(4_in);
  chassis.waitUntilSettled();



}


void lift_task(void* param){
  lift_motor.setMaxVelocity(100);
  while(true){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
      lift_motor.setMaxVelocity(200);
      lift_motor.setTarget(1100);
      lift_motor.waitUntilSettled();
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
    lift_motor.setMaxVelocity(200);
    lift_motor.setTarget(860);
    lift_motor.waitUntilSettled();
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    lift.move_velocity(200); // up
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    lift.move_velocity(-120); // up
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
    lift_motor.setTarget(200);
    lift_motor.waitUntilSettled();
    lift_motor.setTarget(0);
    lift_motor.waitUntilSettled();
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
  stacking = false;
  pros::c::motor_set_brake_mode(tray_port, MOTOR_BRAKE_HOLD);
  while(true){
    if(!stacking){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
      tray_motor.setMaxVelocity(200);
      tray_motor.setTarget(550);
      tray_motor.waitUntilSettled();
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
    tray_motor.setMaxVelocity(200);
    tray_motor.setTarget(550);
    tray_motor.waitUntilSettled();
}
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
    tray.move_velocity(100); // up

  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) || stacking){
    std::string param3("stack");
  	pros::Task task3(stack,&param3);
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
    tray_motor.setTarget(200);
    tray_motor.waitUntilSettled();
    tray_motor.setTarget(0);
    tray_motor.waitUntilSettled();
  }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
      tray.move_velocity(-200); // up
  }
  else{
    // pros::c::motor_set_brake_mode(tray_port, MOTOR_BRAKE_HOLD);
    // pros::c::motor_set_brake_mode(intakeR_port, MOTOR_BRAKE_HOLD);
    // pros::c::motor_set_brake_mode(intakeL_port, MOTOR_BRAKE_HOLD);
    tray.move_velocity(0);
  }

}
  pros::delay(10);
}

}
