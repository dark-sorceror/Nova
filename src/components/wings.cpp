/**
 * \file wings.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/13/2024
 */ 

#include "main.h"

int airRemaining = 100;

void nova::Wings::open() {
    nova::frontWings.set_value(HIGH);
    nova::backWings.set_value(HIGH);

    airRemaining -= 5;
}

void nova::Wings::openFrontWings() {
    nova::frontWings.set_value(HIGH);
}

void nova::Wings::openBackWings() {
    nova::backWings.set_value(HIGH);
}

void nova::Wings::close() {
    nova::frontWings.set_value(LOW);
    nova::backWings.set_value(LOW);

    airRemaining -= 5;
}

void nova::Wings::closeFrontWings() {
    nova::frontWings.set_value(LOW);
}

void nova::Wings::closeBackWings() {
    nova::backWings.set_value(LOW);
}

void nova::Wings::toggleFrontWings() {
    if (!this -> frontWingsActive) this -> openFrontWings(); else this -> closeFrontWings();
    this -> frontWingsActive = !this -> frontWingsActive;
}

void nova::Wings::toggleBackWings() {
    if (!this -> backWingsActive) this -> openBackWings(); else this -> closeBackWings();
    this -> backWingsActive = !this -> backWingsActive;
}

void nova::Wings::run() {
    master.print(0, 0, "Air Remaining: %i", airRemaining);
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) this -> openFrontWings();
    else this -> closeFrontWings();
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) this -> toggleBackWings();
}

