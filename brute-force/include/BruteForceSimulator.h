#pragma once

#include <vector>
#include "Body.h"
#include "vector2D.h"
#include "verletIntegrator.h"

class BruteForceSimulator {
    public:

        BruteForceSimulator(std::vector<Body>& bodies, float dt);
        void update();
        void run(int steps);

    private:
        std::vector<Body>& bodies;
        float dt;
        void computeForces();
};
