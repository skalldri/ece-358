#ifndef _PACKET_HPP
#define _PACKET_HPP

class Packet
{
public:
	Packet(unsigned int size, unsigned long long int start_tick);
	
	void processing_complete(unsigned long long int end_tick);
    
	unsigned int size;
	unsigned long long creation_tick;
	unsigned long long end_tick;
		
};

#endif //_PACKET_HPP
