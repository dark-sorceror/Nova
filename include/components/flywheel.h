/**
 * \file flywheel.h
 *
 * Updated - 1/6/2024
 * Last Successful Test - 1/6/2024
 */ 

#ifndef __FLYWHEEL
#define __FLYWHEEL

namespace nova {
    class Flywheel {
        public:
            void initialize();
            void spinDuration(int duration);
            void run();
        private:
            bool flywheelActive = false;
    };
}

#endif