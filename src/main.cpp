/**
 * \file main.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/10/2024
 */ 

#include "main.h"

nova::Drive drive = nova::Drive();
nova::Intake intake = nova::Intake();
nova::Lift lift = nova::Lift();
nova::Wings wings = nova::Wings();
nova::Flywheel flywheel = nova::Flywheel();
nova::Auton auton = nova::Auton(drive, intake, lift, flywheel, wings);
//nova::Odometry odometry = nova::Odometry();

std::map < std::pair < float, float >, std::string > autons = {
    {{0.0, 682.5}, "Nothing"},
    {{682.5, 1365.0}, "Far Side AWP"},
    {{1365.0, 2047.5}, "Far Side"},
    {{2047.5, 2730.0}, "Close Side AWP"},
    {{2730.0, 3412.5}, "Close Side"},
    {{3412.5, 4095.0}, "Skills"}
};

std::string autonSelection;

void autonSelectorUpdate() {
    while (1) {
        for (const auto& entry : autons) {
            if (auton.getAuton() >= entry.first.first && auton.getAuton() <= entry.first.second) {
                autonSelection = entry.second;
            }
        }

        lcd::print(3, "Auton Selected: %s", autonSelection);

        pros::delay(10);
    }
}

void initialize() {
    wings.close();
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
    wings.close();
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

    pros::Task autonSelectorRefresh(autonSelectorUpdate);

    autonomous();
}

void autonomous() {
    if (autonSelection == "Far Side AWP") auton.farSideAWP();
    else if (autonSelection == "Far Side") auton.farSide();
    else if (autonSelection == "Close Side AWP") auton.closeSideAWP();
    else if (autonSelection == "Close Side") auton.closeSide();
    else if (autonSelection == "Skills") auton.skills();
}

void opcontrol() {
	while (1) {
		drive.run();
        intake.run();
        lift.run();
        wings.run();
        flywheel.run();

        drive.getAvgEncoderValue();

		pros::delay(10);
	}
}