/**
 * \file auton.h
 *
 * Updated - 1/10/2024
 * Last Successful Test - 1/10/2024
 */ 

#ifndef __AUTON
#define __AUTON

#include "components/drive.h"
#include "components/intake.h"
#include "components/flywheel.h"
#include "components/wings.h"
#include "PID.hpp"
#include <iostream>
#include <map>
#include <list>

namespace nova {
    class Auton {
        public: 
            Auton(Drive drive, Intake intake, Flywheel flywheel, Wings wings);

            float getAuton();

            void farSideAWP();
            void farSide();
            void farSideElims();
            void closeSideAWP();
            void closeSide();
            void skills();
        private:
            Drive drive;
            Intake intake;
            Flywheel flywheel;
            Wings wings;

            //void trackPosition(int left, int right);
            void translate(float dist);
            void setPath(std::list < std::pair < std::string, float > > path);
            void rotate(float angle);
            void rotateAbsolute(float angle);
            void swerveLeft(float dist, float angle);
            void swerveRight(float dist, float angle);
    };
}

#endif



