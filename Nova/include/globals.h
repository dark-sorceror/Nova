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

    extern pros::Motor_Group leftDrive;
    extern pros::Motor_Group rightDrive;
    extern pros::Motor_Group driveMotors;

    extern pros::Motor flywheel;
    extern pros::Motor arm;
    
    extern pros::Imu IMU;

    extern pros::ADIDigitalOut leftWing;
    extern pros::ADIDigitalOut rightWing;
}

#endif