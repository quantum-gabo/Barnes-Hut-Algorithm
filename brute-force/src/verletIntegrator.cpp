#include "verletIntegrator.h"

void verletIntegrator(Body& body, float dt) {
    // Store current position temporarily
    Vec2D tempPos = body.pos;
    
    body.pos = tempPos * 2 - body.prevPos + body.acc * dt * dt;
    
    body.prevPos = tempPos;
    
    body.vel = (body.pos - body.prevPos) / dt;
    
    body.acc = Vec2D::zero(); 
}

    
