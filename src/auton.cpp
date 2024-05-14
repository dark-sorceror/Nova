/**
 * \file auton.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/10/2024
 */ 

#include "PID.hpp"
#include "components/flywheel.h"
#include "globals.h"
#include "auton.h"
#include "pros/rtos.hpp"
#include <iostream>
#include <map>
#include <list>

/*
1800 ticks/rev with 36:1 gears red
900 ticks/rev with 18:1 gears green
300 ticks/rev with 6:1 gears blue

144 inches x 144 inches field
omni wheel circumference =  2pi 3.25 inch = 20.42 inches / rev
*/

nova::Auton::Auton(Drive drive, Intake intake, Flywheel flywheel, Wings wings):
    drive(drive),
    intake(intake),
    flywheel(flywheel),
    wings(wings)
{};

float nova::Auton::getAuton() { return nova::potentiometer.get_value(); }

void nova::Auton::translate(float dist) {
    PID drivePID = PID(
        0, 
        1, 
        0.01, 
        5, 
        250, 
        50, 
        250, 
        5000
    );

    PID turnPID = PID(
        0, 
        4, 
        0.0, 
        1, 
        250
    );

    this -> drive.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float targetAngle = drive.getIMURotation();
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 4, MIN_STALL_TIME = 400;

    while (!(drivePID.isSettled())) {
        float driveError = targetPosition - this -> drive.getAvgEncoderValue();
        float turnError = targetAngle - drive.getIMURotation();

        float driveOutput = drivePID.compute(driveError);
        float turnOutput = turnPID.compute(turnError);

        float drivePower = driveOutput > 120 ? 120 : (driveOutput < -120 ? -120 : driveOutput);
        float turnPower = turnOutput > 120 ? 120 : (turnOutput < -120 ? -120 : turnOutput);

        nova::leftDrive = drivePower + turnPower;
        nova::rightDrive = drivePower - turnPower;

        pros::delay(10);

        if (drivePower > MIN_STALL_POWER && this -> drive.getAvgVelocity() < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }

    drivePID.reset();
    turnPID.reset();
}

void nova::Auton::rotate(float angle) {
    PID turnPID = PID(
        0, 
        4.75, 
        0.0, 
        28, 
        250, 
        5, 
        250, 
        3000
    );
    
    float targetPosition = this -> drive.getIMURotation() + angle;

    while (!(turnPID.isSettled())) {
        float error = targetPosition - this -> drive.getIMURotation();
        float power = turnPID.compute(error);

        nova::leftDrive = power;
        nova::rightDrive = -power;

        pros::delay(10);
    }

    turnPID.reset();
}

void nova::Auton::rotateAbsolute(float angle) {
    PID turnPID = PID(
        0, 
        4.75, 
        0.0, 
        28.0, 
        100, 
        5, 
        500, 
        3000
    );

    while (!(turnPID.isSettled())) {
        float error = angle - this -> drive.getIMURotation();
        float power = turnPID.compute(error);

        nova::leftDrive = power;
        nova::rightDrive = -power;

        pros::delay(10);
    }

    turnPID.reset();
}

void nova::Auton::swerveRight(float dist, float angle) {
    PID drivePID = PID(
        0, 
        1.5, 
        0.0, 
        8.5, 
        250, 
        50, 
        250, 
        5000
    );

    PID turnPID = PID(
        0, 
        0.1, 
        0.0, 
        1, 
        100
    );

    PID swingPID = PID(
        0, 
        3.0, 
        0.0, 
        2.0, 
        250,
        50, 
        250, 
        5000
    );

    master.print(0, 0, "%f", drive.getIMURotation());

    this -> drive.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float targetAngle = drive.getIMURotation();
    float targetSwerveAngle = drive.getIMURotation() - angle;
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 10, MIN_STALL_TIME = 400;

    while (!(swingPID.isSettled())) {
        float driveError = targetPosition - this-> drive.getAvgEncoderValue();
        float turnError = targetAngle - this-> drive.getIMURotation();
        float swerveError = targetSwerveAngle - this->drive.getIMURotation();

        float driveOutput = drivePID.compute(driveError);
        float turnOutput = turnPID.compute(turnError);
        float swerveOutput = swingPID.compute(swerveError);
        
        float drivePower = driveOutput > 500 ? 500 : driveOutput;
        float turnPower = turnOutput > 500 ? 500 : turnOutput;
        float swervePower = swerveOutput > 500 ? 500 : swerveOutput;

        nova::leftDrive = drivePower + turnPower;
        nova::rightDrive = drivePower - turnPower - swervePower;

        pros::delay(10);

        if (fabs(drivePower) < MIN_STALL_POWER && fabs(this -> drive.getAvgVelocity()) < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }
    
    nova::drive.brake();
    drivePID.reset();
    turnPID.reset();
    swingPID.reset();
}

void nova::Auton::swerveLeft(float dist, float angle) { 
     PID drivePID = PID(
        0, 
        1.5, 
        0.0, 
        8.5, 
        250, 
        50, 
        250, 
        5000
    );

    PID turnPID = PID(
        0, 
        0.1, 
        0.0, 
        1, 
        100
    );

    PID swingPID = PID(
        0, 
        3.0, 
        0.0, 
        2.0, 
        250,
        50, 
        250, 
        5000
    );

    master.print(0, 0, "%f", drive.getIMURotation());

    this -> drive.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float targetAngle = drive.getIMURotation();
    float targetSwerveAngle = drive.getIMURotation() + angle;
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 10, MIN_STALL_TIME = 400;

    while (!(swingPID.isSettled())) {
        float driveError = targetPosition - this-> drive.getAvgEncoderValue();
        float turnError = targetAngle - this-> drive.getIMURotation();
        float swerveError = targetSwerveAngle - this->drive.getIMURotation();

        float driveOutput = drivePID.compute(driveError);
        float turnOutput = turnPID.compute(turnError);
        float swerveOutput = swingPID.compute(swerveError);
        
        float drivePower = driveOutput > 500 ? 500 : driveOutput;
        float turnPower = turnOutput > 500 ? 500 : turnOutput;
        float swervePower = swerveOutput > 500 ? 500 : swerveOutput;

        nova::leftDrive = drivePower + turnPower + swervePower;
        nova::rightDrive = drivePower - turnPower;

        pros::delay(10);

        if (fabs(drivePower) < MIN_STALL_POWER && fabs(this -> drive.getAvgVelocity()) < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }
    
    nova::drive.brake();
    drivePID.reset();
    turnPID.reset();
    swingPID.reset();
}

void nova::Auton::farSideAWP() {
    intake.spinRevolutions(-3);
    translate(3);
    pros::delay(500);
    translate(11);
    wings.openBackWings();
    pros::delay(500);
    translate(-7);
    rotate(-135);
    rotate(135);
    wings.closeBackWings();
    translate(16);
    rotate(45);
    intake.spinRevolutions(3);
    pros::delay(500);
    rotate(180);
    translate(-15);
    translate(13);
    rotate(-45);
    translate(20);
    rotate(-45);
    rotateAbsolute(135);
    translate(37.5);
}

void nova::Auton::farSide() {
    translate(55);
    rotate(-90);
    translate(15);
    translate(-10);
    //rotate(90);
    /*
    // Front matching the black pole (straight line)
    // Facing the net
    translate(-10);
    translateRotate(30, 45);
    translateRotate(33, 45);
    translate(12);

    translateRotate(-14, 75);
    pros::delay(1000);
    rotateAbsolute(165);
    translate(-3);
    */
}

void nova::Auton::farSideElims() {
    wings.openFrontWings();
    pros::delay(500);
    wings.closeFrontWings();
    intake.spinRevolutions(-5);
    translate(51);
    wings.openFrontWings();
    rotate(60);
    translate(20);
    wings.closeFrontWings();
    swerveLeft(-20, -90);
    swerveLeft(-50, -90);
    rotateAbsolute(-120);
    
    translate(-26);
}

void nova::Auton::closeSideAWP() {
    wings.openFrontWings();
    pros::delay(500);
    wings.closeFrontWings();
    intake.spinRevolutions(-4);
    translate(67.14);
    rotate(130);
    wings.openFrontWings();
    pros::delay(500);
    translate(31.85);
    translate(-10);
    wings.closeFrontWings();
    rotate(135);
    intake.spinRevolutions(-4);
    pros::delay(500);
    translate(30.06);
    translate(-10);
    rotate(-100.55);
    translate(48);
    intake.spinRevolutions(2);
    rotate(-90);
    pros::delay(500);
    swerveLeft(-5, -135);
    intake.spinRevolutions(-4);
    translate(32);
    swerveRight(-30, -225);
    wings.openFrontWings();
    translate(18);
    wings.closeFrontWings();
    rotate(-45);
    translate(20);
   
}

void nova::Auton::closeSide() {
    swerveLeft(-10, 90);
    /*
    intake.spinRevolutions(-12);
    translate(-5);
    translate(8);
    translate(-36);
    rotate(-48);
    translate(-23);
    rotate(-48);
    translate(-17);
    translate(10);
    rotate(190);
    translate(15);
    translate(-10);
    rotate(-90);
    translate(46);
    intake.spinRevolutions(-5);
    pros::delay(500);
    translate(-46);
    rotate(90);
    translate(12);
    */
}

void nova::Auton::skills() {
    translate(-25.04);
    rotate(48.06);
    translate(-12.74);
    translate(12.09);
    rotate(-110);
    pros::delay(250);
    rotateAbsolute(-75);
    wings.openBackWings();
    translate(-3);

    flywheel.spinDuration(30);
    pros::delay(30000);
    nova::flywheel.brake();
    wings.closeBackWings();

    translate(4);
    rotateAbsolute(180);
    rotateAbsolute(180);
    translate(-23);
    rotate(-45);
    translate(-81.14);
    wings.openBackWings();
    rotate(-45);
    translate(-30.54);
    wings.closeBackWings();
    rotate(-48.76);
    rotate(180);
    translate(18.25);
    translate(-12);
    translate(18);

    rotateAbsolute(-135);
    translate(-3.38);
    rotate(90);
    translate(-49.93);
    wings.openBackWings();
    rotate(90.00);
    translate(-17.95);
    rotate(78.49);
    translate(-28.66);
    translate(10);
    translate(-10);
    rotateAbsolute(135);
    wings.closeBackWings();
    translate(24.97);
    rotate(-90);
    wings.openBackWings();
    translate(-17.17);
    rotate(77.72);
    translate(-28.58);
    translate(10);
    translate(-10);
    rotateAbsolute(135);
    wings.closeBackWings();
    translate(28.64);
    rotate(-90);
    wings.openBackWings();
    translate(-28.33);
    rotate(89.10);
    translate(-49.94);
    rotate(90);
    translate(5.20);
}