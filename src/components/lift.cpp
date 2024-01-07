/**
 * \file arm.cpp
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#include "main.h"

void nova::Lift::initialize() {
    nova::lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    nova::lift.tare_position();
}

void nova::Lift::spinForward(int power) {
    nova::lift = power;
}

void nova::Lift::liftUp() {
    nova::lift.move_absolute(1800, 100);
}

void nova::Lift::liftDown() {
    nova::lift.move_absolute(-1800, 100);
}

void nova::Lift::toggle() {
    if (!this -> liftActive) this -> spinForward(127); else this -> spinForward(0);
    this -> liftActive = !this -> liftActive;
}

void nova::Lift::run() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        nova::lift = 127;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        nova::lift = -127;
    } else {
        nova::lift = 0;
    }
}