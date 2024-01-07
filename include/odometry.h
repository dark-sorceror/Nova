/**
 * \file odometry.h
 *
 * Updated - 1/1/2024
 * Last Successful Test - /
 */ 

#include "api.h"

#ifndef __ODOMETRY
#define __ODOMETRY

namespace nova {
    class Odometry {
        public:
            typedef struct _pos {
                float angle;
                float y;
                float x;
                int leftLst;
                int rightLst;
                int backLst;
            } sPos;

            sPos botPosition;

            float getAvgLeftEncoderValue();
            float getAvgRightEncoderValue();
            float getTrackingEncoderValue();

            void trackPosition(int left, int right, int back, sPos& position);
            void resetPosition(sPos& position);
            pros::Task updateTrackPosition();
        private:
            const float WHEEL_DIAMETER = 3.25; // inches
            const float LEFT_SIDE_RADIUS = 4.724;
            const float RIGHT_SIDE_RADIUS = 4.724;
            const float BACK_SIDE_RADIUS = 4;
            const float TICKS_PER_ROTATION = 300;
            const float LEFT_SIDE_CIRCUMFERENCE = (WHEEL_DIAMETER * 3.14159265) / TICKS_PER_ROTATION;
    };
}

#endif
