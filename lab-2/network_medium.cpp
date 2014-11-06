#include "network_medium.hpp"

Network_medium::Network_medium(unsigned int ticks_per_second) : 
    Simulatable(ticks_per_second)
{
    
}

void Network_medium::run_tick(unsigned long long int tick)
{
    //I don't think anything needs to happen here. All the notification logic will occur in transmit_packet
}

// Other people call this when they want to send a packet over the medium. 
void transmit_packet(Computer* sender, Packet p)
{
    //If more than one person tries to transmit, notify everyone who's transmitted during this tick
    //Note: conditions for when a collision occurs might be more complex than just "two people in same tick". Need to review CSMA/CD signal propagation issues to be sure.
}
