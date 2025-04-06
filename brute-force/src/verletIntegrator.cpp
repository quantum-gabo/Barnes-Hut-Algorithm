#include "verletIntegrator.h"

void verletIntegrator(Body& body, float dt) {
    // Store current position temporarily
    Vec2D tempPos = body.pos;
    
    // Calculate new position using the Verlet algorithm formula:
    // newPos = 2 * currentPos - prevPos + acceleration * dt^2
    body.pos = tempPos * 2 - body.prevPos + body.acc * dt * dt;
    
    // Update previous position for next iteration
    body.prevPos = tempPos;
    
    // Calculate velocity (optional, if needed elsewhere)
    body.vel = (body.pos - body.prevPos) / dt;
    
    // Note: acceleration is reset in the force computation function, not here
    // This allows proper accumulation of forces before integration
    body.acc = Vec2D::zero(); // Reset acceleration after updating position
}

    
