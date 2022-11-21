#include "plane.hpp"
#include "../utils/utils.hpp"

Plane::Plane(sf::Vector3f normal, float bias, Color color): normal(normal), bias(bias), color(color){}

std::optional<sf::Vector3f> Plane::hit(const Ray& ray){
    float alpha = (-bias - dot(normal, ray.o)) / dot(normal, ray.direct);
    if (alpha < 0.0) return std::nullopt;
    return std::optional<sf::Vector3f>(ray.o + alpha*ray.direct);
}

Color Plane::getColor() {
    return color;
}

sf::Vector3f Plane::getNormal(sf::Vector3f) {
    return normal;
}

bool Plane::isPlane() {
    return true;
}

bool Plane::operator==(const Shape& sh)const {
    const Plane* tmp = dynamic_cast<const Plane*>(&sh);
    if (tmp==NULL) return false;
    return tmp->bias == bias && tmp->normal == normal;
}

Material Plane::getMaterial(){
    return this->mat;
}

void Plane::setMaterial(Material m){
    this->mat = m;
}