#include "config.h"

// declares controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

const int frontL_port = 10;
const int frontR_port = 2;
const int backL_port = 9;
const int backR_port = 1;
const int intakeL_port = 16;
const int intakeR_port = 11;
const int tray_port = 20;
const int lift_port = 19;
const int limit_port = 1;

// declares motor port and whether it is reversed
pros::Motor frontL(frontL_port,false); //bruh
pros::Motor frontR(frontR_port, true);
pros::Motor backL(backL_port,true);
pros::Motor backR(backR_port, false);
pros::Motor intakeL(intakeL_port,false);
pros::Motor intakeR(intakeR_port, true);
pros::Motor tray(tray_port, true);
pros::Motor lift(lift_port, true);
