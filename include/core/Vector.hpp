#ifndef CUSTOMER_CHURN_PREDICTION_VECTOR_HPP
#define CUSTOMER_CHURN_PREDICTION_VECTOR_HPP
class Vector
{
    public:
        Vector();
        Vector(std::vector<int>& array);
        Vector(std::initializer_list<int> array);
        explicit vector(size_t size);
        size_t size() const;
        double dot(const Vector& other) const;
        Vector operator+(const Vector& other) const;
        Vector operator-(const Vector& other) const;
        Vector operator*(double scalar) const;
        bool operator==(const Vector& other) const;
        double& operator[](size_t index);
        const double& operator[](size_t index) const;
    private:
        std::vector<double> data_;
};
#endif