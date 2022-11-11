#include <SFML/System/Vector3.hpp>

struct Ray{
    sf::Vector3f o;
    sf::Vector3f direct;
    Ray() = default;
    Ray(const sf::Vector3f& o, const sf::Vector3f& dir):o(o), direct(dir){}
    Ray(float x0, float y0, float z0, float v1, float v2, float v3): o({x0, y0, z0}), direct(sf::Vector3f({v1, v2, v3})){}
    Ray(const Ray& r) = default;
};