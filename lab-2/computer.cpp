#include "computer.hpp"

Computer::Computer(unsigned int ticks_per_sec) :
    Simulatable(ticks_per_sec)
{
    
}
    
void Computer::run_tick(unsigned long long int tick)
{
    // Check and see if we want to transmit during this tick (do we have a new packet to transmit OR are we currently transmitting a packet?)
    // Also, if we need to transmit a new packet and we're currently transmitting, queue the packet
    
    // If no, return
    
    // If yes, try and transmit a packet over the medium
    
    // Cannot immediately know if a collision occurred: what if this is the first transmission during this tick, but there are others?
    // Solution: the Network_medium will callback anyone who needs to know about collisions
}

// Called by the network medium whenever a collision occurs
void Computer::collision_callback()
{
    // Abort transmitting current packet and requeue according to CSMA/CD
}
