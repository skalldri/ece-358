#include "computer.hpp"

using namespace std;

Computer::Computer(Network_medium* med, Csma_mode c, float p, int i, unsigned int pack_size, unsigned int pps, unsigned int ticks_per_sec, unsigned int bps) :
    Simulatable(ticks_per_sec),
    expRand(pps, ticks_per_sec, rand())
{
	bits_per_second = bps;
	csma = c;
	state = IDLE;
	csma_p = p;
        id = i;
	medium = med;
	packet_size = pack_size;
	to_transmit = 0;
	collision_count = 0;
	timeout = 0;
	packets_per_second = pps;
	next_creation = expRand.get_random_ticks();
}

Computer::~Computer()
{

}
    
void Computer::run_tick(unsigned long long int tick)
{	
	if(state == IDLE)
	{
		if(input.size() > 0) // There is a packet to transmit, and we are currently idle
		{
			//cout << "Computer " << get_id() << " beginning medium sense" << endl;
			medium_sense_time = (96.0/((float)bits_per_second)) * (float)ticks_per_second; // Set the number of ticks we will observe the medium for
			state = MEDIUM_SENSE;
		}
	}
	else if(state == MEDIUM_SENSE)
	{
		switch(csma)
		{
			case CSMA_PERSISTENT:
			
				medium_sense_time--;			
	
				if(medium->is_busy(this))
				{
					medium_sense_time = (96.0/((float)bits_per_second)) * (float)ticks_per_second;
					return;
				}

				if(medium_sense_time <= 0)
				{
					//cout << "Computer " << get_id() << " beginning transmit" << endl;
					state = TRANSMIT;
	        			to_transmit = (ticks_per_second / bits_per_second) * input.front().size; //to_transmit is the number of ticks we need to transmit for to send the packet
					collision_count = 0;
				}
			
				break;
			
			case CSMA_NON_PERSISTENT:
			break;

			case CSMA_P_PERSISTENT:
			break;
		}
	}
	else if(state == TRANSMIT)
	{
		medium->transmit(this);

		if(medium->is_busy(this)) // Collision occurred
		{
			//cout << "Computer " << get_id() << " detected collision" << endl;
			state = EXP_BACKOFF;
			collision_count++;
			backoff_count = (rand() % (2 << collision_count)) * ((512.0/((float)bits_per_second)) * (float)ticks_per_second);
		}

		to_transmit--;

		if(to_transmit <= 0)
		{
			//cout << "Computer " << get_id() << " transmit complete, returning to IDLE" << endl;
			output.push(input.front());
			input.pop();
			state = IDLE;
		}
	}
	else if(state == EXP_BACKOFF)
	{
		backoff_count--;

		if(backoff_count <= 0)
		{
			//cout << "Computer " << get_id() << " exp backoff complete, returning to IDLE" << endl;
			state = IDLE;
		}
	}
			
	if(tick >= next_creation) {
		generate_packet(tick);
	}    
}

int Computer::get_id()
{
	return id;
}

void Computer::generate_packet(unsigned long long int current_tick)
{
	unsigned int random = expRand.get_random_ticks();
	next_creation = random + current_tick;
	Packet t = Packet(packet_size, current_tick);
	input.push(t);
	//cout << "Computer " << get_id() << " generating packet in tick " << current_tick << endl;
}
