/**
 * \file flywheel.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/13/2024
 */ 
 
#include "main.h"
#include "pros/misc.h"

void nova::Flywheel::initialize() {
    nova::flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    nova::flywheel.tare_position();
}

void nova::Flywheel::spinDuration(int duration) { // seconds
    int revolutions = duration * (600 / 60);
    int ticks = 150 * revolutions;

    nova::flywheel.move_absolute(ticks, 520);
}

void nova::Flywheel::run() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) nova::flywheel.move_velocity(100);
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) nova::flywheel.move_velocity(200);
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) nova::flywheel.move_velocity(300);
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) nova::flywheel.move_velocity(400);
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) nova::flywheel.move_velocity(500);
    /*
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) nova::flywheel = 110;
    else nova::flywheel = 0;
    */
}