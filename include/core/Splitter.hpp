#ifndef CUSTOMER_CHURN_PREDICTION_SPLITTER_HPP
#define CUSTOMER_CHURN_PREDICTION_SPLITTER_HPP
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <pair>
#include <algorithm>
#include <random>
struct Splitter
{
    virtual std::pair<ProcessedData, ProcessedData>split(const ProcessedData& data, double& ratio) = 0;
    virtual Splitter() = default;
};

struct RamdomSplitter : public Splitter
{
    std::pair<ProcessedData, ProcessedData>split(const ProcessedData& data, const double ratio) override;
};
#endif