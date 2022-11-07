#include <iostream>
#include <cmath>
#include <optional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Shape.cpp"
#include "config.cpp"
#include "trace.cpp"


// 3d ray from dot on the screen
Ray getRay(float x, float y) {
    sf::Vector3f screenDot (
        0.0,
        x - WINDOW_WIDTH / 2,
        WINDOW_HEIGHT / 2 - y
    );
    return Ray(camera, normalize(screenDot - camera));
}


Color handlePixel(int x, int y) {
    Ray ray = getRay(x, y);
    return trace(ray);
}

int main() {
    sf::Texture texture;
    if (!texture.create(WINDOW_WIDTH, WINDOW_HEIGHT)) std::cout << "Error while creating texture!\n";

    sf::Uint8* pixels = new sf::Uint8[WINDOW_WIDTH * WINDOW_HEIGHT * 4];

    Color color;
    for (int x = 0; x < WINDOW_WIDTH; ++x) {
        for (int y = 0; y < WINDOW_HEIGHT; ++y) {
            int index = (y*WINDOW_WIDTH + x) * 4;
            color = handlePixel(x, y);
            pixels[index] = color.r;
            pixels[index+1] = color.g;
            pixels[index+2] = color.b;
            pixels[index+3] = color.a;
        }
    }
    
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