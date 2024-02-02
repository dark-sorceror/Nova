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

float nova::Auton::getAuton() { return nova::potentiometer.get_value(); }

void nova::Auton::translateRotate(float dist, float angle) {
    PID drivePID = PID(
        0, 
        1.5, 
        0.0, 
        8.5, 
        250, 
        50, 
        0, 
        5000
    );

    PID headingPID = PID(
        0, 
        0.1, 
        0.0, 
        1, 
        100
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
        float turnOutput = headingPID.compute(turnError);

        float drivePower = driveOutput > 500 ? 500 : driveOutput;
        float turnPower = turnOutput > 500 ? 500 : turnOutput;


        nova::leftDrive = drivePower + turnPower;
        nova::rightDrive = drivePower - turnPower;

        pros::delay(10);

        if (drivePower > MIN_STALL_POWER && this -> drive.getAvgVelocity() < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }

    drivePID.reset();
    headingPID.reset();

    PID turnPID = PID(
        0, 
        4.25, 
        0.0, 
        28.0, 
        100,
        5, 
        250, 
        3000
    );

    targetAngle = this -> drive.getIMURotation() + angle;

    while (!(turnPID.isSettled())) {
        float error = targetAngle - this -> drive.getIMURotation();
        float power = turnPID.compute(error);

        nova::leftDrive = power;
        nova::rightDrive = -power;

        pros::delay(10);
    }

    turnPID.reset();
    nova::drive.brake();
}

void nova::Auton::rotateTranslate(float angle, float dist) {
    PID turnPID = PID(
        0, 
        4.25, 
        0.0, 
        28.0, 
        100, 
        5, 
        250, 
        3000
    );

    float targetAngle = this -> drive.getIMURotation() + angle;

    while (!(turnPID.isSettled())) {
        float error = targetAngle - this -> drive.getIMURotation();
        float power = turnPID.compute(error);

        nova::leftDrive = power;
        nova::rightDrive = -power;

        pros::delay(10);
    }

    turnPID.reset();

    PID drivePID = PID(
        0, 
        1.5, 
        0.0, 
        8.5, 
        250, 
        50, 
        0, 
        5000
    );

    this -> drive.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 4, MIN_STALL_TIME = 400;

    while (!(drivePID.isSettled())) {
        float driveError = targetPosition - this -> drive.getAvgEncoderValue();

        float drivePower = drivePID.compute(driveError);

        nova::leftDrive = drivePower;
        nova::rightDrive = drivePower;

        pros::delay(10);

        if (drivePower > MIN_STALL_POWER && this -> drive.getAvgVelocity() < MIN_STALL_VELOCITY) {
            timeSpentStalled += 10;
        } else {
            timeSpentStalled = 0;
        }

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }

    drivePID.reset();
    nova::drive.brake();
}

void nova::Auton::translate(float dist) {
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

        float drivePower = driveOutput > 500 ? 500 : driveOutput;
        float turnPower = turnOutput > 500 ? 500 : turnOutput;


        nova::leftDrive = drivePower + turnPower;
        nova::rightDrive = drivePower - turnPower;

        pros::delay(10);

        if (drivePower > MIN_STALL_POWER && this -> drive.getAvgVelocity() < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }

    drivePID.reset();
    turnPID.reset();
    nova::drive.brake();
}

void nova::Auton::swingLeft(float angle) {
    PID swingPID = PID(
        0, 
        2.0, 
        0.0, 
        1.0, 
        100, 
        5, 
        250, 
        3000
    );
    
    float targetPosition = this -> drive.getIMURotation() + angle;
    while(!(swingPID.isSettled())){
        float error = targetPosition - this -> drive.getIMURotation();
        float drivePower = swingPID.compute(error);

        nova::leftDrive = drivePower;
        nova::rightDrive.brake();

        pros::delay(10);
    }
    nova::drive.brake();
    swingPID.reset();
}

void nova::Auton::swingRight(float angle) {
    PID swingPID = PID(
                0, 
                2.0, 
                0.0, 
                1.0, 
                100, 
                5, 
                250, 
                3000
            );

    float targetPosition = this -> drive.getIMURotation() + angle;
    while(!(swingPID.isSettled())){
        float error = targetPosition - this -> drive.getIMURotation();
        float drivePower = swingPID.compute(error);

        nova::rightDrive = -drivePower;
        nova::leftDrive.brake();

        pros::delay(10);
    }
    nova::drive.brake();
    swingPID.reset();
}

void nova::Auton::rotate(float angle) {
    PID turnPID = PID(
        0, 
        4.25, 
        0.0, 
        28.0, 
        100, 
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

    nova::drive.brake();
    turnPID.reset();
}

void nova::Auton::rotateAbsolute(float angle) {
    PID turnPID = PID(
        0, 
        4.25, 
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

    nova::drive.brake();
    turnPID.reset();
}

void nova::Auton::farSideAWP() {
    // Start paralele the corner pole
    // back against the glass
    // place tri-ball corner closest to robot
    lift.autonStart();
    intake.spinRevolutions(-4);

    translate(17);
    wings.open();
    pros::delay(250);
    translateRotate(-7, -45);

    // Move to side of goal and score
    wings.close();
    translateRotate(-7, 45);
    intake.spinRevolutions(3);
    translateRotate(20, 45);
    translate(12);
    
    // Move to bar 
    translateRotate(-14, -45);
    translateRotate(-28, -45);
    pros::delay(500);
    rotateAbsolute(-45);
    translate(-29);
}

void nova::Auton::farSide() {
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
    lift.liftUp();
}

void nova::Auton::closeSideAWP() {
    // start intake right above the tri-ball under the pole

    // Start Intake and Intake Tri-ball under Pole
    wings.close();
    lift.autonStart();
    translate(3);
    intake.spinRevolutions(-4);
    pros::delay(500);

    // Move To corner and get triball out
    translateRotate(-35.5, -45);
    wings.open();
    pros::delay(250);
    translateRotate(-15, -60);
    wings.close();
    rotateTranslate(60, -8);
    swingLeft(-45);
    translate(-5);
    translate(5);
    rotateAbsolute(-90);
    
    rotate(180);
    intake.spinRevolutions(3);
    translate(5);
    translate(-5);

    // Move to leftmost tri-ball
    rotate(-75);

    translate(52);
    intake.spinRevolutions(-3);
    pros::delay(250);

    rotate(135);
    intake.spinRevolutions(6);
    translate(18);
    pros::delay(250);
    translate(-5);

    rotateTranslate(-120, 24);
    intake.spinRevolutions(-2);
    pros::delay(250);
    rotateAbsolute(-180);
    intake.spinRevolutions(2);
    pros::delay(250);
    rotate(180);
    wings.open();
    translate(-20);
    translate(2);

    /*
    // Turn and score intake tri-ball
    
    // Move into position and score two tri-ball
    rotate(-46);
    wings.open();
    pros::delay(500);
    rotateAbsolute(0);
    translate(-31);
    translate(6);
    wings.close();

    // Score intake tri-ball
    rotate(180);
    translate(6);
    */
}

void nova::Auton::closeSide() {
    //start with back against glass
    //back left touching the glass connector
    
    lift.autonStart();
    pros::delay(1000);
    intake.spinRevolutions(-4);
    translateRotate(55, 90);
    translate(14);
    
    // Get the leftmost tri-ball
    translateRotate(-10, 160);
    intake.spinRevolutions(-3);
    pros::delay(250);
    translateRotate(25, 170);
    translate(15);
    intake.spinRevolutions(1);
    pros::delay(250);
    translateRotate(-5, -110);
    intake.spinRevolutions(-3);
    translateRotate(15, -55);
    wings.open();
    pros::delay(250);
    translate(-30);

    // Flip and score tri-ball in intake
    translate(5);
    wings.close();
    rotate(180);
    intake.spinRevolutions(3);
    pros::delay(250);
    translate(7);
    translate(-10);
}

void nova::Auton::skills() {
    // Score the two matchloads
    translateRotate(-24, 45);
    translate(-12);

    // Move into matchloading position
    translateRotate(8, -120);
    pros::delay(500);
    rotateAbsolute(-75);
    wings.openRight();
    translate(-4);

    // Matchloading
    flywheel.spinDuration(2);
    pros::delay(2000);
    nova::flywheel.brake();
    wings.closeRight();

    translate(3);
    rotate(30);
    pros::delay(500);
    rotateAbsolute(-45);
    translateRotate(28, 90);
    translateRotate(-70, 90);
    wings.open();
    pros::delay(250);
    translate(-20);
    wings.close();

    rotateAbsolute(135);

    translateRotate(24, -90);
    translateRotate(-24, 90);
    translateRotate(-75, 45);
    translateRotate(-20, 45);
    translate(-10);
    translate(10);
    translate(-10);
    translateRotate(10, 90);
    pros::delay(500);
    rotateAbsolute(-45);
    translateRotate(-24, -90);
    translateRotate(-40, -90);
    wings.open();
    pros::delay(250);
    translate(-20);
    translate(20);
    translate(-20);
    wings.close();
    translateRotate(20, 90);
    pros::delay(500);
    rotateAbsolute(-225);
    translateRotate(-20, -90);
    wings.open();
    pros::delay(250);
    translate(-20);
    
}