/**
 * \file lift.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/13/2024
 */ 

#include "main.h"

void nova::Lift::initialize() {
    nova::lift.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    nova::lift.tare_position();
}

void nova::Lift::liftUp() {
    nova::lift.move_absolute(1800, 100);
}

void nova::Lift::liftDown() {
    nova::lift.move_absolute(-1800, 100);
}

void nova::Lift::autonStart() {
    nova::lift.move_absolute(-400, 100);
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