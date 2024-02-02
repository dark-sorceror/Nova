/**
 * \file wings.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/13/2024
 */ 

#include "main.h"

int airRemaining = 100;

void nova::Wings::open() {
    nova::leftWing.set_value(HIGH);
    nova::rightWing.set_value(HIGH);

    airRemaining -= 5;
}

void nova::Wings::openLeft() {
    nova::leftWing.set_value(HIGH);
}

void nova::Wings::openRight() {
    nova::rightWing.set_value(HIGH);
}

void nova::Wings::close() {
    nova::leftWing.set_value(LOW);
    nova::rightWing.set_value(LOW);

    airRemaining -= 5;
}

void nova::Wings::closeLeft() {
    nova::leftWing.set_value(LOW);
}

void nova::Wings::closeRight() {
    nova::rightWing.set_value(LOW);
}

void nova::Wings::toggle() {
    if (!this -> wingsActive) this -> open(); else this -> close();
    this -> wingsActive = !this -> wingsActive;
}

void nova::Wings::run() {
    master.print(0, 0, "Air Remaining: %i", airRemaining);
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) this -> toggle();
}

