#include<iostream>
#include<iomanip>
#include"include/utils/CSVReader.hpp"
#include "include/core/ProcessedData.hpp"
using namespace std;
int main()
{
    auto data = CSVReader::readCSV("data/WA_Fn-UseC_-Telco-Customer-Churn.csv");
    auto processedDATA = CSVReader::preprocess(data, true, 20, {0});
    return 0;
}