/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_MISC__
#define __CAMOMILE_PD_MISC__

#include <string>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <mutex>
#include <tuple>
#include <iostream>
#include <memory>

namespace pd
{
    // ==================================================================================== //
    //                                      LEAK DETECTOR                                   //
    // ==================================================================================== //
    
    template <class T> class LeakDetector
    {
    public:
        inline LeakDetector() noexcept {++(getCounter().nobjects); }
        
        inline ~LeakDetector() {
            if(--(getCounter().nobjects) < 0)
                 std::cout << "Leak Detected";
        }
        
    private:
        
        class LeakCounter
        {
        public:
            inline LeakCounter() noexcept : nobjects(0) {}
            inline ~LeakCounter() noexcept {
                if(nobjects > 0)
                    std::cout << "Leak Detected";
            }
            
            std::atomic_int nobjects;
        };
        
        static LeakCounter& getCounter() noexcept
        {
            static LeakCounter counter;
            return counter;
        }
    };
}

#endif
