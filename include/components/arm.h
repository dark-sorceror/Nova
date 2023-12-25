/**
 * \file arm.h
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#ifndef __ARM
#define __ARM

namespace nova {
    class Arm {
        public:
            void initialize();
            void spinForward(int power);
            void toggle();
            void run();
        private:
            bool armActive = false;
    };
}

#endif
