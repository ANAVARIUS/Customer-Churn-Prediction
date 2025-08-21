#include "../../include/core/Splitter.hpp"
std::pair<ProcessedData, ProcessedData> RandomSplitter::split(const ProcessedData& data, const double ratio)
{
    Matrix shuffledData = data.features;
    Vector churnResults = data.churnResults;
    auto rng = std::default_random_engine {std::random_device{}()};
    size_t dataSize = shuffledData.size();
    std::vector<size_t> indices(dataSize);
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), rng);
    size_t limit = static_cast<size_t>(dataSize * ratio);
    ProcessedData train, test;
    for (size_t i = 0; i < limit; ++i)
    {
        train.features.push_back(shuffledData[indices[i]]);
        train.churnResults.push_back(churnResults[indices[i]]);
    }

    for (size_t i = limit; i < dataSize; ++i)
    {
        test.features.push_back(shuffledData[indices[i]]);
        test.churnResults.push_back(churnResults[indices[i]]);
    }
    train.headers = test.headers = data.headers;
    return {train, test};
}