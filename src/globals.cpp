/**
 * \file globals.cpp
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#include "api.h"
#include "globals.h"

namespace nova {
    const std::string TEAM_NAME = "Nova";
    const std::string TEAM_NUMBER = "3388N";

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    pros::Motor frontLeft (1, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backBottomLeft (2, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backTopLeft (11, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor frontRight (9, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backBottomRight (10, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backTopRight (20, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    //pros::Motor backTracking (20, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::Motor_Group leftDrive ({frontLeft, backBottomLeft, backTopLeft});
    pros::Motor_Group rightDrive ({frontRight, backBottomRight, backTopRight});
    pros::Motor_Group drive ({frontLeft, backBottomLeft, backTopLeft, frontRight, backBottomRight, backTopRight});

    pros::Motor intake (6, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor lift (16, pros::E_MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor flywheel (8, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::ADIDigitalOut leftWing ('A', LOW);
    pros::ADIDigitalOut rightWing ('H', LOW);

    pros::Imu IMU (19);
}