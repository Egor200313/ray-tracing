#include <cmath>
#include <SFML/System/Vector3.hpp>

float dot(const sf::Vector3f& v1, const sf::Vector3f& v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

float dist(const sf::Vector3f& v1, const sf::Vector3f& v2) {
    sf::Vector3f diff = v1 - v2;
    return std::sqrt(dot(diff, diff));
}

sf::Vector3f normalize(sf::Vector3f v){
    float len = std::sqrt(dot(v, v));
    return v / len;
}

sf::Vector3f cross(sf::Vector3f v1, sf::Vector3f v2){
    return sf::Vector3f{v1.y*v2.z - v1.z*v2.y, v1.z*v2.x-v1.x*v2.z, v1.x*v2.y-v1.y*v2.x};
}