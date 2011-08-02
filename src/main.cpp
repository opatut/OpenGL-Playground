#include "Color.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Util.hpp"

#include <SFML/Window.hpp>

#include <noise/noise.h>

#include <cmath>
#include <iostream>


float total_time = 0;
noise::module::Perlin perlin;

Color noiseGenerator(float x, float y) {
    float v = perlin.GetValue(x, y, total_time * 0.1) * 100 + 120;
    util::Clamp(v, 100.f, 120.f);
    util::LinearScale(v, 100.f, 120.f, 0.f, 255.f);
    return Color(v,v,v);
}

int main() {
    sf::Window window(sf::VideoMode(800, 600, 32), "Test");
    sf::Clock clock;

    if(!util::InitGlew()) {
        window.Close();
        return 1;
    }

    perlin.SetOctaveCount(3);
    perlin.SetFrequency(2);
    perlin.SetPersistence(0.8);

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

    int size = 256;

    Texture tex(size, size);
    tex.Generate(&noiseGenerator);
    glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // load test shader
    /*
    Shader shader(Shader::TYPE_FRAGMENT, "test.glsl", true);
    Program program;
    program.AddShader(shader);
    program.Activate();
    */

    bool running = true;
    while(running) {
        float frame_time = clock.GetElapsedTime() / 1000.f;
        clock.Reset();
        total_time += frame_time;

        tex.Generate(&noiseGenerator);

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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -2);
        //glRotatef(total_time * 45, 0, 1, 0);

        glBegin(GL_QUADS);
            glTexCoord2f(0.f,0.0f);
            glVertex3f(-1.f,  1.f, 0);

            glTexCoord2f(1.0f,0.0f);
            glVertex3f( 1.f,  1.f, 0);

            glTexCoord2f(1.0f,1.f);
            glVertex3f( 1.f, -1.f, 0);

            glTexCoord2f(0.f, 1.f);
            glVertex3f(-1.f, -1.f, 0);
        glEnd();

        window.Display();
    }


}
