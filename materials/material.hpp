#include "../color/color.hpp"

struct Material{
    sf::Vector3f ambient_ratio = {0.2125, 0.1275, 0.054};
    sf::Vector3f diffuse_ratio = {0.714, 0.4284, 0.181};
    sf::Vector3f specular_ratio = {0.3935, 0.2719, 0.1667};
    int shiness = 25;

    float reflect_ratio = -1.0;
    float refract_ratio = 1.0;

    Material& operator=(const Material& other) = default;
    Material() = default;
    Material(sf::Vector3f, sf::Vector3f, sf::Vector3f, int);
    Material(sf::Vector3f, sf::Vector3f, sf::Vector3f, int, float);
    Material(sf::Vector3f, sf::Vector3f, sf::Vector3f, int, float, float);
};