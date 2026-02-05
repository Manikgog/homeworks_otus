#include <cstdlib>
#include <ctime>

#include "get_random_target.h"

int getRandomTarget(int max_number)
{
    std::srand(std::time(nullptr));
    return std::rand() % max_number;
}