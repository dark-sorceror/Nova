/**
 * \file intake.h
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/13/2024
 */ 

#ifndef __INTAKE
#define __INTAKE

namespace nova {
    class Intake {
        public:
            void initialize();
            void spinRevolutions(int revolutions);
            void run();
        private:
            bool intakeActive = false;
    };
}

#endif

