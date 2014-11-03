#include "network_medium.hpp"

Network_medium::Network_medium(unsigned int ticks_per_second) : 
    Simulatable(ticks_per_second)
{
    
}

void Network_medium::run_tick(unsigned long long int tick)
{

}

// Other people call this when they want to send a packet over the medium. 
void transmit_packet(Computer* sender, Packet p)
{
    
}
