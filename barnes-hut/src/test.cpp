#include <iostream>
#include "../include/vector2D.h"
#include "../include/Body.h"
#include "../include/verletIntegrator.h"
#include "../include/BruteForceSimulator.h"

int main() {
    float dt = 0.01f; // Time step

    // Create two test bodies
    std::vector<Body> bodies;
    bodies.push_back(Body(Vec2D(100.0f, 300.0f), Vec2D(5.0f, 0.0f), 10.0f, 5.0f));
    bodies.push_back(Body(Vec2D(400.0f, 300.0f), Vec2D(-5.0f, 0.0f), 10.0f, 5.0f));

    // Initialize prevPos correctly
    for (auto& body : bodies) {
        body.prevPos = body.pos - body.vel * dt;
    }

    BruteForceSimulator simulator(bodies, dt);

    // Run for 10 steps
    for (int step = 0; step < 10; ++step) {
        std::cout << "Step " << step << ":\n";
        for (size_t i = 0; i < bodies.size(); ++i) {
            std::cout << " Body " << i << " Position: (" << bodies[i].pos.x << ", " << bodies[i].pos.y << ")\n";
        }
        simulator.run(1);
    }

    return 0;
}
