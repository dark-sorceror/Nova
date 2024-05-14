/**
 * \file kicker.cpp
 *
 * Updated - 2/24/2024
 * Last Successful Test - 
 */ 
 
#include "main.h"

void nova::Kicker::initialize() {
    nova::kicker.set_brake_modes(E_MOTOR_BRAKE_HOLD);
    nova::kicker.tare_position();
    nova::kickerSetter.reset();
}

void nova::Kicker::chargeSync() {
    int sensorProximity = nova::triballChecker.get();
    const int sensorThreshold = 50;

    CHARGED_POSITION_ANGLE = 80;

    float error = CHARGED_POSITION_ANGLE - nova::kickerSetter.get_angle();
    float power = kickerPID.compute(error);

    if(sensorProximity <= sensorThreshold) {
        nova::kicker = 127; // Fire Catapult
    } else {
        if(nova::kickerSetter.get_angle() > CHARGED_POSITION_ANGLE || nova::kickerSetter.get_angle() < 0){
            nova::kicker.brake();
        } else {
            nova::kicker = power;
        }
    }
}

void nova::Kicker::skillsMatchload() {
    while (!timesUp)  {
        nova::kicker = 127;
    }
}

void nova::Kicker::run() {
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        nova::kicker = 127;
    } else {
        nova::kicker.brake();
    }

}