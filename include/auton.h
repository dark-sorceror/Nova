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
            
            PID drivePID = PID(
                0, 
                1.5, 
                0.0, 
                8.5, 
                250, 
                50, 
                175, 
                5000
            );

            PID turnPID = PID(
                0, 
                4.0, 
                0.0, 
                28.0, 
                100, 
                5, 
                75, 
                3000
            );

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
            void rotate(float angle);
            void swing(float angle);
    };
}

#endif



