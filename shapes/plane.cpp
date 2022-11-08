#include "plane.hpp"

Plane::Plane(sf::Vector3f normal, float bias): normal(normal), bias(bias){}

std::optional<sf::Vector3f> Plane::hit(const Ray& ray) override{
    float alpha = (-bias - dot(normal, ray.o)) / dot(normal, ray.direct);
    if (alpha < 0.0) return std::nullopt;
    return std::optional<sf::Vector3f>(ray.o + alpha*ray.direct);
}

Color Plane::getColor() override{
    return Color(100, 100, 100);
}

sf::Vector3f Plane::getNormal(sf::Vector3f) override{
    return normal;
}

bool Plane::isPlane() override{
    return true;
}

bool Plane::operator==(const Shape& sh)const override{
    const Plane* tmp = dynamic_cast<const Plane*>(&sh);
    if (tmp==NULL) return false;
    return tmp->bias == bias && tmp->normal == normal;
}