/**
 * \file intake.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/13/2024
 */ 

#include "main.h"

void nova::Intake::initialize() {
    nova::intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    nova::intake.tare_position();
}

void nova::Intake::spinRevolutions(int revolutions) {
    float targetPosition = revolutions * 900; 
    nova::intake.move_absolute(targetPosition, 127);
}

void nova::Intake::run() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) nova::intake = 127;
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) nova::intake = -127;
    else nova::intake = 0;
}

