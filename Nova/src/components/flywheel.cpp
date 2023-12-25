/**
 * \file flywheel.cpp
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#include "main.h"

void nova::Flywheel::initialize() {
    nova::flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void nova::Flywheel::spinForward(int power) {
    nova::flywheel = power;
}

void nova::Flywheel::toggle() {
    if (!this -> flywheelActive) this -> spinForward(127); else (this -> spinForward(0));
    this -> flywheelActive = !this -> flywheelActive;
}

void nova::Flywheel::run() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) this -> toggle();
}