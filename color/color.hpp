#pragma once
#include <SFML/System/Vector3.hpp>

struct Color{
    int r, g, b;
    int a = 255;
    Color() = default;
    Color(int r, int g, int b, int a): r(r), g(g), b(b), a(a){}
    Color(int r, int g, int b): r(r), g(g), b(b){}
    Color(const Color& c) = default;

    Color operator+ (const sf::Vector3i&);
    Color operator* (const float&);
};

Color operator+ (const Color& c1, const Color& c2);