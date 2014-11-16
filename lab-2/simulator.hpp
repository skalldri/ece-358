#ifndef _SIMULATOR_HPP
#define _SIMULATOR_HPP

#include <vector>
#include <iostream>
#include "simulatable.hpp"
#include <unistd.h>

class Simulator {

public:
	Simulator(unsigned long long int sim_time);
	
	void tick();
	void run();
	void add_simulatable(Simulatable* sim);
	
private:
	unsigned long long int current_tick;
        unsigned long long int max_tick;
	std::vector<Simulatable*> simulatables;
};

#endif //_SIMULATOR_HPP
