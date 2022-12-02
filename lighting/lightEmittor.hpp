#pragma once
#include <SFML/System/Vector3.hpp>
#include "../color/color.hpp"

class LightEmittor{
public:
    sf::Vector3f position;
    Color ambient_intensity;
    Color diffuse_intensity;
    Color specular_intensity;
    LightEmittor(sf::Vector3f, Color, Color, Color);
};