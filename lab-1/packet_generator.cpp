#include "packet_generator.hpp"

using namespace std;

Packet_generator::Packet_generator(unsigned int pk_per_sec, 
								   unsigned int pk_size, 
								   unsigned int ticks_per_sec, 
								   Packet_server* target) : 
	Simulatable(ticks_per_sec),
	packet_size(pk_size),
	packets_per_second(pk_per_sec),
	server(target),
	next_tick(0),
    exp_rand(pk_per_sec, ticks_per_second)
{
    
}

/*
 * -Check if we are past our time limit for next tick
 * -Generate packet if neccessary
 * -Sleep until next time
 */
void Packet_generator::run_tick(unsigned long long int tick)
{    
    if(tick >= next_tick)
    {
        cout << "PACKET_GENERATOR: Adding new packet" << endl;
        
        //Generate a new packet
        Packet newPacket(packet_size, tick);
        server->add_packet(newPacket);
        //Setup next tick
        next_tick = tick + exp_rand.get_random_ticks();
    }
}
