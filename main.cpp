#include <iostream>
#include <cmath>
#include <optional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>


#include "shapes/plane.hpp"
#include "shapes/sphere.hpp"
#include "shapes/polyhedron.hpp"
#include "tracer/tracer.hpp"
#include "utils/utils.hpp"
#include "shapes/cube.hpp"

// want to include only tracer and scene

int index(int x, int y, int width){
    return (y * width + x) * 4;
}

void blur(sf::Uint8* pixels, int width, int height) {
    for (int x = 1; x < width - 1; ++x){
        for (int y = 1; y < height - 1; ++y){
            int indexx = (y * width + x) * 4;
            pixels[indexx] = (pixels[index(x + 1, y, width)] + pixels[index(x - 1, y, width)] + pixels[index(x, y + 1, width)] + pixels[index(x, y - 1, width)]) / 4;
            pixels[indexx+1] = (pixels[index(x + 1, y, width) + 1] + pixels[index(x - 1, y, width)+1] + pixels[index(x, y + 1, width)+1] + pixels[index(x, y - 1, width)+1]) / 4;
            pixels[indexx+2] = (pixels[index(x + 1, y, width)+2] + pixels[index(x - 1, y, width)+2] + pixels[index(x, y + 1, width)+2] + pixels[index(x, y - 1, width)+2]) / 4;
            pixels[indexx+3] = (pixels[index(x + 1, y, width)+3] + pixels[index(x - 1, y, width)+3] + pixels[index(x, y + 1, width)+3] + pixels[index(x, y - 1, width)+3]) / 4;
        }
    }
}

namespace material{
    Material BRONZE = Material({0.2125, 0.1275, 0.054}, {0.714, 0.4284, 0.181}, {0.3935, 0.2719, 0.1667}, 25, 0.3);
    Material CHROME = Material({0.25, 0.25, 0.25}, {0.4, 0.4, 0.4}, {0.774597, 0.774597, 0.774597}, 76);
    Material GOLD = Material({0.24725, 0.1995, 0.0745}, {0.75164, 0.60648, 0.22648}, {0.628281, 0.555802, 0.366065}, 51, 0.4);
    Material OBSIDIAN = Material({0.05375, 0.05, 0.06625}, {0.18275, 0.17, 0.22525}, {0.332741, 0.328634, 0.346435}, 38);
    Material PLASTIC = Material({1.0, 1.0, 1.0}, {0.4, 0.4, 0.4}, {0.5, 0.5, 0.5}, 32);
    Material MIRROR = Material({1.0, 1.0, 1.0}, {0.4, 0.4, 0.4}, {0.5, 0.5, 0.5}, 32, 0.8);
    Material GLASS = Material({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, 15, -0.8, 1.5);
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

    scene.addLight({-300.0, -120.0, 800.0});

    scene.setScreen(WINDOW_WIDTH, WINDOW_HEIGHT);

    Plane plane({0.0, 0.0, 1.0}, 0.0, Color(50, 50, 50));
    Sphere sp1(-200.0, 0.0, 50.0, 50.0, Color(255, 255, 255));
    Sphere sp2(300.0, -100.0, 200.0, 200.0, Color(255, 255, 255));
    sp1.setMaterial(material::GLASS);
    sp2.setMaterial(material::BRONZE);
    plane.setMaterial(material::MIRROR);

    //Cube cube({-100.0, -300.0, 0.0}, 200);
    //cube.setMaterial(material::OBSIDIAN);

    std::vector<Shape*> shapes = {&plane, &sp1, &sp2};
    scene.addObjects(shapes);
    //////////////////////// Scene construction end ////////////////////////

    Tracer tracer(&scene);

    auto t1 = std::chrono::high_resolution_clock::now();
    tracer.traceScene(pixels);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << ms_int.count() << "ms\n";
    blur(pixels, WINDOW_WIDTH, WINDOW_HEIGHT);
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

     /*sf::Vector3f p1 = {-150.0, -150.0, 0.0};
    sf::Vector3f p2 = {-200.0, 0.0, 100.0};
    sf::Vector3f p3 = {-220.0, 10.0, 40.0};
    sf::Vector3f p4 = {-120.0, 50.0, 0.0};

    Triangle v1({p1,p2,p3});
    Triangle v2({p1,p2,p4});
    Triangle v3({p2,p4,p3});
    Triangle v4({p1,p4,p3});

    std::vector<sf::Vector3f>normals = {
        normalize(-cross(p2-p3, p1-p3)),
        normalize(cross(p1-p4, p2-p4)),
        normalize(cross(p4-p3, p2-p3)),
        normalize({0.0, 0.0, -1.0})
    };

    Polyhedron poly(std::vector<Triangle>({v1, v2, v3, v4}), normals);
    poly.setMaterial(material::GOLD);*/