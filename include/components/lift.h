/**
 * \file arm.h
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#ifndef __LIFT
#define __LIFT

namespace nova {
    class Lift {
        public:
            void initialize();
            void spinForward(int power);
            void liftUp();
            void liftDown();
            void toggle();
            void run();
        private:
            bool liftActive = false;
    };
}

#endif
