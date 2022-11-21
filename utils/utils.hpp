#pragma once
#include <SFML/System/Vector3.hpp>

float dot(const sf::Vector3f& v1, const sf::Vector3f& v2);

float dist(const sf::Vector3f& v1, const sf::Vector3f& v2);

sf::Vector3f normalize(sf::Vector3f v);

sf::Vector3f cross(sf::Vector3f v1, sf::Vector3f v2);