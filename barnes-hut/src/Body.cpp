#include "Body.h"

Body::Body(const Vec2D& pos, const Vec2D& vel, float mass, float r)
    : pos(pos), vel(vel), acc(Vec2D::zero()), mass(mass), radius(r), prevPos(pos - vel * 0.001f) {}

// Update function
void Body::update(float dt, void (*integrator)(Body&, float)) {
    // Call the integrator function
    integrator(*this, dt);
}
  



