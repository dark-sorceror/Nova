/**
 * \file flywheel.h
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#ifndef __FLYWHEEL
#define __FLYWHEEL

namespace nova {
    class Flywheel {
        public:
            void initialize();
            void spinForward(int power);
            void toggle();
            void run();
        private:
            bool flywheelActive = false;
    };
}

#endif

