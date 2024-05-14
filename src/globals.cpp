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

    pros::v5::Controller master(pros::E_CONTROLLER_MASTER);

    pros::v5::Motor frontLeft (1, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::v5::Motor backBottomLeft (5, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::v5::Motor backTopLeft (11, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::v5::Motor frontRight (3, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::v5::Motor backBottomRight (10, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::v5::Motor backTopRight (20, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
    //pros::Motor backTracking (20, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::v5::MotorGroup leftDrive ({frontLeft, backBottomLeft, backTopLeft});
    pros::v5::MotorGroup rightDrive ({frontRight, backBottomRight, backTopRight});
    pros::v5::MotorGroup drive ({frontLeft, backBottomLeft, backTopLeft, frontRight, backBottomRight, backTopRight});

    pros::v5::Motor intake (6, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::v5::Motor flywheel (16, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::adi::Potentiometer potentiometer ('E');
    pros::adi::DigitalOut backWings ('A', LOW);
    pros::adi::DigitalOut frontWings ('H', LOW);
   
    pros::v5::Rotation a (3);

    pros::v5::Imu IMU1 (9);
    //pros::Imu IMU2 (7);
}
