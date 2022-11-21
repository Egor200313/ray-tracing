#pragma once
#include <SFML/System/Vector3.hpp>
#include "ray.hpp"
#include "../materials/material.hpp"
#include <optional>

class Shape {
  public:
    virtual std::optional<sf::Vector3f> hit(const Ray&) = 0;
    virtual Color getColor() = 0;
    virtual sf::Vector3f getNormal(sf::Vector3f) = 0;

    virtual bool operator==(const Shape& s) const = 0;

    virtual bool isPlane() = 0;

    virtual Material getMaterial() = 0;
};