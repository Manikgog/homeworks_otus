#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "get_random_target.h"
#include "check_value.h"
#include "file_processor.h"

static int level1_max_number = 10;
static int level2_max_number = 50;
static int level3_max_number = 100;


std::string inputName()
{
    std::string name;
    while (true)
    {
        std::cout << "Input your name: ";
        std::getline(std::cin, name);
        if (!name.empty())
        {
            break;
        }
        std::cout << "name must be not empty" << std::endl;
    }
    return name;
}


void gameProcess(const std::string& statistic_file_name, int max_number)
{
    std::string name = inputName();
    if (!fileExists(statistic_file_name))
    {
        createFile(statistic_file_name);
    }
    int target_number = getRandomTarget(max_number);
    int points = checkValue(target_number);
    writePointsToFile(name, points, statistic_file_name);
}

void processTableVariant()
{
    std::cout << "*********************************" << std::endl;
    std::cout << "High scores table:" << std::endl;
    std::cout << readTableFromFile(file_name) << std::endl;
    std::cout << "High scores level 1 table:" << std::endl;
    std::cout << readTableFromFile(file_name_level1) << std::endl;
    std::cout << "High scores level 2 table:" << std::endl;
    std::cout << readTableFromFile(file_name_level2) << std::endl;
    std::cout << "High scores level 3 table:" << std::endl;
    std::cout << readTableFromFile(file_name_level3) << std::endl;
    std::cout << "*********************************" << std::endl;
}


int main(int argc, char** argv)
{

    if (argc < 2)
    {
        std::cout << "Input max number after key '-max'" << std::endl;
        return -1;
    }
    if (!fileExists(file_name))
    {
        createFile(file_name);
    }

    if (argc == 2)
    {
        std::string arg1_value{ argv[1] };
        if (arg1_value == "-table")
        {
            processTableVariant();
            return 0;
        }
        if (arg1_value == "-help")
        {
            std::string help = R"(
Commands:
    -max 'number' -> Where the number is the maximum number within which the number is guessed for its search.
    -table -> Command to get high scores tables.
    -level 'number' -> Where number is the difficulty level number. 1 is the number to search for from 0 to 10, 2 is from 0 to 50, 3 is from 0 to 100.
)";
            std::cout << help << std::endl;
            return 0;
        }
    }

    if (argc == 3)
    {
        std::string arg1_value{ argv[1] };
        if (arg1_value == "-max")
        {
            gameProcess(file_name, std::stoi(argv[2]));
            return 0;
        }
        if (arg1_value == "-level")
        {
            int level = std::stoi(argv[2]);
            switch (level)
            {
            case 1:
                {
                    gameProcess(file_name_level1, level1_max_number);
                    break;
                }
            case 2:
                {
                    gameProcess(file_name_level2, level2_max_number);
                    break;
                }
            case 3:
                {
                    gameProcess(file_name_level3, level3_max_number);
                    break;
                }
            default:
                {
                    std::cout << "Invalid level number: " << level << ". Levels can range from 1 to 3." << std::endl;
                }
            }
            return 0;
        }
    }
    std::cout << "Invalid number of arguments: " << argc << ". For help enter: -help" << std::endl;
    return -1;
}