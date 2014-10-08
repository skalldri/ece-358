#include <iostream>
#include "simulator.hpp"
#include "packet_generator.hpp"
#include "packet_server.hpp"

//ONE TICK IS ONE NANOSECOND

using namespace std;

static const unsigned int ticks_per_second   = 1000000000; // 1 tick = 1 ns
static const unsigned int packets_per_second = 100;
static const unsigned int packet_size        = 2000;     // 2000 bits
static const int          max_queue_size     = 10;       // Unlimited size
static const unsigned int bits_per_second    = 10000;
static const unsigned int simulation_time    = ticks_per_second * 60;

//Time required to process one packet
static unsigned int processing_time(unsigned int ticks_per_second, unsigned int bits_per_second, unsigned int packet_size)
{
    return (ticks_per_second / bits_per_second) * packet_size;
}

int main() {
	Simulator network_simulator(simulation_time);
    Packet_server server(ticks_per_second, max_queue_size, processing_time(ticks_per_second, bits_per_second, packet_size));
    Packet_generator generator(packets_per_second, packet_size, ticks_per_second, &server);
    
    network_simulator.add_simulatable(&server);
    network_simulator.add_simulatable(&generator);
    
    cout << "-------------ECE 358 NETWORK SIMULATOR---------------" << endl << endl;
    cout << "             ONE TICK IS ONE NANOSECOND" << endl << endl;
    cout << "Ticks per sim-second: " << ticks_per_second << endl;
    cout << "Packets per sim-second: " << packets_per_second << endl;
    cout << "Packet size: " << packet_size << " bytes" << endl;
    cout << "Bits per sim-second: " << bits_per_second << " bits" << endl;
    cout << "Packet processing time: " << processing_time(ticks_per_second, bits_per_second, packet_size) << " ticks" << endl;
    cout << "Average time between packets: " << (ticks_per_second / packets_per_second) << " ticks" << endl;
    
    network_simulator.run();
}


