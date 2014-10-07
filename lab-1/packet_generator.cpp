#include "packet_generator.hpp"

using namespace std;

Packet_generator::Packet_generator(unsigned int pk_per_sec, 
								   unsigned int pk_size, 
								   unsigned int tick_resolution_ns, 
								   deque<Packet>* target_queue) : 
	Simulatable(tick_resolution_ns),
	packet_size(pk_size),
	packets_per_second(pk_per_sec),
	queue(target_queue),
	next_tick(0)
{

}

/*
 * -Check if we are past our time limit for next tick
 * -Generate packet if neccessary
 * -Sleep until next time
 */
void Packet_generator::run_tick(unsigned long long int tick)
{
	
}
