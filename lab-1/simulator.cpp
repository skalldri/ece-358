#include "simulator.hpp"

using namespace std;

Simulator::Simulator()
{

}

void Simulator::tick()
{
	for( vector<Simulatable*>::iterator it = simulatables.begin();
	     it != simulatables.end(); 
	     ++it )
	{
		(*it)->run_tick(current_tick);
	}
	
	current_tick++;
}

void Simulator::add_simulatable(Simulatable* sim)
{
	simulatables.push_back(sim);
}
