/**
 * \file main.cpp
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#include "main.h"
#include "globals.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "selector.h"

nova::Drive drive = nova::Drive();
nova::Intake intake = nova::Intake();
nova::Lift lift = nova::Lift();
nova::Wings wings = nova::Wings();
nova::Flywheel flywheel = nova::Flywheel();
nova::Auton auton = nova::Auton(drive, intake, lift, flywheel, wings);
//nova::Odometry odometry = nova::Odometry();

void initialize() {
    drive.initialize();
    lift.initialize();
    intake.initialize();

    drive.resetIMU();
    drive.resetMotorEncoders();

    lcd::initialize();
	lcd::set_background_color(LV_COLOR_BLACK);
	lcd::set_text_color(LV_COLOR_GREEN);
    lcd::print(0, "%s", nova::TEAM_NAME);
    lcd::print(1, "%s", nova::TEAM_NUMBER);
}

void disabled() {}

void competition_initialize() {
    drive.initialize();
    lift.initialize();
    intake.initialize();

    drive.resetIMU();
    drive.resetMotorEncoders();

    selector::init();
    autonomous();
}

void autonomous() { 
    auton.skills();
}

void opcontrol() {
	while (true) {
		drive.run();
        intake.run();
        lift.run();
        wings.run();
        flywheel.run();
        
		pros::delay(10);
	}
}