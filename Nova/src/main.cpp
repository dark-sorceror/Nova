/**
 * \file main.cpp
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#include "main.h"

nova::Drive drive = nova::Drive();
nova::Arm arm = nova::Arm();
nova::Flywheel flywheel = nova::Flywheel();
nova::Wings wings = nova::Wings();

void initialize() {
    drive.initialize();
    arm.initialize();
    flywheel.initialize();

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
    arm.initialize();
    flywheel.initialize();

    drive.resetIMU();
    drive.resetMotorEncoders();

    autonomous();
}

void autonomous() {
    //autonFar(); TODO: entire autonomous :skull:
}

void opcontrol() {
	while (true) {
		drive.run();

        flywheel.run();
        arm.run();
        wings.run();
        
		pros::delay(10);
	}
}