/**
 * \file lift.h
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/13/2024
 */ 

#ifndef __LIFT
#define __LIFT

namespace nova {
    class Lift {
        public:
            void initialize();
            void liftUp();
            void liftDown();
            void autonStart();
            void run();
        private:
            bool liftActive = false;
    };
}

#endif
