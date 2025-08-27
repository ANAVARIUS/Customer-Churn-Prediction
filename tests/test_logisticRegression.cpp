#include"catch.hpp"
#include"../include/log/Logger.hpp"
#include "../include/core/Matrix.hpp"
#include "../include/core/Vector.hpp"
#include "../include/core/ProcessedData.hpp"
#include "../include/model/LogisticRegression.hpp"
//T0 RUN THESE TESTS, FIRST MAKE EVERY ATTRIBUTE ON THE LogisticRegression class public
TEST_CASE("SIGMOID PRODUCES VALUES BETWEEN 0 AND 1", "[model]")
{
    LogisticRegression model(1);
    REQUIRE(model.sigmoid(0.0) == Approx(0.5));
    REQUIRE(model.sigmoid(100.0) == Approx(1.0).margin(1e-5));
    REQUIRE(model.sigmoid(-100.0) == Approx(0.0).margin(1e-5));
}

TEST_CASE("PREDICT RETURNS EXPECTED PROBABILITY", "[model]")
{
    LogisticRegression model(2);
    model.weights = Vector{1.0, -1.0};
    model.bias = 0.0;
    Vector x{2.0, 1.0};
    double y_pred = model.predict(x);
    REQUIRE(y_pred == Approx(1.0 / (1.0 + std::exp(-1.0))));
}

TEST_CASE("UPDATEWEIGHTS ADJUSTS WEIGHTS IN THE RIGHT DIRECTION", "[model]")
{
    LogisticRegression model(1);
    model.weights = Vector{0.0};
    model.bias = 0.0;
    Matrix X(2, 1);
    X(0,0) = 1.0; X(1,0) = 2.0;
    Vector y_true{0.0, 1.0};
    Vector y_pred{0.5, 0.5};
    model.updateWeights(X, y_true, y_pred, 0.1);
    REQUIRE(model.weights[0] != 0.0);
    REQUIRE(model.bias != 0.0);
}

TEST_CASE("TRAINING REDUCES LOSS ON SIMPLE DATASET", "[model]")
{
    ProcessedData data;
    data.features = Matrix(4, 2);
    data.features(0,0)=0; data.features(0,1)=0;
    data.features(1,0)=0; data.features(1,1)=1;
    data.features(2,0)=1; data.features(2,1)=0;
    data.features(3,0)=1; data.features(3,1)=1;
    data.labels = Vector{0, 0, 0, 1};
    LogisticRegression model(2);
    double alpha = 0.1;
    int epochs = 500;
    model.train(data, alpha, epochs);
    Vector y_pred;
    for(size_t i=0;i<data.features.rows();i++)
        y_pred.push_back(model.predict(data.features.row(i)));
    REQUIRE(y_pred[3] > 0.5);
}

TEST_CASE("ACCURACY, PRECISION, RECALL, F1SCORE COMPUTE CORRECTLY", "[model]")
{
    ProcessedData test_data;
    test_data.features = Matrix(3,1);
    test_data.features(0,0)=0;
    test_data.features(1,0)=1;
    test_data.features(2,0)=2;
    test_data.labels = Vector{0,0,1};
    LogisticRegression model(1);
    model.weights = Vector{1.0};
    model.bias = -0.5;
    double acc = model.accuracy(test_data);
    REQUIRE(acc > 0.5);
}

