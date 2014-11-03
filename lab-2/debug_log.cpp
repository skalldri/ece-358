#include "debug_log.hpp"

void debug_log(std::string message)
{
    #ifdef DEBUG
    std::cout << message << std::endl;
    #endif
}
