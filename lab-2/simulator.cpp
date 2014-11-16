#include "simulator.hpp"

using namespace std;

Simulator::Simulator(unsigned long long int simulation_time) : 
current_tick(0),
max_tick(simulation_time)
{

}

void Simulator::run()
{
    int print_delay = 0;
    while(current_tick < max_tick)
    {
        tick();
        print_delay++;
        
        if(print_delay > 1000000)
        {
            print_delay = 0;
            cout << "Percent complete: " <<  (((float)current_tick / (float)max_tick) * 100.0) << "%               " << "\r";
            cout.flush();
        }
	
	//usleep(10);
    }
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
