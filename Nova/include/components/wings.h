/**
 * \file wings.h
 *
 * Updated - 12/24/2023
 * Last Successful Test - /
 */ 

#ifndef __WINGS
#define __WINGS

namespace nova {
    class Wings {
        public:
            void open();
            void close();
            void toggle();
            void run();
        private:
            bool wingsActive = false;
    };
}

#endif