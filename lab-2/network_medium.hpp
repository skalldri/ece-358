#ifndef _NETWORK_MEDIUM_HPP
#define _NETWORK_MEDIUM_HPP

#include <iostream>
#include <vector>
#include <math.h>
#include "packet.hpp"
#include "debug_log.hpp"

class Computer;

enum SignalState {
  TRANSMITTED,
  ANTICIPATED,
  TERMINATED
};

typedef struct Collision_event_s {
	Computer * source; // The computer that is transmitting the signal
	float on_propagation_length; // The length (in meters) that the propagation of a "signal on" event has propagated
    float off_propagation_length; // The length (in meters) that the propagation of a "signal off" event has propagated
    SignalState state; // If this signal has stopped transmitting and now we're just waiting for the "signal off" to propagate
} Collision_event;

class Network_medium : public Simulatable {
    public:
        Network_medium(unsigned int ticks_per_second, unsigned int num_comp, float prop_speed);
        void run_tick(unsigned long long int tick);
        void transmit(Computer* sender);
        bool is_busy(Computer* sender);
        int get_speed();

    private:
        unsigned long long int current_tick;
        unsigned int num_computers; 
        float propagation_speed; // In meters / sec
        int speed;
        std::vector<Collision_event> collisions;        
};

#endif
