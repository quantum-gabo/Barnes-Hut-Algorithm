#pragma once

struct Vec2D {
    float x, y;

    // Constructor to initialise the vector
    Vec2D(float x = 0, float y = 0);

    // Overload the addition operator
    Vec2D operator+(const Vec2D& other) const;

    // Overload the multiplication operator
    Vec2D operator*(float scalar) const;

    // Overload the subtraction operator
    Vec2D operator-(const Vec2D& other) const;

    Vec2D operator += (const Vec2D& other);

    Vec2D operator -= (const Vec2D& other);

    Vec2D operator *= (float scalar);

    bool operator == (const Vec2D& other) const;

    Vec2D operator /= (float scalar);

    // Overload the division operator
    Vec2D operator/(float scalar) const;

    float magSqr() const;

    // Static function zero-vector
    static Vec2D zero();
};