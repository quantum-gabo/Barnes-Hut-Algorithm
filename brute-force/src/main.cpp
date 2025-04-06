#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../include/vector2D.h"
#include "../include/Body.h"
#include "../include/verletIntegrator.h"
#include "../include/BruteForceSimulator.h"
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

    float dt = 0.0001f;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Generate random bodies
    std::vector<Body> bodies;
    for (int i = 0; i < 500; ++i) {
        float x = static_cast<float>(std::rand() % 800);
        float y = static_cast<float>(std::rand() % 600);
        //float vx = static_cast<float>(std::rand() % 100); // Random velocity between 0 and 100
        //float vy = static_cast<float>(std::rand() % 100); // Random velocity between 0 and 100
        float vx = 0.0f, vy = 0.0f;
        float mass = 500.0f + std::rand() % 1000;
        float r = 2.0f;
        bodies.push_back(Body(Vec2D(x, y), Vec2D(vx, vy), mass, r));
    }

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

        simulator.run(5);

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
