#pragma once

#include "vector2D.h"

// Body struct
struct Body {
    Vec2D pos, vel, acc, prevPos;
    float mass, radius;
    // Constructor to initialize the body
    Body(const Vec2D& pos, const Vec2D& vel, float mass, float r);

    // Update function
    void update(float dt, void (*integrator)(Body&, float));
};


