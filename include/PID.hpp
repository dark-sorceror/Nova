/**
 * \file PID.hpp
 *
 * Updated - 1/10/2024
 * Last Successful Test - 1/10/2024
 */ 

#ifndef __PID
#define __PID

namespace nova {
    class PID {
        public:
            PID (
                float error,
                float kP,
                float kI,
                float kD,
                float maxCumulativeError,
                float loopTime = 10
            );

            PID (
                float error, 
                float kP, 
                float kI, 
                float kD, 
                float maxCumulativeError,
                float settleError,
                float settleTime,
                float timeout,
                float loopTime = 10
            );
            float kP = 0;
            float kI = 0;
            float kD = 0;

            float dT = 0.2;

            float prevDeriv = 0;
            float acceleration = 0;

            float accumulatedError = 0;
            float maxCumulativeError = 0;
            float futureError = 0;
            float error = 0;
            float prevError = 0;

            float settleTime = 0;
            float settleError = 0;
            float timeSpentSettled = 0;
            float timeSpentRunning = 0;
            float timeout = 0;
            float loopTime = 10;

            float output = 0;

            float compute(float error);
            bool isSettled();
            void reset();

            void setkConstants(
                float kP,
                float kI,
                float kD,
                float maxCumulativeError
            );
            
            void setExitConditionConstants(
                float settleError,
                float settleTime,
                float timeout
            );
    };
}

#endif