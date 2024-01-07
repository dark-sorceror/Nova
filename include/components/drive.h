/**
 * \file drive.h
 *
 * Updated - 12/25/2023
 * Last Successful Test - /
 */ 

#ifndef __DRIVE
#define __DRIVE

namespace nova {
    class Drive {
        public:
            void initialize();
            void resetMotorEncoders();
            void resetIMU();
            float getAvgEncoderValue();
            float getAvgVelocity();
            double getIMURotation();
            void run();
        private:
            const int DEADBAND = 10;
    };
}

#endif