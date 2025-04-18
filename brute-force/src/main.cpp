#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../include/vector2D.h"
#include "../include/Body.h"
#include "../include/verletIntegrator.h"
#include "../include/BruteForceSimulator.h"
#include <gif_lib.h> // Include giflib
#include <vector>
#include <cstdlib> // For random number generation
#include <ctime>   // For time-based seed
#include <algorithm> // For std::clamp


// Function to draw a circle in SDL
void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    filledCircleRGBA(renderer, centerX, centerY, radius, 255, 255, 255, 255);
}

// Zoom & Camera variables
float zoom = 1.0f;
Vec2D cameraOffset(0, 0);
bool isDragging = false;
Vec2D dragStart(0, 0);

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("N-Body Simulation", 
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    float dt = 0.001f;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Generate random bodies
    std::vector<Body> bodies;
    Vec2D center(400.0f, 300.0f); // Center of the screen
    float centralMass = 50000.0f;

    // Central body (massive, will stay nearly fixed due to its mass)
    bodies.push_back(Body(center, Vec2D(0, 0), centralMass, 4.0f));

    // Create circular orbiting bodies
    int numOrbitingBodies = 500;
    float G = 1.0f;

    for (int i = 0; i < numOrbitingBodies; ++i) {
        float angle = 2 * M_PI * i / numOrbitingBodies;
        float radius = 80.0f + static_cast<float>(rand() % 100); // Between 80 and 230

        // Position on the circle
        Vec2D offset(std::cos(angle), std::sin(angle));
        Vec2D pos = center + offset * radius;

        // Tangential velocity direction (perpendicular to position vector)
        Vec2D tangential(-offset.y, offset.x);

        // Calculate orbital speed for circular orbit
        float speed = std::sqrt(G * centralMass / radius);
        Vec2D vel = tangential * speed;

        bodies.push_back(Body(pos, vel, 1.0f, 1.0f));
    }


// Generate bodies for the two clusters

    
    
    

    BruteForceSimulator simulator(bodies, dt);

    // Main loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEWHEEL: {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    float worldX = (mouseX - cameraOffset.x) / zoom;
                    float worldY = (mouseY - cameraOffset.y) / zoom;

                    zoom *= (event.wheel.y > 0) ? 1.1f : 0.9f;
                    zoom = std::clamp(zoom, 0.1f, 10.0f);

                    cameraOffset.x = mouseX - worldX * zoom;
                    cameraOffset.y = mouseY - worldY * zoom;
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        isDragging = true;
                        dragStart.x = event.button.x;
                        dragStart.y = event.button.y;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        isDragging = false;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (isDragging) {
                        cameraOffset.x += event.motion.xrel;
                        cameraOffset.y += event.motion.yrel;
                    }
                    break;
            }
        }

        simulator.run(1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw bodies with zoom and camera offset
        for (const auto& body : bodies) {
            int screenX = static_cast<int>((body.pos.x * zoom) + cameraOffset.x);
            int screenY = static_cast<int>((body.pos.y * zoom) + cameraOffset.y);
            int screenRadius = static_cast<int>(body.radius * zoom);
            DrawCircle(renderer, screenX, screenY, screenRadius);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
