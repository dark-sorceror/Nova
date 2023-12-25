#pragma once

#include <string>

namespace selector {
    extern int auton;
    extern const char * btnmMap[];
    void init(const char **autons = btnmMap);
}