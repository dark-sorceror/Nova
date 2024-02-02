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
#include "components/lift.h"
#include "components/flywheel.h"
#include "components/wings.h"
#include "PID.hpp"

namespace nova {
    class Auton {
        public: 
            Auton(Drive drive, Intake intake, Lift lift, Flywheel flywheel, Wings wings);

            float getAuton();

            void farSideAWP();
            void farSide();
            void closeSideAWP();
            void closeSide();
            void skills();
        private:
            Drive drive;
            Intake intake;
            Lift lift;
            Flywheel flywheel;
            Wings wings;

            //void trackPosition(int left, int right);
            void translate(float dist);
            void translateRotate(float dist, float angle);
            void rotateTranslate(float angle, float dist);
            void rotate(float angle);
            void rotateAbsolute(float angle);
            void swingLeft(float angle);
            void swingRight(float angle);
    };
}

#endif



