#ifndef _COMPUTER_HPP
#define _COMPUTER_HPP

#include "simulatable.hpp"
#include "network_medium.hpp"
#include "packet.hpp"
#include "exponential_rand.hpp"

#define CSMA_PERSISTENT 	0
#define CSMA_NON_PERSISTENT 1
#define CSMA_P_PERSISTENT 	2

using namespace std;

class Computer : public Simulatable {
	public:
    Computer(Network_medium* medium, int id, unsigned int ticks_per_sec);
    ~Computer();
    
    void run_tick(unsigned long long int tick);
    void generate_packet();
    int get_id();
    int collision_handler();
    int timeout_handler(int);
    
    private:
    unsigned int csma;
    float csma_p;
    unsigned int collision_count;
    unsigned int timeout;
	int id;
	int packet_size;
	int to_transmit;
	int next_creation;
	Network_medium* medium;
	Exponential_rand expRand;
	Packet current_packet;
	queue<Packet> input;
	queue<Packet> output;
};

#endif
