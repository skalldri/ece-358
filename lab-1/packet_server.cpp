#include "packet_server.hpp"

using namespace std;

Packet_server::Packet_server(unsigned int ticks_per_sec, int max_queue, unsigned int ticks) : 
	Simulatable(ticks_per_sec),
    max_queue_size(max_queue),
    service_ticks(ticks),
    next_tick(0),
    packets_dropped(0),
    total_packets(0),
    idle_ticks(0),
    total_queue_size(0)
{
    
}

/*
 * -
 * -Generate packet if neccessary
 * -Sleep until next time
 */
void Packet_server::run_tick(unsigned long long int tick)
{
	current_tick = tick;
    total_queue_size += queue.size();
    
    if(queue.size() > 0)
    {
        //If the next packet is done processing
        if(tick >= next_tick)
        {
            //Pop the packet off the input queue, set the completed time, put it in the "finished" queue 
            Packet finished = queue.front();
            queue.pop_front();
            finished.processing_complete(tick);
            finished_packets.push_back(finished);
            
            #ifdef DEBUG
            cout << "PACKET_SERVER: Packet processing completed. Stats: " << endl <<
                    "\tArrived in queue tick: " << finished.creation_tick << endl << 
                    "\tProcessing start tick: " << finished.end_tick - service_ticks << endl << 
                    "\tEnd tick: " << finished.end_tick << endl;
            #endif
            
            //If there are elements left in the queue
            if(queue.size() > 0)
            {
                next_tick = current_tick + service_ticks;
            }
            else
            {
                next_tick = 0;   
            }
        }
    }
    else
    {
        idle_ticks++;
        next_tick = 0;
    }
}

void Packet_server::add_packet(Packet pack)
{
    total_packets++;
    if(max_queue_size <= 0 || queue.size() < max_queue_size)
    {
        debug_log("PACKET_SERVER: Received new packet");
        queue.push_back(pack);
    
        //If no packet is currently processing
        if(next_tick == 0)
        {
            next_tick = current_tick + service_ticks;
        }
    }
    else
    {
        debug_log("PACKET_SERVER: ERROR! Dropping packet due to full queue");
        packets_dropped++;
    }
}
