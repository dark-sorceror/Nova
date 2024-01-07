/**
 * \file auton.h
 *
 * Updated - 12/25/2023
 * Last Successful Test - /
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
            

        /*
        private:
            const float WHEEL_DIAMETER = 3.25; // inches
            const float LEFT_SIDE_RADIUS = 4.724;
            const float RIGHT_SIDE_RADIUS = 4.724;
            const float BACK_SIDE_RADIUS = 4;
            const float TICKS_PER_ROTATION = 300;
            const float WHEEL_CIRCUMFERENCE = (WHEEL_DIAMETER * 3.14159265) / TICKS_PER_ROTATION;

            typedef struct _pos {
                float angle;
                float y;
                float x;
                int leftLst;
                int rightLst;
                int backLst;
            } sPos;

            typedef struct _vector {
                float y;
                float x;
            } sVector;

            typedef struct _polar {
                float magnitude;
                float angle;
            } sPolar;

            typedef struct _line {
                sVector p1;
                sVector p2;
            } sLine;

            sPos botPosition;
            sVector target;

            float getAvgLeftEncoderValue(); //replace with real encoder
            float getAvgRightEncoderValue();
            float getTrackingEncoderValue();

            void trackPosition(int left, int right, int back, sPos& position);
            void resetPosition(sPos& position);

            void moveTo(float x, float y, float xs, float ys);
            
            pros::Task updateTrackPosition();
        */

            Drive drive;
            Intake intake;
            Lift lift;
            Flywheel flywheel;
            Wings wings;

            Auton(Drive drive, Intake intake, Lift lift, Flywheel flywheel, Wings wings);

            //void trackPosition(int left, int right);
            void translate(float dist);
            void rotate(float angle);
            void drift(float angle);

            void closeSide();
            void farSide();
            void skills();
    };
}

#endif



