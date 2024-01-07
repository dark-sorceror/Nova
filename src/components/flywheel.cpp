/**
 * \file flywheel.cpp
 *
 * Updated - 1/6/2024
 * Last Successful Test - 1/5/2024
 */ 
 
#include "main.h"

void nova::Flywheel::initialize() {
    nova::flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    nova::flywheel.tare_position();
}

void nova::Flywheel::spinForward(int power) {
    nova::flywheel = power;
}

void nova::Flywheel::spinDuration(int duration) { // seconds
    int revolutions = duration * (600 * 60);
    int ticks = 300 * revolutions;

    nova::flywheel.move_absolute(ticks, 520);
}

void nova::Flywheel::toggle() {
    if (!this -> flywheelActive) this -> spinForward(127); else (this -> spinForward(0));
    this -> flywheelActive = !this -> flywheelActive;
}

void nova::Flywheel::run() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        nova::flywheel = 110;
    } else {
        nova::flywheel = 0;
    }
}