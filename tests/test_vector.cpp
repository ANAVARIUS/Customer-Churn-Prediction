#include "catch.hpp"
#include "../include/core/Vector.hpp"
#include "vector"

TEST_CASE("INIIALIZAR VECTOR", "[vector]"){
    std::vector<double> array(10, 12);
    Vector v1(array);
    Vector v2 = Vector(array);
    Vector v3 = Vector();
    Vector v4 = Vector(10);
    Vector v5;
    REQUIRE_THROWS_AS(Vector(-5), std::invalid_argument);
    REQUIRE(v1.size() == 10);
    REQUIRE(v1[0] == 12);
    REQUIRE(v2.size() == 10);
    REQUIRE(v2[0] == 12);
    REQUIRE(v3.size() == 0);
    REQUIRE_THROWS_AS(v3[0], std::out_of_range);
    REQUIRE(v4.size() == 10);
    REQUIRE(v5.size() == 0);
}

TEST_CASE("SUMAR VECTORES", "[vector]"){
    Vector v1 = {1, 2, 3, 4};
    Vector v2 = {1, 2, 3, 4};
    Vector v3 = v1 + v2;
    REQUIRE(v3 == Vector({2, 4, 6, 8}));
}

TEST_CASE("RESTAR VECTORES", "[vector]"){
    Vector v1 = {1, 2, 3, 4};
    Vector v2 = {1, 2, 3, 4};
    Vector v3 = v1 - v2;
    REQUIRE(v3 == Vector({0, 0, 0, 0}));
    REQUIRE(v2 - Vector({1, 1, 1, 1}) == Vector({0, 1, 2, 3}));
}

TEST_CASE("PRODUCTO PUNTO", "[vector]"){
    Vector v1 = {51, 74, 22, 98};
    Vector v2 = {27, 31, 55, 2};
    double scalar = v1.dot(v2);
    REQUIRE(scalar == 5077.0);
    REQUIRE(Vector({0, 0, 0, 0}).dot(v2) == 0);
}

TEST_CASE("OPERACIONES CON DIFERENTES TAMAÑOS", "[vector]") {
    Vector v1 = {1, 2, 3};
    Vector v2 = {4, 5};
    REQUIRE_THROWS_AS(v1 + v2, std::invalid_argument);
    REQUIRE_THROWS_AS(v1 - v2, std::invalid_argument);
    REQUIRE_THROWS_AS(v1.dot(v2), std::invalid_argument);
}