#pragma once
#include <SFML/System/Vector3.hpp>
#include <vector>

class Triangle{
public:
    std::vector<sf::Vector3f>vertex;
    Triangle() = default;
    Triangle(const std::vector<sf::Vector3f>& vertex);
    bool contains(sf::Vector3f) const;

    bool operator==(const Triangle& other) const;
};