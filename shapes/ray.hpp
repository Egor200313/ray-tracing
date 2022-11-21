#include <SFML/System/Vector3.hpp>

struct Ray{
    sf::Vector3f o;
    sf::Vector3f direct;
    float refraction_value = 1;
    Ray() = default;
    Ray(const sf::Vector3f& o, const sf::Vector3f& dir):o(o), direct(dir){}
    Ray(const sf::Vector3f& o, const sf::Vector3f& dir, float ref):o(o), direct(dir), refraction_value(ref){}
    Ray(float x0, float y0, float z0, float v1, float v2, float v3): o({x0, y0, z0}), direct(sf::Vector3f({v1, v2, v3})){}
    Ray(const Ray& r) = default;
};