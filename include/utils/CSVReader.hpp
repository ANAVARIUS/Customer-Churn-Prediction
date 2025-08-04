#ifndef CUSTOMER_CHURN_PREDICTION_CSVREADER_HPP
#define CUSTOMER_CHURN_PREDICTION_CSVREADER_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "../core/Vector.hpp"
namespace CSVReader
{
    std::vector<std::vector<std::string>> readCSV(const std::string& filePath);
    std::vector<Vector> preprocess( const std::vector<std::vector<std::string>>& data,
                                    bool hasHeader,
                                    int churnColumn,
                                    std::vector<int> dropColumns);
}
#endif