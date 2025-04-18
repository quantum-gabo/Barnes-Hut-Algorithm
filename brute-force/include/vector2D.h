#pragma once

struct Vec2D {
    float x, y;

    // Constructor to initialise the vector
    Vec2D(float x = 0, float y = 0);

    // Overload some operators
    Vec2D operator+(const Vec2D& other) const;
    Vec2D operator*(float scalar) const;
    Vec2D operator-(const Vec2D& other) const;
    Vec2D operator += (const Vec2D& other);
    Vec2D operator -= (const Vec2D& other);
    Vec2D operator *= (float scalar);
    bool operator == (const Vec2D& other) const;
    Vec2D operator /= (float scalar);
    Vec2D operator/(float scalar) const;

    float magSqr() const;
    static Vec2D zero();
};