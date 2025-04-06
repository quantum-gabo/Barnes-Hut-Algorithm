#include "vector2D.h"
#include <cmath> // For std::abs
#include <stdexcept> // For std::runtime_error

// Constructor
Vec2D::Vec2D(float x, float y) : x(x), y(y) {}

// Overload the addition operator
Vec2D Vec2D::operator+(const Vec2D& other) const {
    return Vec2D(x + other.x, y + other.y);
}

// Overload the multiplication operator
Vec2D Vec2D::operator*(float scalar) const {
    return Vec2D(x * scalar, y * scalar);
}

// Overload the subtraction operator
Vec2D Vec2D::operator-(const Vec2D& other) const {
    return Vec2D(x - other.x, y - other.y);
}

// Overload the addition assignment operator
Vec2D Vec2D::operator += (const Vec2D& other) {
    x += other.x;
    y += other.y;
    return *this;
}
// Overload the subtraction assignment operator
Vec2D Vec2D::operator -= (const Vec2D& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}
// Overload the multiplication assignment operator
Vec2D Vec2D::operator *= (float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

// Overload the equality operator
bool Vec2D::operator == (const Vec2D& other) const {
    const float epsilon = 1e-6f; // Define a small epsilon for floating-point comparison
    return std::abs(x - other.x) < epsilon && std::abs(y - other.y) < epsilon;
}

// Overload the division assignment operator
Vec2D Vec2D::operator /= (float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

// Overload the division operator
Vec2D Vec2D::operator/(float scalar) const {
    if (scalar == 0) {
        throw std::runtime_error("Division by zero");
    }
    return Vec2D(x / scalar, y / scalar);
}

// Function to calculate the squared magnitude of the vector
float Vec2D::magSqr() const {
    return x * x + y * y;
}

// Static function to return a zero vector
Vec2D Vec2D::zero() {
    return Vec2D(0, 0);
}
