#include <iostream>
#include "simulator.hpp"
#include "computer.hpp"
#include "network_medium.hpp"

//#define PREAMBLE //Undefine this to remove a lot of the message dumping procedure. See also #define DEBUG

using namespace std;

static const unsigned long long int ticks_per_second  = 1000000000; // 1 tick = 1 ns
             unsigned int packets_per_second          = 100;        //
static const unsigned int packet_size                 = 2000;       // 2000 bits
             int          max_queue_size              = -1;         // Unlimited size
static const unsigned int bits_per_second             = 1000000;    // 1 Mbps
static const unsigned long long int simulation_time   = ticks_per_second * 5; // Simulate for 10 seconds

//Time required to process one packet
static unsigned int processing_time(unsigned int ticks_per_second, unsigned int bits_per_second, unsigned int packet_size)
{
    return (ticks_per_second / bits_per_second) * packet_size;
}

int main(int argc, char *argv[]) {

    cout << "Please enter max queue size: ";
    cin >> max_queue_size;
    cout << "Max Queue Size is " << max_queue_size << endl;

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
    
    network_simulator.run();
    
    cout << "-------------STATISTICS---------------" << endl << endl;
    
}

