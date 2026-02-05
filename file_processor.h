#pragma once

#include <string>

static std::string file_name = "table.txt";
static std::string file_name_level1 = "level1_table.txt";
static std::string file_name_level2 = "level2_table.txt";
static std::string file_name_level3 = "level3_table.txt";

bool fileExists(const std::string& filename);

std::string findStringWithName(const std::string& name, const std::string& filename);

void rewriteString(int points, const std::string& name, const std::string& filename);

void writePointsToFile(const std::string& name, int points, const std::string& filename);

std::string readTableFromFile(const std::string& filename);

void createFile(const std::string& filename);

void createFileItNotExist(const std::string& filename);