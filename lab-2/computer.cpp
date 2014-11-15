#include "computer.hpp"

Computer::Computer(Network_medium* medium, unsigned int csma, float csma_p, int id, unsigned int packet_size, unsigned int packets_per_second, unsigned int ticks_per_sec) :
    Simulatable(ticks_per_sec)
{
	this.csma = csma;
	this.csma_p = csma_p;
    this.id = id;
	this->medium = medium;
	this.packet_size = packet_size;
	to_transmit = 0;
	collision_count = 0;
	timeout = 0;
	expRand = Exponential_rand(packets_per_second, ticks_per_second);
	input = queue<Packet>();
	output = queue<Packet>();
	generatePacket(tick);
}

Computer::~Computer()
{

}
    
void Computer::run_tick(unsigned long long int tick)
{	
	Packet tmp = input.front();
	if(to_transmit == 0 && tmp.creation_tick <= tick){
		to_transmit += tmp.size;
		current_packet = tmp;
		input.pop_front();
	}
			
	if(tick == next_creation){
		generatePacket(tick);
	}
	
	if(timeout > 0){
		timeout--;
		return
	}
	
	if(is_busy){
		if(to_transmit < packet_size)
			timeout = collision_handler();

		if(csma == CSMA_NON_PERSISTENT)
			timeout = timeout_handler(96 / medium->get_speed() * ticks_per_second);
		
		return;
	}
	
	if(to_transmit > 0){
		to_transmit--;
		if(to_transmit == 0)
			current_packet.processing_complete(tick);
			output.push_back(current_packet);
			collision_count = 0;
	}
		
    // Check and see if we want to transmit during this tick (do we have a new packet to transmit OR are we currently transmitting a packet?)
    // Also, if we need to transmit a new packet and we're currently transmitting, queue the packet
    
    // If no, return
    
    // If yes, try and transmit a packet over the medium
    
    // Cannot immediately know if a collision occurred: what if this is the first transmission during this tick, but there are others?
    // Solution: the Network_medium will callback anyone who needs to know about collisions
    
}

// Called by the network medium whenever a collision occurs
int Computer::collision_handler()
{
	return timeout_handler(pow(2, ++collision_count));
    // Abort transmitting current packet and requeue according to CSMA/CD
}

int Computer::timeout_handler(int n)
{
	rand() % n + 1;
}

int Computer::get_id()
{
	return id;
}

void Computer::generate_packet(unsigned long long int current_tick)
{
	int random = expRand.get_random_ticks();
	next_creation = random + current_tick;
	input.push_back(new Packet(packet_size, next_creation));
}
