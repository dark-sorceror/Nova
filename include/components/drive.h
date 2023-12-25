/**
 * \file drive.h
 *
 * Updated - 12/24/2023
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
            double getAvgEncoderValue();
            double getIMURotation();
            void run();
        private:
            const int DEADBAND = 10;
    };
}

#endif