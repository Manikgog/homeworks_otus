#include "check_value.h"

#include <iostream>

int checkValue(int target_value)
{
    int current_value = 0;
    std::cout << "Enter your guess:" << std::endl;
    int count = 1;
    do
    {
        std::cin >> current_value;

        if (current_value > target_value)
        {
            std::cout << "less than " << current_value << std::endl;
        }
        else if (current_value < target_value)
        {
            std::cout << "greater than " << current_value << std::endl;
        }
        else
        {
            std::cout << "you win!" << std::endl;
            break;
        }
        count++;
    } while(true);
    return count;
}