/**
 * \file globals.h
 *
 * Updated - 1/10/2024
 * Last Successful Test - 1/10/2024
 */

#ifndef __GLOBALS
#define __GLOBALS

#include "api.h"
#include "pros/rotation.hpp"

namespace nova {
    extern const std::string TEAM_NAME;
    extern const std::string TEAM_NUMBER;

    extern pros::v5::Controller master;

    extern pros::v5::Motor frontLeft;
    extern pros::v5::Motor backBottomLeft;
    extern pros::v5::Motor backTopLeft;
    extern pros::v5::Motor frontRight;
    extern pros::v5::Motor backBottomRight;
    extern pros::v5::Motor backTopRight;

    extern pros::v5::MotorGroup leftDrive;
    extern pros::v5::MotorGroup rightDrive;
    extern pros::v5::MotorGroup drive;

    extern pros::v5::Motor intake;
    extern pros::v5::Motor flywheel;

    extern pros::v5::Rotation a;
    
    extern pros::v5::Imu IMU1;
    //extern pros::Imu IMU2;

    extern pros::adi::Potentiometer potentiometer;
    extern pros::adi::DigitalOut frontWings;
    extern pros::adi::AnalogOut backWings;
}

#endif