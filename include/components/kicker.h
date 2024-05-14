#ifndef __KICKER
#define __KICKER

#include "PID.hpp"

namespace nova {
    class Kicker { // Class Template for 6m Drive
        public:

            bool matchLoadRoutineIsActive = false;
            float CHARGED_POSITION_ANGLE = 80; 
            bool ready = false;
            void skillsMatchload();
            bool timesUp = false;
            PID kickerPID = PID(0, 0.1, 0.2, 0, 0, 10 * 100, 500, 4000);

            void initialize();
            void run();

            void chargeSync();
    };
}

#endif 