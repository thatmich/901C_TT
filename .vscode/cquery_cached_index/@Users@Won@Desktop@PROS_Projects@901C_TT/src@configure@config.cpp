#include "config.h"

// declares controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

const int frontL_port = 12;
const int frontR_port = 18;
const int backL_port = 13;
const int backR_port = 19;
const int intakeL_port = 1;
const int intakeR_port = 3;
const int tray_port = 4;
const int lift_port = 2;
const int lift_limit_port = 1;
const int auton_limit_port = 8;

// declares motor port and whether it is reversed
pros::Motor frontL(frontL_port,false);
pros::Motor frontR(frontR_port, true);
pros::Motor backL(backL_port,true);
pros::Motor backR(backR_port, false);
pros::Motor intakeL(intakeL_port,true);
pros::Motor intakeR(intakeR_port, false);
pros::Motor tray(tray_port, true);
pros::Motor lift(lift_port, true);
//pros::ADIDigitalIn lift_limit (lift_limit_port);
pros::ADIDigitalIn auton_limit (auton_limit_port);
