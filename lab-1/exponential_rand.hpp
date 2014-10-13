#include <random>
#include <math.h>

class Exponential_rand 
{
    
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
    int packets_per_second;
    int ticks_per_second;
    
    
public:    
    Exponential_rand(int pps, int tps) : distribution(0.0, 1.0), packets_per_second(pps), ticks_per_second(tps) { };
    
    int get_random_ticks()
    {
        double u = distribution(generator);
        return ticks_per_second*((-1.0 / (double)packets_per_second) * log(1 - u));
    };
};
