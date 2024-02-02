/**
 * \file wings.h
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/10/2024
 */ 

#ifndef __WINGS
#define __WINGS

namespace nova {
    class Wings {
        public:
            void open();
            void openLeft();
            void openRight();

            void close();
            void closeLeft();
            void closeRight();

            void run();
        private:
            void toggle();
            
            bool wingsActive = false;
    };
}

#endif