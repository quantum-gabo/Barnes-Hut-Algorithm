#include "BruteForceSimulator.h"
#include <cmath>
#include <algorithm> // For std::max
//doday
BruteForceSimulator::BruteForceSimulator(std::vector<Body>& bodies, float dt)
    : bodies(bodies), dt(dt) {
    // Initialize previous positions correctly for Verlet
    for (Body& body : bodies) {
        body.prevPos = body.pos - body.vel * dt; 
    }

}

void BruteForceSimulator::computeForces() {
    const float G = 1.0f;
    const float MIN = 0.05f;

    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {

            Vec2D r = bodies[j].pos - bodies[i].pos;
            float magSqr = r.magSqr(); 
            float mag = std::sqrt(magSqr);
            Vec2D temp = r / (std::max(magSqr, MIN)); // Avoid division by zero
            bodies[i].acc += temp * bodies[j].mass;
            bodies[j].acc -= temp * bodies[i].mass;
        }
    }
}

void BruteForceSimulator::update() {
    computeForces();
    for (Body& body : bodies) {
        body.update(dt, verletIntegrator);
    }
}

void BruteForceSimulator::run(int steps) {
    for (int i = 0; i < steps; ++i) {
        update();
    }
}
