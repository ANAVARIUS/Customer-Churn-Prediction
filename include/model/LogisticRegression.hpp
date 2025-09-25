#ifndef CUSTOMER_CHURN_PREDICTION_LOGISTICREGRESSION_HPP
#define CUSTOMER_CHURN_PREDICTION_LOGISTICREGRESSION_HPP
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <vector>
#include <cmath>
#include "../core/Vector.hpp"
#include "../core/Matrix.hpp"
#include "../core/ProcessedData.hpp"

class LogisticRegression
{
    public:
        LogisticRegression(size_t n_features);
        double predict(const Vector& x) const;
        void train(const ProcessedData& data, double alpha, int epochs);
        double accuracy(const ProcessedData& test) const;
        double precision(const ProcessedData& test) const; //Of all customers I said will churn, how many really did?
        double recall(const ProcessedData& test) const; //Of all churners, how many did I catch?
        double f1Score(const ProcessedData& test) const;
        void save(const std::string& filename) const;
        void load(const std::string& filename);
    private:
        Vector weights;
        double bias;
        double loss;
        double sigmoid(const double z);
        double computeLoss(const double y_true, const double y_pred) const; //Calculates Loss using cross enthropy loss function
        void updateWeights(const ProcessedData& data, const double& alpha) const;
    };
}

#endif