#include "../auton_functions/auton_functions.h"
#include "../configure/config.cpp"

void acceleration_test(){
  int time = 0;
  frontL.move_velocity(180);
  frontR.move_velocity(180);
  backL.move_velocity(180);
  backR.move_velocity(180);
  while(true){
    std::cout << "%d", frontL.get_actual_velocity();
    std::cout << "%d", frontR.get_actual_velocity();
    std::cout << "%d", backL.get_actual_velocity();
    std::cout << "%d \n", backR.get_actual_velocity();
    if(frontL.get_actual_velocity() >= 179){
      std::cout << "END \n";
      break;
    }
    time = time + 4;
    pros::delay(4);
  }
}
