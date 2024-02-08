/**
 * \file globals.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/10/2024
 */ 

#include "api.h"
#include "globals.h"
#include "pros/adi.hpp"
#include "pros/rotation.hpp"

namespace nova {
    const std::string TEAM_NAME = "Nova";
    const std::string TEAM_NUMBER = "3388N";

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    pros::Motor frontLeft (1, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backBottomLeft (5, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backTopLeft (11, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor frontRight (3, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backBottomRight (10, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor backTopRight (20, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    //pros::Motor backTracking (20, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::Motor_Group leftDrive ({frontLeft, backBottomLeft, backTopLeft});
    pros::Motor_Group rightDrive ({frontRight, backBottomRight, backTopRight});
    pros::Motor_Group drive ({frontLeft, backBottomLeft, backTopLeft, frontRight, backBottomRight, backTopRight});

    pros::Motor intake (6, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor flywheel (16, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::ADIPotentiometer potentiometer ('E');
    pros::ADIDigitalOut backWings ('A', LOW);
    pros::ADIDigitalOut frontWings ('H', LOW);

    pros::Rotation a (3);

    pros::Imu IMU1 (9);
    //pros::Imu IMU2 (7);
}
