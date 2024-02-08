/**
 * \file drive.cpp
 *
 * Updated - 1/10/2024
 * Last Successful Test - 1/10/2024
 */ 

#include "globals.h"
#include "main.h"
#include "pros/motors.h"

void nova::Drive::initialize() {
    nova::frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    nova::backBottomLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    nova::backTopLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    nova::frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    nova::backBottomRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    nova::backTopRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
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
    nova::IMU1.reset();
}

float nova::Drive::getAvgEncoderValue() {
    return (nova::frontLeft.get_position() + nova::backBottomLeft.get_position() + nova::backTopLeft.get_position() + nova::frontRight.get_position() + nova::backBottomRight.get_position() + nova::backTopRight.get_position())/6;
}

float nova::Drive::getAvgVelocity() {
    return (nova::frontLeft.get_actual_velocity() + nova::backBottomLeft.get_actual_velocity() + nova::backTopLeft.get_actual_velocity() + nova::frontRight.get_actual_velocity() + nova::backBottomRight.get_actual_velocity() + nova::backTopRight.get_actual_velocity())/6;
}

double nova::Drive::getIMURotation() {
    return nova::IMU1.get_rotation();
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

    master.print(0, 0, "%f", this->getIMURotation());
    //master.print(0, 0, "%f", this->getAvgEncoderValue());
}