/**
 * \file globals.cpp
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#include "api.h"

namespace nova {
    const std::string TEAM_NAME = "NOVA";
    const std::string TEAM_NUMBER = "3388N";

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    pros::Motor frontLeft (8, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backBottomLeft (9, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backTopLeft (10, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor frontRight (18, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backBottomRight (19, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backTopRight (20, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::Motor_Group leftDrive ({frontLeft, backBottomLeft, backTopLeft});
    pros::Motor_Group rightDrive ({frontRight, backBottomRight, backTopRight});
    pros::Motor_Group drive ({frontLeft, backBottomLeft, backTopLeft, frontRight, backBottomRight, backTopRight});

    pros::Motor flywheel (17, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor arm (16, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::ADIDigitalOut leftWing ('A', LOW);
    pros::ADIDigitalOut rightWing ('G', LOW);

    pros::Imu IMU (6);
}