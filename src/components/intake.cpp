/**
 * \file flywheel.cpp
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#include "main.h"

void nova::Intake::initialize() {
    nova::intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    nova::intake.tare_position();
}

void nova::Intake::spinForward(int power) {
    nova::intake = power;
}

void nova::Intake::spinDistance(int revolutions) {
    float targetPosition = revolutions * 900; 
    nova::intake.move_absolute(targetPosition, 127);
}

void nova::Intake::toggle() { // ok we not using this 
    if (!this -> intakeActive) this -> spinForward(127); else (this -> spinForward(0));
    this -> intakeActive = !this -> intakeActive;
}

void nova::Intake::run() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        nova::intake = 127;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        nova::intake = -127;
    } else {
        nova::intake = 0;
    }
}

