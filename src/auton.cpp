#include "auton.h"
#include "main.h"
#include "pros/link.h"
#include "pros/rtos.hpp"
#include <cmath>

/*
float startPos = left_drive.getCurrentPosition();
    float prevError = goalPos - startPos;
    float integral = 0;
    
    float error = goalPos - getCurrentPosition();
    
    float pid = error * kP;
    motor

    // move motors with 'pid' amount
    prevError = error;

    wait(15, msec);
    // stop motors
*/

/*
1800 ticks/rev with 36:1 gears red
900 ticks/rev with 18:1 gears green
300 ticks/rev with 6:1 gears blue

144 inches x 144 inches field
omni wheel circumference =  2pi 3.25 inch = 20.42 inches / rev
*/

bool wingsActivated = false;
double prevIMUAngle = 0;

void toggleWings() {
    if (wingsActivated) {
        piston_1.set_value(0);
        piston_2.set_value(0);

        wingsActivated = false;
    } else {
        piston_1.set_value(100);
        piston_2.set_value(100);

        wingsActivated = true;
    }
}

double averageDriveEncoderValue() {
    return fabs(leftDrive[0].get_position()) + fabs(leftDrive[1].get_position()) + fabs(leftDrive[2].get_position()) + fabs(rightDrive[0].get_position()) + fabs(rightDrive[1].get_position()) + fabs(rightDrive[2].get_position());
}

void resetDriveEncoders() {
    leftDrive.tare_position();
    rightDrive.tare_position();
}

void setDrive(int left, int right) {
    leftDrive[0] = -left;
    leftDrive[1] = -left; 
    leftDrive[2] = -left;
    rightDrive[0] = right;
    rightDrive[1] = right;
    rightDrive[2] = right;
}

void translate(int units, int voltage) {
    int direction = abs(units) / units;

    resetDriveEncoders();

    while(averageDriveEncoderValue() < abs(units)) {
        setDrive(0.8 * voltage * direction, 0.8 * voltage * direction);
        pros::delay(10);
    }

    setDrive(-10 * direction, -10 * direction);
    pros::delay(50);

    setDrive(0, 0);
}

void rotate(int degrees, int voltage) {
    int direction = abs(degrees) / degrees;

    setDrive(0.5 *-voltage * direction, 0.5 * voltage * direction);
    while ((fabs(imu.get_rotation()) - fabs(prevIMUAngle)) < (abs(degrees)-50)) {
        pros::delay(10);
    }

    pros::delay(100);

    if (fabs(fabs(imu.get_rotation()) - fabs(prevIMUAngle)) < abs(degrees)) {
        setDrive(0.5 * voltage * direction, 0.5 * -voltage * direction);

        while (fabs(fabs(imu.get_rotation()) - fabs(prevIMUAngle)) > abs(degrees)) {
            pros::delay(10);
        }
    } else if (fabs(fabs(imu.get_rotation()) - fabs(prevIMUAngle)) > abs(degrees)) {
        setDrive(0.5 * -voltage * direction, 0.5 * voltage * direction);

        while ((fabs(imu.get_rotation()) - fabs(prevIMUAngle)) < abs(degrees)) {
            pros::delay(10);
        }
    }

    setDrive(0, 0);

    prevIMUAngle = imu.get_rotation();
}

void autonClose() {
    toggleWings();
    pros::delay(500);
    translate(2500, 127);
    pros::delay(1000);
    rotate(45, 127);
    pros::delay(1000);
    translate(4500, 127);
    pros::delay(1000);
    toggleWings();
    translate(-1500, 127);
    pros::delay(1000);
    arm.move_absolute(-400, 127);
    pros::delay(500);
    translate(3000, 127);
    pros::delay(1000);
    translate(-1500, 127);
    pros::delay(500);
    arm.move_absolute(400, 127);
    translate(4000, 127);
    pros::delay(1000);
    translate(-2000, 127);
}

void autonFar() {
    translate(14500, 127); // offset by like 1000 comment this if get cornoer
    pros::delay(1000);
    rotate(80, 127); // comment from here if coernr to down there
    pros::delay(500);
    arm.move_absolute(-400, 127);
    translate(6750, 127);
    pros::delay(500);
    translate(-2000, 127);
    pros::delay(500);
    arm.move_absolute(400, 127);
}
 
void autonSkills() {
    translate(4500, 127);
    pros::delay(1000);
    rotate(-55, 127);
    pros::delay(1000);
    translate(-4500, 127);
    arm.move_absolute(-450, 127);
    flywheel.move_absolute(-1000000, 500);
    pros::delay(40000);
    toggleWings();
    translate(20000, 127);
    pros::delay(1000);
    translate(-3000, 127);


}

