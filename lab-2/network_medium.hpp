#ifndef _NETWORK_MEDIUM_HPP
#define _NETWORK_MEDIUM_HPP

#include "packet.hpp"
#include "computer.hpp"

class Network_medium : public Simulatable {
    public:
        Network_medium(unsigned int ticks_per_sec);
        void run_tick(unsigned long long int tick);
        void transmit_packet(Computer* sender, Packet p);
};

#endif
