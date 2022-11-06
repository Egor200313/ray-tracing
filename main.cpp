#include <iostream>
#include <cmath>
#include <optional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Shape.cpp"

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

const float xCamera = WINDOW_WIDTH / 2;
const float yCamera = 300;
const float distScreen = 500;

sf::Vector3f camera = {-distScreen, xCamera - WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - yCamera};

sf::Vector3f light = {200.0, -400.0, 800.0};

const int light_power = 60;

// 3d ray from dot on the screen
Ray getRay(float x, float y) {
    sf::Vector3f screenDot;
    screenDot.x = 0;
    screenDot.y = x - WINDOW_WIDTH / 2;
    screenDot.z = WINDOW_HEIGHT / 2 - y;

    Ray result;
    result.o = camera;
    result.direct = screenDot - camera;
    return result;
}


sf::Vector3f plane_normal = {0.0, 0.0, 1.0};
Plane plane(plane_normal, 0.0);
Sphere sp1(-200.0, 0.0, 80.0, 80.0, Color(56, 123, 76));
Sphere sp2(-280.0, -60.0, 40.0, 40.0, Color(173, 34, 87));
std::vector<Shape*> shapes = {&plane, &sp1, &sp2};

Color handlePixel(int x, int y) {
    Ray ray = getRay(x, y);
    auto hitted_pair = nearest_hit(ray, shapes);
    Shape* hitted_shape = hitted_pair.first;
    auto point = hitted_pair.second;
    sf::Vector3i l = {light_power, light_power, 4*light_power};
    if (hitted_shape == nullptr) return Color(0, 0, 0);

    Ray to_light;
    to_light.o = point;
    to_light.direct = normalize(light - point);
    auto secondary_hit_pair = nearest_hit(to_light, shapes, hitted_shape);
    float intensity = dot(hitted_shape->getNormal(point), to_light.direct); // [-1, 1]
    sf::Vector3i reflected(light_power*intensity, light_power*intensity, light_power*intensity);
    if (secondary_hit_pair.first == nullptr) return hitted_shape->getColor() + reflected;

    point = secondary_hit_pair.second;
    float shade_intensity = dot(hitted_shape->getNormal(point), to_light.direct); // [-1, 1]
    sf::Vector3i shade(-light_power*shade_intensity, -light_power*shade_intensity, -light_power*shade_intensity);
    Color res = hitted_shape->getColor();
    return res + shade + reflected;
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