#include "packet.hpp"

Packet::Packet(unsigned int s, unsigned long long int start_tick) :
	size(s),
	creation_tick(start_tick)
{

}

void Packet::processing_complete(unsigned long long int end)
{
	end_tick = end;
}

