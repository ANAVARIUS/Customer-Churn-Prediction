#include"../../include/utils/CSVReader.hpp"

std::vector<std::vector<std::string>> CSVReader::readCSV(const std::string& filePath)
{
    std::ifstream file(filePath);
    if(!file.is_open()) throw std::invalid_argument("Could not open file " + filePath);
    std::vector<std::vector<std::string>> data;
    std::string line;
    while(std::getline(file, line))
    {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while(std::getline(ss, cell, ',')) row.push_back(cell);
        if(data.size() && (row.size() != data[0].size()))
            throw std::invalid_argument("The number of columns in the file is inconsistent");
        data.push_back(row);
    }
    return data;
}