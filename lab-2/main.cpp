#include <iostream>
#include "simulator.hpp"
#include "computer.hpp"
#include "network_medium.hpp"

//#define PREAMBLE //Undefine this to remove a lot of the message dumping procedure. See also #define DEBUG

using namespace std;

static const unsigned long long int ticks_per_second  = 100000000; // 1 tick = 1 us
             unsigned int packets_per_second          = 4;        //
static const unsigned int packet_size                 = 1500 * 8;   // 1500 bytes (It takes 0.012 seconds to transmit this at 1 Mbps)
	     int          num_computers               = 20;
static const unsigned int bits_per_second             = 1000000;    // 1 Mbps
static const unsigned int seconds                     = 60;
static const unsigned long long int simulation_time   = ticks_per_second * seconds; // Simulate for 10 seconds
static const unsigned int propagation_speed           = 2 * 100000000; // meters per second (This is fast enough to ensure that collisions can always be heard)

//Time required to process one packet
static unsigned int processing_time(unsigned int ticks_per_second, unsigned int bits_per_second, unsigned int packet_size)
{
    return (ticks_per_second / bits_per_second) * packet_size;
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    cout << "Please enter number of computers: ";
    cin >> num_computers;
    cout << "Number of computers on lan is " << num_computers << endl;

    cout << "Please enter packets per second: ";
    cin >> packets_per_second;
    cout << "Packets per second is " << packets_per_second << endl;

    Simulator network_simulator(simulation_time);
        
    
    #ifdef PREAMBLE
    cout << "-------------ECE 358 NETWORK SIMULATOR---------------" << endl << endl;
    cout << "             ONE TICK IS ONE NANOSECOND" << endl << endl;
    cout << "Ticks per sim-second: " << ticks_per_second << endl;
    cout << "Packets per sim-second: " << packets_per_second << endl;
    cout << "Packet size: " << packet_size << " bytes" << endl;
    cout << "Bits per sim-second: " << bits_per_second << " bits" << endl;
    cout << "Packet processing time: " << processing_time(ticks_per_second, bits_per_second, packet_size) << " ticks" << endl;
    cout << "Average time between packets: " << (ticks_per_second / packets_per_second) << " ticks" << endl;
    cout << "Total ticks: " << simulation_time << " ticks" << endl << endl;
    cout << "-------------MESSAGES---------------" << endl << endl;
    #endif
    
    vector<Computer*> computers;
    Network_medium medium(ticks_per_second, num_computers, propagation_speed);

    Csma_mode csma        = CSMA_PERSISTENT;
    float     csma_p      = 1.0;

    for(int i = 0; i < num_computers; i++)
    {
	Computer* comp = new Computer(&medium, CSMA_PERSISTENT, csma_p, i, packet_size, packets_per_second, ticks_per_second, bits_per_second);

	computers.push_back(comp);
	network_simulator.add_simulatable(comp);
    }

    network_simulator.add_simulatable(&medium);

    network_simulator.run();
    
    cout << "-------------STATISTICS---------------" << endl << endl;

    float sojourn_time_total = 0.0;
    unsigned long long int num_bits = 0;
    unsigned long long int total_packets = 0;
    unsigned long long int total_sent_packets = 0;
   
    for(vector<Computer*>::iterator it = computers.begin();
        it != computers.end();
        ++it)
    {   
	total_sent_packets += (*it)->output.size();
	total_packets += (*it)->output.size();
	total_packets += (*it)->input.size();

        while((*it)->output.size() > 0)
        {
            Packet finished = (*it)->output.front();
            (*it)->output.pop();

            num_bits += finished.size;
            sojourn_time_total += (finished.end_tick - finished.creation_tick);
	    /*
	    cout << "Computer " << 
		    (*it)->get_id() << 
		    " had packet that took " << 
                    (finished.end_tick - finished.creation_tick) << 
                    " ticks to transmit" << endl;*/
        }
    }

    cout << "Average packets / sec: " << (float)total_packets / (float)(num_computers * seconds) << endl;
    cout << "Successfully transmitted packets: "  << total_sent_packets << endl;
    cout << "Total attempted to transmit packets: " << total_packets << endl;
    cout << "Average Delay: " <<  sojourn_time_total / (float)(total_sent_packets * ticks_per_second) << endl;
    cout << "Average Throughput: " << (float)num_bits / (float)(seconds) << " bits/sec" << endl;
    
    return 0;
}


