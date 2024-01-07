/**
 * \file globals.h
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */

#ifndef __GLOBALS
#define __GLOBALS

#include "api.h"

namespace nova {
    extern const std::string TEAM_NAME;
    extern const std::string TEAM_NUMBER;

    extern pros::Controller master;

    extern pros::Motor frontLeft;
    extern pros::Motor backBottomLeft;
    extern pros::Motor backTopLeft;
    extern pros::Motor frontRight;
    extern pros::Motor backBottomRight;
    extern pros::Motor backTopRight;
    extern pros::Motor backTracking;

    extern pros::Motor_Group leftDrive;
    extern pros::Motor_Group rightDrive;
    extern pros::Motor_Group drive;

    extern pros::Motor intake;
    extern pros::Motor lift;
    extern pros::Motor flywheel;
    
    extern pros::Imu IMU;

    extern pros::ADIDigitalOut leftWing;
    extern pros::ADIDigitalOut rightWing;
}

#endif