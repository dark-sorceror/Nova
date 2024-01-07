/**
 * \file auton.cpp
 *
 * Updated - 1/5/2024
 * Last Successful Test - 1/5/2924
 */ 

#include "PID.hpp"
#include "globals.h"
#include "auton.h"
#include "pros/rtos.hpp"
#include <cmath>

/*
1800 ticks/rev with 36:1 gears red
900 ticks/rev with 18:1 gears green
300 ticks/rev with 6:1 gears blue

144 inches x 144 inches field
omni wheel circumference =  2pi 3.25 inch = 20.42 inches / rev
*/

nova::Auton::Auton(Drive drive, Intake intake, Lift lift, Flywheel flywheel, Wings wings):
    drive(drive),
    intake(intake),
    lift(lift),
    flywheel(flywheel),
    wings(wings)
{};

void nova::Auton::translate(float dist) {
    this -> drive.resetMotorEncoders();
    PID drivePID = PID(0, 0.6, 0.0, 1.0, 250, 50, 300, 5000);

    float targetPosition = dist * 47.88245103; // dist * 300/2pir
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 4, MIN_STALL_TIME = 400;

    while (!(drivePID.isSettled())) {
        float error = targetPosition - this -> drive.getAvgEncoderValue();
        float power = drivePID.compute(error);

        nova::drive = power;
        pros::delay(10);

        if (power > MIN_STALL_POWER && this -> drive.getAvgVelocity() < MIN_STALL_VELOCITY) {
            timeSpentStalled += 10;
        } else {
            timeSpentStalled = 0;
        }

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }

    nova::drive.brake();
    drivePID.reset();
}

void nova::Auton::rotate(float angle) {
    float targetPosition = this -> drive.getIMURotation() + angle;
    PID turnPID = PID(0, 3.0, 0.0, 1.0, 100, 5, 400, 3000);

    while (!(turnPID.isSettled())) {
        float error = targetPosition - this -> drive.getIMURotation();
        float power = turnPID.compute(error);

        nova::leftDrive = power;
        nova::rightDrive = -power;

        pros::delay(10);
    }

    nova::drive.brake();
    turnPID.reset();
}
/*
void nova::Auton::drift(float angle) {
    float targetPosition = this -> drive.getIMURotation() + angle;

    while (!(this -> swingPID.isSettled())) {
        float error = targetPosition - this -> drive.getIMURotation();
        float power = this -> swingPID.compute(error);

        if (angle > 0) nova::leftDrive = power;
        else nova::rightDrive = power;

        pros::delay(10);
    }

    nova::drive.brake();
    this -> swingPID.reset();
}
*/
void nova::Auton::closeSide() {
    this -> translate(50);
    this -> rotate(90);
    intake.spinDistance(4); // output
    this -> rotate(160);
    this -> translate(32);
    intake.spinDistance(4); // input
    this -> rotate(-195);
    intake.spinDistance(4); //output
    this -> rotate(-98);
    intake.spinDistance(4); // input
    this -> translate(15);
    this -> rotate(-50);
    this -> translate(-35);
    this -> rotate(180);
    intake.spinDistance(4); // output
    this -> translate(15);
    this -> rotate(-50);
    this -> translate(-46);
    this -> rotate(50);
    this -> translate(-6);
    wings.open();
}

void nova::Auton::farSide() {
    this->translate(60);
    intake.spinDistance(8);
    this -> translate(-12);
    //pros::delay(2000);
}

void nova::Auton::skills() {
    this -> translate(18);
    this -> rotate(90);
    this -> translate(-30);
    wings.open();
    lift.liftUp();
    flywheel.spinDuration(30);
    pros::delay(30000);
    lift.liftDown();
    this -> translate(7);
    wings.close();
    //flywheel.spinDuration(35);
    this -> rotate(-135);
    this -> translate(-32);
    this -> rotate(-45);
    this -> translate(-85);
    this -> rotate(-45);
    this -> translate(-30);
    this -> translate(10);
    this -> translate(-15);
    this -> translate(8);
    this -> rotate(-95);
    this -> translate(-45);
    this -> rotate(90);
    this -> translate(-40);
    this -> rotate(100);
    wings.open();
    this -> translate(-35);
    this -> translate(7);
    this -> translate(-12);
    this -> translate(7);
    this -> rotate(20);
    this -> translate(35);
    this -> translate(-35);
    this -> translate(5);
    wings.close();
}

/*

float nova::Auton::getLineLength(sLine line) {
    float x = line.p2.x - line.p1.x;
    float y = line.p2.y - line.p1.y;

    return sqrt(x * x + y * y);
}

float nova::Auton::getLineAngle(sLine line) {
    return atan2(line.p2.x - line.p1.x, line.p2.y - line.p1.y);
}

float nova::Auton::nearAngle(float angle, float reference) {
    return round((reference - angle) / (2 * 3.14159265)) * (2 * 3.14159265) + angle;
}

void nova::Auton::moveTo(float x, float y, float xs, float ys, int power) {
    this -> target.x = x;
    this -> target.y = y;

    sLine path;
    
    path.p1.x = xs;
    path.p1.y = ys;
    path.p2.x = x;
    path.p2.y = y;

    float length = this -> getLineLength(path);
    float angle = this -> getLineAngle(path);
    float anglePID = this -> nearAngle(angle - (power < 0 ? 3.14159265 : 0), this -> botPosition.angle);

    sVector currentPosVector;
    sPolar currentPosPolar;
}
*/
