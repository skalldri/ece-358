#include "network_medium.hpp"
#include "computer.hpp"

using namespace std;

Network_medium::Network_medium(unsigned int ticks_per_second, unsigned int num_comp, float prop_speed) : 
    Simulatable(ticks_per_second),
    num_computers(num_comp),
    propagation_speed(prop_speed)
{
    
}

void Network_medium::run_tick(unsigned long long int tick)
{
    //Transmit to any computers that need to be notified
    current_tick = tick;
    
    float cable_length = num_computers * 10.0;
    
    //cout << "Beginning network_medium processing time" << endl;

    	for( vector<Collision_event>::iterator it = collisions.begin();
	     it != collisions.end(); )
	{
        	// If the "signal off" wave has propagated the entire length of the cable...
		if(it->off_propagation_length > cable_length)
        	{
            		// Delete the collision event as we won't ever use this again
            		it = collisions.erase(it);
            		continue;
        	}

		if(it->state == ANTICIPATED)
		{
		    it->state = TERMINATED;
		} 
		else if(it->state == TRANSMITTED)
		{
		    it->state = ANTICIPATED;
		}
		
		if(it->state == TERMINATED)
		{
		    it->off_propagation_length += propagation_speed * (1.0 / (float)ticks_per_second);
		}
		
		it->on_propagation_length += propagation_speed * (1.0 / (float)ticks_per_second);
		
		++it;
	}
}

// Call this function every tick while you are transmitting a packet
void Network_medium::transmit(Computer* sender)
{
    //Search for this computer in the list of Collision_events
    for( vector<Collision_event>::iterator it = collisions.begin();
	     it != collisions.end(); 
	     ++it )
	{
                // If this computer is in the progress of transmitting a packet...
		if(it->source == sender && it->state == ANTICIPATED)
        	{
            		// Update the state to show we're still transmitting (this prevents the "signal off" wave from propagating)
            		it->state = TRANSMITTED;
            		return;
        	} 
	}
    
    // If we got to here, either this computer hasn't transmitted before or it had, but the signal had gone stale for at least one tick.
    // We will create a new event to track this transmission
    //cout << "New transmission detected over network medium!" << endl;
    Collision_event newEvent;
    newEvent.state = TRANSMITTED;
    newEvent.source = sender;
    newEvent.on_propagation_length = 0.0;
    newEvent.off_propagation_length = 0.0;
    
    collisions.push_back(newEvent);
}

// Returns true is the network medium AT THE LOCATION OF THE CURRENT COMPUTER is busy
// Will not return true if YOU are the one transmitting: only other people
bool Network_medium::is_busy(Computer* sender)
{
    // Search to find out if any current transmissions (or ended transmissions) can be detected at the target computer
    for( vector<Collision_event>::iterator it = collisions.begin();
	 it != collisions.end(); 
	 ++it )
	{
        	// Get the distance between this "transmitting computer" and the computer that is checking the line for busy
        	float distance = abs(sender->get_id() - it->source->get_id()) * 10.0;
        
		if(it->on_propagation_length >= distance && it->off_propagation_length < distance)
        	{
            		return true;
        	} 
	}
    
    return false;
}
