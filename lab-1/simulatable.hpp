class Simulatable {
public:
	Simulatable(unsigned int tick_resolution_ns) : tick_res_ns(tick_resolution_ns) { }
	~Simulatable();
	
	virtual void run_tick(unsigned long long int tick) = 0;
	
private:
	unsigned int tick_res_ns; // The number of nanoseconds that make up 1 tick
};
