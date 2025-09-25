#include"../../include/model/LogisticRegression.hpp"

LogisticRegression::LogisticRegression(size_t n_features)
{
    weights = Vector(n_features);
    bias = 0.0;
    loss = 0.0;
}

double LogisticRegression::sigmoid(const double z)
{
    return 1.0 / (1.0 + std::exp(-z));
}

double LogisticRegression::predict(const Vector& x) const {
    double z = weights.dot(x) + bias;
    return sigmoid(z);
}

void LogisticRegression::train(const ProcessedData& data, double alpha, int epochs) {
    for (int e = 0; e < epochs; e++) {
        loss = computeLoss(data.churnResults[i], predict(data.features[i]));
        updateWeights(data, alpha);
    }
}

double LogisticRegression::computeLoss(const double y_true, const double y_pred) const
{
    double y_hat = std::min(std::max(y_pred, 1e-15), 1.0 - 1e-15);
    return -((y_true*std::log(y_hat))+((1-y_true)*std::log(1-y_hat)));
}

void LogisticRegression::updateWeights(const ProcessedData& data, const double& alpha)
{
    for(size_t i = 0; i < data.features.size(); ++i)
    {
        double gradient;
        double prediction = predict(data.features[i]);
        for(size_t j = 0; j < weights.size(); ++j)
        {
            gradient = (prediction - data.churnResults[i]) * data.features[i][j];
            weights[j] -= alpha * gradient;
        }
        bias -= alpha * (prediction - data.churnResults[i]);
    }
}

double LogisticRegression::accuracy(const ProcessedData& test) const
{
    size_t rightGuess = 0;
    for(size_t i = 0; i < test.features.size(); ++i)
    {
        if(test.churnResults[i] == std::round(predict(test.features[i])))
            rightGuess++;
    }
    return rightGuess / static_cast<double>(test.features.size());
};

double LogisticRegression::precision(const ProcessedData& test) const
{
    size_t predicted_positives = 0;
    size_t true_positives = 0;
    for(size_t i = 0; i < test.features.size(); ++i)
    {
        if(std::round(predict(test.features[i])))
        {
            predicted_positives++;
            if(test.churnResults[i])
                true_positives++;
        }
    }
    return true_positives / static_cast<double>(predicted_positives);
};

double LogisticRegression::recall(const ProcessedData& test) const
{
    size_t correctly_predicted_positives = 0;
    size_t true_positives = 0;
    for(size_t i = 0; i < test.features.size(); ++i)
    {
        if(test.churnResults[i])
        {
            true_positives++;
            if(std::round(predict(test.features[i])))
                correctly_predicted_positives++;
        }
    }
    return correctly_predicted_positives / static_cast<double>(true_positives);
};

double LogisticRegression::f1Score(const ProcessedData& test) const
{
    double model_precision = precision(test);
    double model_recall = recall(test);
    if (model_precision + model_recall == 0.0)
        return 0.0;
    return 2.0 * ((model_precision * model_recall) / (model_precision + model_recall));
};