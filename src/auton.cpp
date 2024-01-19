/**
 * \file auton.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/10/2024
 */ 

#include "PID.hpp"
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

float nova::Auton::getAuton() {
    return nova::potentiometer.get_value();
}

void nova::Auton::translate(float dist) {
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

    nova::drive.brake();
    drivePID.reset();
}

void nova::Auton::swing(float angle) {
    PID swingPID = PID(
                0, 
                2.0, 
                0.0, 
                1.0, 
                100, 
                5, 
                75, 
                3000
            );
    while(!(swingPID.isSettled())){
        float error = angle - this -> drive.getIMURotation();
        float drivePower = swingPID.compute(error);

        if (angle > 0) {
            nova::leftDrive = drivePower;
            nova::rightDrive.brake();
        } else {
            nova::rightDrive = drivePower;
            nova::leftDrive.brake();
        }

        pros::delay(10);
    }
    nova::drive.brake();
    swingPID.reset();
}

void nova::Auton::rotate(float angle) {
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

void nova::Auton::farSideAWP() {
    // Get tri-ball from corner out
    translate(17);
    wings.open();
    pros::delay(250);
    translate(-7);
    rotate(-45);

    // Move to side of goal and score
    wings.close();
    translate(-5);
    rotate(45);
    translate(20);
    rotate(45);
    translate(12);
    
    // Move to bar 
    translate(-10);
    wings.open();
    rotate(-45);
    translate(-28);
    rotate(-45);
    translate(-33);
}

void nova::Auton::farSide() { // TODO
    translate(10);
    rotate(90);
    lift.liftUp();
    pros::delay(2000);
    flywheel.spinDuration(1);
}

void nova::Auton::closeSideAWP() {
    // Move to goal and score matchloaded tri-ball
    intake.spinRevolutions(-2);
    this -> translate(5);
    this -> translate(-45);
    this -> rotate(-45);
    this -> translate(-12);
    wings.openLeft();
    this -> rotate(-45);
    this -> translate(-16);
    this -> translate(6);
    this -> rotate(180);
    this -> translate(6);
    this -> translate(-6);
    

    /* old
    translate(50);
    rotate(90);
    translate(14);
    

    // Get the leftmost tri-ball
    translate(-10);
    rotate(160);
    intake.spinRevolutions(-3);
    translate(25);

    // Release the tri-ball
    rotate(170);
    translate(15);
    intake.spinRevolutions(1);
    pros::delay(250);
    translate(-5);
    
    // Get the middle tri-ball
    rotate(-110);
    intake.spinRevolutions(-3);
    translate(15);
    
    // Position into scoring and score bottom tri-ball and leftmost tri-ball
    rotate(-55);
    wings.open();
    pros::delay(250);
    translate(-30);

    // Flip and score tri-ball in intake
    translate(5);
    wings.close();
    rotate(180);
    intake.spinRevolutions(3);
    translate(7);

    // Move to pole
    wings.open();
    translate(-10);
    rotate(-45);
    translate(-34);
    rotate(35);
    translate(-10);
    */
}

void nova::Auton::closeSide() { // TODO
    this -> translate(17);
    wings.open();
    pros::delay(250);
    translate(-7);
    rotate(-45);
    pros::delay(250);
    rotate(-45);
    translate(-50);
    rotate(45);
    translate(-10);
    wings.close();
    translate(40);
    translate(-5);
    rotate(90);
    translate(-48);
    rotate(-90);
    translate(-40);
}

void nova::Auton::skills() {
    // Score the two matchloads
    this -> translate(-24);
    this -> rotate(45);
    this -> translate(-15);

    // Move into matchloading position
    this -> translate(14);
    this -> rotate(-105);
    this -> translate(-3);

    // Matchloading
    lift.liftUp();
    pros::delay(2000);
    lift.liftDown();

    // Move to the other side
    this -> translate(3);
    this -> rotate(-121);
    this -> translate(-26);
    this -> rotate(-45);
    this -> translate(-90);
    
    // Score on the left side of goal
    this -> rotate(-45);
    this -> translate(-24);
    this -> rotate(-45);
    this -> translate(-10);

    // Move to score position 1/3
    this -> translate(7);
    this -> rotate(-90);
    this -> translate(-50);
    this -> rotate(90);
    this -> translate(-12);
    wings.open();
    this -> rotate(60);
}