#include <iostream>
#include <cmath>
#include <optional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "tracer/tracer.hpp"
#include "shapes/plane.hpp"
#include "shapes/sphere.hpp"

// want to include only tracer and scene


int main() {
    const int WINDOW_WIDTH = 1080;
    const int WINDOW_HEIGHT = 720;

    sf::Texture texture;
    if (!texture.create(WINDOW_WIDTH, WINDOW_HEIGHT)) std::cout << "Error while creating texture!\n";

    sf::Uint8* pixels = new sf::Uint8[WINDOW_WIDTH * WINDOW_HEIGHT * 4];
    Scene scene;
    const float xCamera = WINDOW_WIDTH / 2;
    const float yCamera = 300;
    const float distScreen = 500;

    scene.setCamera({-distScreen, xCamera - WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - yCamera});

    scene.addLight({200.0, -400.0, 800.0});

    scene.setScreen(WINDOW_WIDTH, WINDOW_HEIGHT);

    Plane plane({0.0, 0.0, 1.0}, 0.0);
    Sphere sp1(-100.0, 0.0, 80.0, 80.0, Color(56, 123, 76));
    Sphere sp2(-200.0, -80.0, 40.0, 40.0, Color(173, 34, 87));
    std::vector<Shape*> shapes = {&plane, &sp1, &sp2};
    
    scene.addObjects(shapes);
    // scene construction

    Tracer tracer(&scene);
    tracer.traceScene(pixels);
    
    texture.update(pixels);
    texture.copyToImage().saveToFile("texture.png");

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