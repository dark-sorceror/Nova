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
            void openFrontWings();
            void openBackWings();

            void close();
            void closeFrontWings();
            void closeBackWings();

            void run();
        private:
            void toggleFrontWings();
            void toggleBackWings();
            
            bool frontWingsActive = false;
            bool backWingsActive = false;
    };
}

#endif