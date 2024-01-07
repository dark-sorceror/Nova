/**
 * \file wings.h
 *
 * Updated - 12/25/2023
 * Last Successful Test - /
 */ 

#ifndef __WINGS
#define __WINGS

namespace nova {
    class Wings {
        public:
            int airRemaining = 100;

            void open();
            void close();
            void toggle();
            void run();
        private:
            bool wingsActive = false;
    };
}

#endif