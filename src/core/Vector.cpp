#include "../../include/core/Vector.hpp"

Vector::Vector() = default;
Vector::Vector(long long size)
{
    if(size < 0) throw std::invalid_argument("Vector::Vector(): size must be positive");
    data_ = std::vector<double>(size, 0.0);
};
size_t Vector::size() const
{
    return data_.size();
};
double Vector::dot(const Vector& other) const
{
    if(data_.size() != other.size()) throw std::invalid_argument("Vector::dot");
    double result = 0.0;
    for(size_t i = 0; i < size(); ++i) result += data_[i] * other[i];
    return result;
};
Vector Vector::operator+(const Vector& other) const
{
    if(data_.size() != other.size()) throw std::invalid_argument("Vector::operator+");
    std::vector<double> result(data_.size());
    for(size_t i = 0; i < size(); ++i) result[i] = data_[i] + other[i];
    return Vector(result);
};
Vector Vector::operator-(const Vector& other) const
{
    if(data_.size() != other.size()) throw std::invalid_argument("Vector::operator-");
    std::vector<double> result(data_.size());
    for(size_t i = 0; i < size(); ++i) result[i] = data_[i] - other[i];
    return Vector(result);
};
Vector Vector::operator*(double scalar) const
{
    std::vector<double> result(data_.size());
    for(size_t i = 0; i < size(); ++i) result[i] = data_[i]*scalar;
    return Vector(result);
};
bool Vector::operator==(const Vector& other) const
{
    if(data_.size() != other.size()) return false;
    for(size_t i = 0; i < size(); ++i) if(data_[i] != other[i]) return false;
    return true;
};
double& Vector::operator[](long long index)
{
    if(index >= data_.size() || index < 0) throw std::out_of_range("Vector::operator[]");
    return data_[index];
};
const double& Vector::operator[](long long index) const
{
    if(index >= data_.size() || index < 0) throw std::out_of_range("Vector::operator[]");
    return data_[index];
};