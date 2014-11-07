#ifndef _COMPUTER_HPP
#define _COMPUTER_HPP

#include "simulatable.hpp"

class Computer : public Simulatable {
    Computer(unsigned int ticks_per_sec);
    
    void run_tick(unsigned long long int tick);
    
    void collision_callback();
};

#endif
