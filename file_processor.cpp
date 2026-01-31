#include <fstream>
#include <iostream>

#include "file_processor.h"

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::string findStringWithName(const std::string& name, const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    std::string n;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            n = line.substr(0, line.find(' '));
            if (n == name)
            {
                return line;
            }
        }
    }
    return "";
}


void rewriteString(int points, const std::string& name, const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    std::string lines;
    std::string n;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            n = line.substr(0, line.find(' '));
            if (n == name)
            {
                lines += name + " " + std::to_string(points);
            }
            else
            {
                lines += line;
            }
            lines += "\n";
        }
    }
    file.close();
    std::ofstream f(filename);
    if (f.is_open()) {
        f << lines;
    }
    f.close();
}


int getPointsFromString(const std::string& line)
{
    int index_of_space = line.find(' ');
    if (index_of_space == -1)
    {
        return -1;
    }
    std::string number = line.substr(index_of_space, line.length());
    return stoi(number);
}

void writePointsToFile(const std::string& name, int points, const std::string& filename) {
    std::string string_with_name = findStringWithName(name, filename);
    if (points < getPointsFromString(string_with_name))
    {
        rewriteString(points, name, filename);
        return;
    }
    std::ofstream f(filename, std::ios::app);
    if (f.is_open()) {
        f << name << " " << points << "\n";
    }
    f.close();
}



std::string readTableFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string table;
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            table.append(line).append("\n");
        }
    }
    return table;
}

void createFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file.close();
    } else {
        std::cerr << "Failed to create a file " << filename << std::endl;
    }
}

void createFileItNotExist(const std::string& filename) {
    if (fileExists(file_name)) {
        std::cout << "File " << file_name << " is exists." << std::endl;
    }
    else {
        createFile(file_name);
    }
}
