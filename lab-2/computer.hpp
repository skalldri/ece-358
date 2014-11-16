#ifndef _COMPUTER_HPP
#define _COMPUTER_HPP

#include "simulatable.hpp"
#include "network_medium.hpp"
#include "packet.hpp"
#include "exponential_rand.hpp"
#include <queue>
#include <math.h>
#include <iostream>

enum Csma_mode
{
	CSMA_PERSISTENT,
	CSMA_NON_PERSISTENT,
	CSMA_P_PERSISTENT
};

enum Computer_state
{
    IDLE,
    MEDIUM_SENSE,
    TRANSMIT,
    EXP_BACKOFF
};

class Computer : public Simulatable {
	public:
    Computer(Network_medium* medium, Csma_mode csma, float csma_p, int id, unsigned int packet_size, unsigned int packets_per_second, unsigned int ticks_per_sec, unsigned int bits_per_second);
    ~Computer();
    
    void run_tick(unsigned long long int tick);
    void generate_packet(unsigned long long int tick);
    int get_id();
    int collision_handler();
    int timeout_handler(int);
    
    private:
        Computer_state state;
        Csma_mode csma;
        float csma_p;
	unsigned int bits_per_second;
        unsigned int collision_count;
        unsigned int timeout;
	unsigned int id;
	unsigned int packet_size;
	unsigned int to_transmit;
	unsigned int medium_sense_time;
	unsigned int backoff_count;
	unsigned long long int next_creation;
	unsigned int packets_per_second;
	Network_medium* medium;
	Exponential_rand expRand;
	std::queue<Packet> input;
	std::queue<Packet> output;
};

#endif
