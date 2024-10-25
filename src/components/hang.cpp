/**
 * \file hang.cpp
 *
 * Updated - 2/24/2024
 * Last Successful Test - 3/13/2024
 */ 
 
#include "main.h"

void nova::Hang::open() { 
    nova::hang1.set_value(HIGH);
    nova::hang2.set_value(HIGH);
}

void nova::Hang::close() { 
    nova::hang1.set_value(LOW); 
    nova::hang2.set_value(LOW);
}

void nova::Hang::toggle() {
    if (!this -> hangActive) this -> open(); else this -> close();
    this -> hangActive = !this -> hangActive;
}

void nova::Hang::run() { 
    if (nova::master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) this->open();
    else this->close();
}
