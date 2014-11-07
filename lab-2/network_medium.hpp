#ifndef _NETWORK_MEDIUM_HPP
#define _NETWORK_MEDIUM_HPP

#include <iostream>
#include "packet.hpp"
#include "computer.hpp"

typedef struct Collision_event_s {
	Computer * source; // The computer that is transmitting the signal
	unsigned int on_propagation_length; // The length (in nodes) that the propagation of a "signal on" event has propagated
    unsigned int off_propagation_length; // The length (in nodes) that the propagation of a "signal off" event has propagated
    unsigned long long int next_on_propagation_tick; // The next tick that the "signal on" propagation will increase
    unsigned long long int next_off_propagation_tick; // The next tick that the "signal off" propagation will increase
} Collision_event;

class Network_medium : public Simulatable {
    public:
        Network_medium(unsigned int ticks_per_sec, unsigned int num_computer);
        void run_tick(unsigned long long int tick);
        void transmit(Computer* sender);
        bool is_busy(Computer* sender);

    private:
        unsigned long long int current_tick;
        unsigned int num_computers;
        
        std::vector<Collision_event> collisions;        
};

#endif
