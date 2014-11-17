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
			random_wait_count = 0;
		}
	}
	else if(state == MEDIUM_SENSE)
	{
		switch(csma)
		{
			case CSMA_PERSISTENT:
				if(medium_sense_time > 0)	
					medium_sense_time--;			

				if(medium->is_busy(this)) // Medium is busy, skip the sense waiting period
				{
					medium_sense_time = 0;
				}
				else if(medium_sense_time <= 0) // Medium was not busy, TRANSMIT!
				{
					//cout << "Computer " << get_id() << " beginning transmit" << endl;
					state = TRANSMIT;
	        			to_transmit = (ticks_per_second / bits_per_second) * input.front().size; //to_transmit is the number of ticks we need to transmit for to send the packet
					collision_count = 0;
				}
			
				break;
			
			case CSMA_NON_PERSISTENT:
				if(medium_sense_time > 0)
					medium_sense_time--;
				
				if(medium->is_busy(this))
				{
					if(medium_sense_time <= 0) //We have finished a waiting period, but the medium is still busy
					{
						if(random_wait_count < 10)
							random_wait_count++;

						medium_sense_time = (rand() % (2 << random_wait_count)) * ((512.0/((float)bits_per_second)) * (float)ticks_per_second);
					}
				}
				else if(medium_sense_time <= 0) //Medium wasn't busy and we're at the end of a waiting period, GO!
				{
					//cout << "Computer " << get_id() << " beginning transmit" << endl;
					state = TRANSMIT;
	        			to_transmit = (ticks_per_second / bits_per_second) * input.front().size; //to_transmit is the number of ticks we need to transmit for to send the packet
					collision_count = 0;
				}
			break;

			case CSMA_P_PERSISTENT:
				if(medium_sense_time > 0)	
					medium_sense_time--;			

				if(medium->is_busy(this)) // Medium is busy, skip the sense waiting period
				{
					medium_sense_time = 0;
				}
				else if(medium_sense_time <= 0) // Medium was not busy, POSSIBLY TRANSMIT!
				{
					//cout << "Computer " << get_id() << " beginning transmit" << endl;
					int probability = rand() % 101;
					float comparator = csma_p * 100.0;
					
					state = TRANSMIT;
	        			to_transmit = (ticks_per_second / bits_per_second) * input.front().size; //to_transmit is the number of ticks we need to transmit for to send the packet
					collision_count = 0;
				}
			break;
		}
	}
	else if(state == TRANSMIT)
	{
		medium->transmit(this);

		if(to_transmit > 0)
			to_transmit--;

		if(medium->is_busy(this)) // Collision occurred
		{
			//cout << "Computer " << get_id() << " detected collision, beginning Jamming" << endl;
			state = JAMMING;
			jamming_time = (48.0/((float)bits_per_second)) * (float)ticks_per_second;
		}
		else if(to_transmit <= 0)
		{
			//cout << "Computer " << get_id() << " transmit complete, returning to IDLE" << endl;
			Packet done = input.front();
			done.processing_complete(tick);
			output.push(done);
			input.pop();
			state = IDLE;
		}
	}
        else if(state == JAMMING)
	{
		medium->transmit(this);
	
		if(jamming_time > 0)
			jamming_time--;

		if(jamming_time <= 0)
		{
			//cout << "Computer " << get_id() << " beginning exponential backoff" << endl;
			state = EXP_BACKOFF;

			if(collision_count < 10)
				collision_count++;

			backoff_count = (rand() % (2 << collision_count)) * ((512.0/((float)bits_per_second)) * (float)ticks_per_second);
		}
	}
	else if(state == EXP_BACKOFF)
	{
		if(backoff_count > 0)
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
	//cout << "Computer " << get_id() << " queue length " << input.size() << endl;
	//cout << "Computer " << get_id() << " current state is " << state << endl;
}
