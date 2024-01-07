/**
 * \file wings.cpp
 *
 * Updated - 12/25/2023
 * Last Successful Test - /
 */ 

#include "main.h"

void nova::Wings::open() {
    nova::leftWing.set_value(HIGH);
    nova::rightWing.set_value(HIGH);

    // TODO: Amount of Air used
}

void nova::Wings::close() {
    nova::leftWing.set_value(LOW);
    nova::rightWing.set_value(LOW);

    // TODO: Amount of Air used
}

void nova::Wings::toggle() {
    if (!this -> wingsActive) this -> open(); else this -> close();
    this -> wingsActive = !this -> wingsActive;
}

void nova::Wings::run() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) this -> toggle();
    // TODO: Amount of Air Left
}

