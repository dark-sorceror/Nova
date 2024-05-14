/**
 * \file hang.h
 *
 * Updated - 2/24/2024
 * Last Successful Test - 
 */ 

#ifndef __HANG
#define __HANG

namespace nova {
    class Hang {
        public:
            void open();
            void close();
            
            void run();
        private:
            void toggle();
            bool hangActive = false;
    };
}

#endif