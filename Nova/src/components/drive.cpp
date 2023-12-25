/**
 * \file drive.cpp
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#include "main.h"

void nova::Drive::initialize() {
    nova::frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    nova::backBottomLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    nova::backTopLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    nova::frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    nova::backBottomRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    nova::backTopRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void nova::Drive::resetMotorEncoders() {
    nova::frontLeft.tare_position();
    nova::backBottomLeft.tare_position();
    nova::backTopLeft.tare_position();
    nova::frontRight.tare_position();
    nova::backBottomRight.tare_position();
    nova::backTopRight.tare_position();
}

void nova::Drive::resetIMU() {
    nova::IMU.reset();
}

double nova::Drive::getAvgEncoderValue() {
    return (nova::frontLeft.get_position() + nova::backBottomLeft.get_position() + nova::backTopLeft.get_position() + nova::frontRight.get_position() + nova::backBottomRight.get_position() + nova::backTopRight.get_position());
}

double nova::Drive::getIMURotation() {
    return nova::IMU.get_rotation();
}

void nova::Drive::run() {
    int x = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	int y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

    x = 0 ? (abs(x) <= this -> DEADBAND) : x;
    y = 0 ? (abs(y) <= this -> DEADBAND) : y;

    nova::frontLeft = y + x;
    nova::backBottomLeft = y + x;
    nova::backTopLeft = y + x;

    nova::frontRight = y - x;
    nova::backBottomRight = y - x;
    nova::backTopRight = y - x;
}