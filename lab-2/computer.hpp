#ifndef _COMPUTER_HPP
#define _COMPUTER_HPP

#include "simulatable.hpp"
#include "network_medium.hpp"

class Computer : public Simulatable {
    Computer(Network_medium* medium, int id, unsigned int ticks_per_sec);
    
    void run_tick(unsigned long long int tick);
    
    private:
	int id;
	Network_medium* medium;
};

#endif
