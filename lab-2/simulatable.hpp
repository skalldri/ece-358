#ifndef _SIMULATABLE_HPP
#define _SIMULATABLE_HPP

class Simulatable {
public:
	Simulatable(unsigned int ticks_per_sec) : ticks_per_second(ticks_per_sec) { }
	
	virtual void run_tick(unsigned long long int tick) = 0;
	
protected:
	unsigned int ticks_per_second; // The number of nanoseconds that make up 1 tick
};

#endif //_SIMULATABLE_HPP
