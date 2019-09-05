#include "config.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor frontL(1,false);
pros::Motor frontR(9, true);
pros::Motor backL(2,false);
pros::Motor backR(10, true);
pros::Motor intakeL(20,false);
pros::Motor intakeR(11, true);
pros::Motor tray(16, true);
pros::Motor lift(4, true);
