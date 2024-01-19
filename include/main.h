/**
 * \file main.h
 *
 * Copyright (c) 2017-2022, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Updated - 1/10/2024
 * Last Successful Test - 1/10/2024
 */

#ifndef _PROS_MAIN_H_

#define _PROS_MAIN_H_
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"

#include "globals.h"
#include "components/drive.h"
#include "components/intake.h"
#include "components/lift.h"
#include "components/wings.h"
#include "components/flywheel.h"
#include "PID.hpp"
#include "auton.h"

using namespace pros;

#ifdef __cplusplus

extern "C" {
    #endif
    void autonomous(void);
    void initialize(void);
    void disabled(void);
    void competition_initialize(void);
    void opcontrol(void);
    #ifdef __cplusplus
}

#endif

#ifdef __cplusplus

#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
#include <string>

#endif

#endif // _PROS_MAIN_H_
