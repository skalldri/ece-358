#include "network_medium.hpp"

using namespace std;

Network_medium::Network_medium(unsigned int ticks_per_second, unsigned int num_comp) : 
    Simulatable(ticks_per_second),
    num_computers(num_comp)
{
    
}

void Network_medium::run_tick(unsigned long long int tick)
{
    //Transmit to any computers that need to be notified
    current_tick = tick;
    
    for( vector<Collision_event>::iterator it = collisions.begin();
	     it != collisions.end(); 
	     //Empty )
	{
		if((*it).off_propagation_length <= num_computers)
        {
            collisions.erase(it);
        }
        else
        {
            ++it;
        }
	}
}

// Call this function every tick while you are transmitting a packet
void Network_medium::transmit(Computer* sender)
{
    //Add this computer to the list of transmitting computers (this is on a per-tick basis)   
    transmitters.push_back(sender);
    
}

// Returns true is the network medium AT THE LOCATION OF THE CURRENT COMPUTER is busy
// Will not return true if YOU are the one transmitting: only other people
bool Network_medium::is_busy(Computer* sender)
{
    
}
