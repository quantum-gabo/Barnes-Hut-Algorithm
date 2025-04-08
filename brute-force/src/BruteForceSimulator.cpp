#include "BruteForceSimulator.h"
#include <cmath>
#include <algorithm> // For std::max
#include <iostream> // For debugging
//doday
BruteForceSimulator::BruteForceSimulator(std::vector<Body>& bodies, float dt)
    : bodies(bodies), dt(dt) {
    // Initialize previous positions correctly for Verlet
    // Compute the acceleration for each body for the first time
    computeForces();
    for (Body& body : bodies) {
        Vec2D temp = body.pos;
        body.pos = body.pos + body.vel * dt + body.acc * (dt * dt) / 2;
        body.prevPos = temp;
        body.acc = Vec2D::zero(); // Reset acceleration after updating position
    }
}

void BruteForceSimulator::computeForces() {
    const float G = 1.0f;
    const float MIN = 0.001f;

    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {

            Vec2D r = bodies[j].pos - bodies[i].pos;

            float magSqr = r.magSqr(); 
            float mag = std::sqrt(magSqr);
            Vec2D force = r*(1) / std::pow(mag + (MIN * MIN), 1.5); 
            bodies[i].acc += force * bodies[j].mass;
            bodies[j].acc -= force * bodies[i].mass;
        }
    }
}

// void BruteForceSimulator::computeForces() {
//     const float G = 1.0f;
//     const float MIN = 0.001f;
    
//     // Reset accelerations
//     for (Body& body : bodies) {
//         body.acc = Vec2D::zero();
//     }
    
//     std::cout << "Starting force calculation..." << std::endl;
    
//     for (size_t i = 0; i < bodies.size(); ++i) {
//         for (size_t j = i + 1; j < bodies.size(); ++j) {
//             Vec2D r = bodies[j].pos - bodies[i].pos;
//             float distSqr = r.magSqr();
//             float dist = std::sqrt(distSqr);
            
//             if (dist < 1e-10) continue; // Skip if too close
            
//             // Print distance between bodies
//             std::cout << "Distance between bodies " << i << " and " << j << ": " << dist << std::endl;
            
//             float forceMag = G * bodies[i].mass * bodies[j].mass / (distSqr + MIN * MIN);
//             Vec2D dir = r / dist;
            
//             // Print force magnitude
//             std::cout << "Force magnitude: " << forceMag << std::endl;
            
//             // Apply acceleration
//             Vec2D accI = dir * (forceMag / bodies[i].mass);
//             Vec2D accJ = dir * (-forceMag / bodies[j].mass);
            
//             bodies[i].acc += accI;
//             bodies[j].acc += accJ;
            
//             // Print resulting accelerations
//             std::cout << "Body " << i << " acc: (" << bodies[i].acc.x << ", " << bodies[i].acc.y << ")" << std::endl;
//             std::cout << "Body " << j << " acc: (" << bodies[j].acc.x << ", " << bodies[j].acc.y << ")" << std::endl;
//         }
//     }
// }

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
