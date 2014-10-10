#ifndef _PACKET_GENERATOR_HPP
#define _PACKET_GENERATOR_HPP

#include <iostream>
#include <deque>
#include "simulatable.hpp"
#include "packet.hpp"
#include "packet_server.hpp"
#include "exponential_rand.hpp"
#include "debug_log.hpp"

/*
 * This class is one of the two possible simulatable objects. The first time this object is ticked, it will
 * generate a new packet. It will also generate a new "tick time", essentially a time to wait until emitting the next packet.
 * The packet generator will wait until the prescribed time (passed in to run_tick()) and then emit another packet,
 * and generate a new time. Rinse and repeat.
 * 
 */

class Packet_generator : public Simulatable {
	
public:
	/* 
	 * The constructor for the Packet_generator object.
	 * 
	 * packets_per_second: The average number of packets-per-second this generator should create
	 * packet_size: The number of bits in each packet (not real, but for simulation tracking purposes)
	 * tick_resolution_ns: The number of nanoseconds each tick represents
	 */
	Packet_generator(unsigned int packets_per_second, 
					 unsigned int packet_size, 
					 unsigned int ticks_per_second,
					 Packet_server* server);
	
	void run_tick(unsigned long long int tick);

private:
	unsigned int packet_size;
	unsigned int packets_per_second;
	Packet_server* server;
	unsigned long long int next_tick;
    Exponential_rand exp_rand;
};

#endif //_PACKET_GENERATOR_HPP
