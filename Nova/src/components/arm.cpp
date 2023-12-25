/**
 * \file arm.cpp
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#include "main.h"

void nova::Arm::initialize() {
    nova::arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void nova::Arm::spinForward(int power) {
    nova::arm = power;
}

void nova::Arm::toggle() {
    if (!this -> armActive) this -> spinForward(127); else this -> spinForward(0);
    this -> armActive = !this -> armActive;
}

void nova::Arm::run() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) this -> toggle();
}