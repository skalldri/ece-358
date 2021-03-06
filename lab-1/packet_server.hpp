#ifndef _PACKET_SERVER_HPP
#define _PACKET_SERVER_HPP

#include <iostream>
#include <deque>
#include "simulatable.hpp"
#include "packet.hpp"
#include "debug_log.hpp"

/*
 * This class is one of the two possible simulatable objects. The first time this object is ticked, it will
 * generate a new packet. It will also generate a new "tick time", essentially a time to wait until emitting the next packet.
 * The packet generator will wait until the prescribed time (passed in to run_tick()) and then emit another packet,
 * and generate a new time. Rinse and repeat.
 * 
 */

class Packet_server : public Simulatable {
	
public:
	/* 
	 * The constructor for the Packet_server object.
	 * 
	 * packets_per_second: The average number of packets-per-second this generator should create
	 * packet_size: The number of bits in each packet (not real, but for simulation tracking purposes)
	 * ticks_per_sec: Ticks per second
	 */
	Packet_server(unsigned int ticks_per_sec,
                  int max_queue,
                  unsigned int ticks_per_packet);
	
	void run_tick(unsigned long long int tick);
    void add_packet(Packet pack);

    unsigned long long int total_packets;
    unsigned long long int packets_dropped;
    unsigned long long int idle_ticks;
    unsigned long long int total_queue_size; // total queue size, measured each tick. (total_queue_size / ticks) = average queue length
    std::deque<Packet> finished_packets;

private:
	std::deque<Packet> queue;
    unsigned int max_queue_size;
    unsigned int service_ticks;
    unsigned long long int next_tick;
    unsigned long long int current_tick;
    
};

#endif //_PACKET_SERVER_HPP
