#include<iostream>
#include<iomanip>
#include"include/utils/CSVReader.hpp"
using namespace std;
int main()
{
    auto data = CSVReader::readCSV("data/WA_Fn-UseC_-Telco-Customer-Churn.csv");
    for(auto row : data)
    {
        for(auto cell: row)
            cout<<std::setw(15)<<cell;
        cout<<endl<<"-------------------------------------------------------------------------"<<endl;
    }

    return 0;
}