#include"catch.hpp"
#include"../include/log/Logger.hpp"
#include "../include/core/Matrix.hpp"
#include "../include/core/Vector.hpp"
#include "../include/core/ProcessedData.hpp"
#include "../include/model/LogisticRegression.hpp"

TEST_CASE("SIGMOID PRODUCES VALUES BETWEEN 0 AND 1", "[model]")
{
    LogisticRegression model(1);
    REQUIRE(model.sigmoid(0.0) == Approx(0.5).margin(1e-5));
    REQUIRE(model.sigmoid(100.0) == Approx(1.0).margin(1e-5));
    REQUIRE(model.sigmoid(-100.0) == Approx(0.0).margin(1e-5));
}

TEST_CASE("PREDICT RETURNS EXPECTED PROBABILITY", "[model]")
{
    LogisticRegression model(2);
    model.weights = Vector{1.0, -1.0};
    model.bias = 0.0;
    Vector x{2.0, 1.0};
    double expected_prob = 1.0 / (1.0 + std::exp(-1.0));
    double y_pred = model.predict(x);
    REQUIRE(y_pred == Approx(expected_prob));
}

TEST_CASE("UPDATEWEIGHTS ADJUSTS WEIGHTS IN THE RIGHT DIRECTION", "[model]")
{
    LogisticRegression model(1);
    model.weights = Vector{0.0};
    model.bias = 0.0;
    ProcessedData data;
    data.features = Matrix(2, 1);
    data.features[0][0] = 1.0;
    data.features[1][0] = 2.0;
    data.churnResults = Vector{0.0, 1.0};
    model.updateWeights(data, 0.1);
    REQUIRE(model.weights[0] == Approx(0.05749).margin(0.001));
    REQUIRE(model.bias == Approx(0.00374).margin(0.001));
}

TEST_CASE("TRAINING REDUCES LOSS AND CLASSIFIES CORRECTLY", "[model]")
{
    ProcessedData data;
    data.features = Matrix(4, 2);
    data.features[0] = Vector{0.0, 0.0};
    data.features[1] = Vector{0.0, 1.0};
    data.features[2] = Vector{1.0, 0.0};
    data.features[3] = Vector{1.0, 1.0};
    data.churnResults = Vector{0.0, 0.0, 0.0, 1.0};
    LogisticRegression model(2);
    double alpha = 0.5;
    int epochs = 750;
    model.train(data, alpha, epochs);
    Vector positive_sample{1.0, 1.0};
    double y_pred_positive = model.predict(positive_sample);
    REQUIRE(y_pred_positive > 0.85);
    Vector negative_sample{0.0, 0.0};
    double y_pred_negative = model.predict(negative_sample);
    REQUIRE(y_pred_negative < 0.15);
}

TEST_CASE("ACCURACY, PRECISION, RECALL, F1SCORE COMPUTE CORRECTLY", "[model]")
{
    ProcessedData test_data;
    test_data.features = Matrix{
        Vector{0.0},
        Vector{1.0},
        Vector{2.0}
    };
    test_data.churnResults = Vector{0.0, 0.0, 1.0};
    LogisticRegression model(1);
    model.weights = Vector{1.0};
    model.bias = -0.5;
    REQUIRE(model.accuracy(test_data) == Approx(2.0 / 3.0));
    REQUIRE(model.precision(test_data) == Approx(0.5));
    REQUIRE(model.recall(test_data) == Approx(1.0));
    REQUIRE(model.f1Score(test_data) == Approx(2.0 / 3.0));
}

TEST_CASE("PERSISTENCE SAVE/LOAD CHECK", "[model]")
{
    LogisticRegression model(3);
    const std::string filename = "simple_test_model.json";
    model.weights = Vector({0.1, -0.5, 0.9});
    model.bias = 0.42;
    double original_bias = model.bias;
    Vector original_weights = model.weights;
    REQUIRE_NOTHROW(model.save(filename));
    LogisticRegression loaded_model(3);
    REQUIRE_NOTHROW(loaded_model.load(filename));
    REQUIRE(loaded_model.bias == Approx(original_bias));
    REQUIRE(loaded_model.weights.size() == original_weights.size());
    for (size_t i = 0; i < loaded_model.weights.size(); ++i) {
        REQUIRE(loaded_model.weights[i] == Approx(original_weights[i]));
    }
    std::remove(filename.c_str());
}
