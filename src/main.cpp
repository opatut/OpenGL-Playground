#include "Color.hpp"
#include "Mesh.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "TerrainMesh.hpp"
#include "Texture.hpp"
#include "Util.hpp"

#include <SFML/Window.hpp>

#include <noise/noise.h>

#include <cmath>
#include <cstring>
#include <iostream>

////////////////////////////////////////////////////////////////

void prepareNoise();
void prepareGraphics();
Color textureGenerator(float x, float y);
float heightmapGenerator(float x, float y);

////////////////////////////////////////////////////////////////

float total_time = 0;
int heightmap_size = 512;

sf::Window window;
sf::Clock frame_clock;

noise::module::Perlin simplePerlin;

noise::module::RidgedMulti mountainTerrain;
noise::module::Billow baseFlatTerrain;
noise::module::ScaleBias flatTerrain;
noise::module::Perlin terrainType;
noise::module::Select terrainSelector;
noise::module::Turbulence finalTerrain;

////////////////////////////////////////////////////////////////

void prepareNoise() {

    // -- terrain --
    baseFlatTerrain.SetFrequency (2.0);

    flatTerrain.SetSourceModule (0, baseFlatTerrain);
    flatTerrain.SetScale (0.125);
    flatTerrain.SetBias (-0.75);

    terrainType.SetFrequency (0.5);
    terrainType.SetPersistence (0.25);

    terrainSelector.SetSourceModule (0, flatTerrain);
    terrainSelector.SetSourceModule (1, mountainTerrain);
    terrainSelector.SetControlModule (terrainType);
    terrainSelector.SetBounds (0.0, 1000.0);
    terrainSelector.SetEdgeFalloff (0.125);

    finalTerrain.SetSourceModule (0, terrainSelector);
    finalTerrain.SetFrequency (4.0);
    finalTerrain.SetPower (0.125);

    // -- texture --
    simplePerlin.SetOctaveCount(3);
    simplePerlin.SetFrequency(2);
    simplePerlin.SetPersistence(0.8);
}

////////////////////////////////////////////////////////////////

void prepareGraphics() {
    // create window + render context
    window.Create(sf::VideoMode(800, 600, 32), "Test");

    // initialize GLEW
    if(!util::InitGlew()) {
        window.Close();
        exit(1);
    }


    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);     // Turn transparency on

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 800.f / 600.f, .1f, 100.f);
}

////////////////////////////////////////////////////////////////

float heightmapGenerator(float x, float y) {
    float h = finalTerrain.GetValue(x, y, 0);
    h = h * 0.5 + 0.5; // map to 0..1
    util::Clamp(h, 0.f, 1.f);
    return h;
}

////////////////////////////////////////////////////////////////

Color textureGenerator(float x, float y) {
    float h = simplePerlin.GetValue(x, y, 0);
    util::Clamp(h, -1.f, 1.f);
    util::LinearScale(h, -1.f, 1.f, 0.f, 255.f);
    return Color(h, h, h);
}

////////////////////////////////////////////////////////////////

int main() {
    std::cout << "=> Setting up graphics" << std::endl;
    prepareGraphics();

    std::cout << "=> Generating media" << std::endl;
    prepareNoise();

    Texture texture(heightmap_size, heightmap_size, false);
    texture.Generate(&textureGenerator);

    TerrainMesh terrain(texture, 256, 10, 2, 2);
    terrain.SetPosition(Vector3f(0, -3, -5));
    terrain.Generate(&heightmapGenerator);

    bool running = true;
    while(running) {
        float frame_time = frame_clock.GetElapsedTime() / 1000.f;
        frame_clock.Reset();
        total_time += frame_time;

        terrain.SetRotation(Quaternion(total_time * 20, 0, 1, 0));

        sf::Event event;
        while (window.PollEvent(event)) {
            if(event.Type == sf::Event::Closed)
                running = false;
            if (event.Type == sf::Event::Resized) {
                glViewport(0, 0, event.Size.Width, event.Size.Height);
                gluPerspective(90.0f, event.Size.Width * 1.0 / event.Size.Height, .1f, 100.f);
            }
        }

        window.SetActive();

        // clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);

        terrain.Render();

        window.Display();
    }


}
