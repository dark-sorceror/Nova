/**
 * \file flywheel.h
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#ifndef __INTAKE
#define __INTAKE

namespace nova {
    class Intake {
        public:
            void initialize();
            void spinForward(int power);
            void spinDistance(int revolutions);
            void toggle();
            void run();
        private:
            bool intakeActive = false;
    };
}

#endif

