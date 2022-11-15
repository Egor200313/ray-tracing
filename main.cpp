#include <iostream>
#include <cmath>
#include <optional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>


#include "shapes/plane.hpp"
#include "shapes/sphere.hpp"
#include "tracer/tracer.hpp"

// want to include only tracer and scene

namespace material{
    Material BRONZE = Material({0.2125, 0.1275, 0.054}, {0.714, 0.4284, 0.181}, {0.3935, 0.2719, 0.1667}, 25);
    Material CHROME = Material({0.25, 0.25, 0.25}, {0.4, 0.4, 0.4}, {0.774597, 0.774597, 0.774597}, 76);
    Material GOLD = Material({0.24725, 0.1995, 0.0745}, {0.75164, 0.60648, 0.22648}, {0.628281, 0.555802, 0.366065}, 51);
    Material OBSIDIAN = Material({0.05375, 0.05, 0.06625}, {0.18275, 0.17, 0.22525}, {0.332741, 0.328634, 0.346435}, 38);
    Material PLASTIC = Material({1.0, 1.0, 1.0}, {0.4, 0.4, 0.4}, {0.5, 0.5, 0.5}, 32);
}



int main() {
    const int WINDOW_WIDTH = 1080;
    const int WINDOW_HEIGHT = 720;

    sf::Texture texture;
    if (!texture.create(WINDOW_WIDTH, WINDOW_HEIGHT)) std::cout << "Error while creating texture!\n";

    sf::Uint8* pixels = new sf::Uint8[WINDOW_WIDTH * WINDOW_HEIGHT * 4];

    //////////////////////// Scene construction start ////////////////////////
    Scene scene;
    const float xCamera = WINDOW_WIDTH / 2;
    const float yCamera = 300;
    const float distScreen = 500;

    scene.setCamera({-distScreen, xCamera - WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - yCamera});

    scene.addLight({-300.0, -60.0, 300.0});

    scene.setScreen(WINDOW_WIDTH, WINDOW_HEIGHT);

    Plane plane({0.0, 0.0, 1.0}, 0.0, Color(50, 50, 50));
    Sphere sp1(-100.0, 0.0, 80.0, 80.0, Color(255, 255, 255));
    Sphere sp2(-200.0, -80.0, 40.0, 40.0, Color(255, 255, 255));
    sp1.setMaterial(material::GOLD);
    plane.setMaterial(material::PLASTIC);
    std::vector<Shape*> shapes = {&plane, &sp1};
    
    scene.addObjects(shapes);
    //////////////////////// Scene construction end ////////////////////////

    Tracer tracer(&scene);

    auto t1 = std::chrono::high_resolution_clock::now();
    tracer.traceScene(pixels);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << ms_int.count() << "ms\n";
    
    texture.update(pixels);
    texture.copyToImage().saveToFile("../texture.png");

    delete[] pixels;

    return 0;
}



/*sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");
    window.setFramerateLimit(60);
   
    const float R = 50.f;
    sf::CircleShape shape(R);
    shape.setFillColor(sf::Color(100, 250, 50));
    sf::Vector2f position(300, 300);
    shape.setPosition(position);

    float xVelocity = 3;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (xVelocity > 0) {
            if (position.x < WINDOW_WIDTH - 2*R) position.x += xVelocity;
            else xVelocity *= -1;
        } else {
            if (position.x > 0) position.x += xVelocity;
            else xVelocity *= -1;
        }
        
        shape.setPosition(position);
        
        window.clear(sf::Color::White);
        window.draw(shape);
        window.display();
    }*/


    /*auto result = intersect(8.0, 2.0, 4.0, 2.0, 8.0, 2.0, 4.0);
    if (result.first.has_value()) std::cout << result.first.value().first << " " << result.first.value().second << std::endl;
    if (result.second.has_value()) std::cout << result.second.value().first << " " << result.second.value().second << std::endl;*/