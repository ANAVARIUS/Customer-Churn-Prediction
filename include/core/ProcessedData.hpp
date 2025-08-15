#ifndef CUSTOMER_CHURN_PREDICTION_PROCESSEDDATA_HPP
#define CUSTOMER_CHURN_PREDICTION_PROCESSEDDATA_HPP
#include <vector>
#include <string>
#include "Matrix.hpp"
struct ProcessedData
{
    Matrix features;
    std::vector<std::string> headers;
    std::vector<double> churnResults;
};
#endif