#include<iostream>
#include<memory>
#include<iomanip>
#include"include/utils/CSVReader.hpp"
#include"include/core/ProcessedData.hpp"
#include"include/core/Splitter.hpp"
using namespace std;
int main()
{
    auto data = CSVReader::readCSV("data/WA_Fn-UseC_-Telco-Customer-Churn.csv");
    auto processedDATA = CSVReader::preprocess(data, true, 20, {0});
    for(const auto& header : processedDATA.headers) std::cout<<header<<" | ";
    std::unique_ptr<Splitter> mysplitter = std::make_unique<RandomSplitter>();
    auto splitdata = mysplitter->split(processedDATA, 0.8);
    return 0;
}