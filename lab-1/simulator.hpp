#include <vector>
#include <iostream>
#include "simulatable.hpp"

class Simulator {

public:
	Simulator();
	~Simulator();
	
	void tick();
	
	void add_simulatable(Simulatable* sim);
	
private:
	unsigned long long int current_tick;
	std::vector<Simulatable*> simulatables;
};
