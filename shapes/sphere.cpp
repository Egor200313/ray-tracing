#include "sphere.hpp"

Sphere::Sphere(float x0, float y0, float z0, float R):center({x0, y0, z0}), R(R){
    clr = Color(0, 0, 0);
}
Sphere::Sphere(float x0, float y0, float z0, float R, Color c){
    center.x = x0;
    center.y = y0;
    center.z = z0;
    this->R = R;
    clr = c;
}
Sphere::Sphere(const Sphere& s) = default;

void Sphere::setColor(Color c) {
    clr = c;
}

bool Sphere::isPlane() override{
    return false;
}

std::optional<sf::Vector3f> Sphere::hit(const Ray& ray) override{
    sf::Vector3f diff = ray.o - center;
    float D = dot(diff, ray.direct)*dot(diff, ray.direct) - dot(ray.direct, ray.direct)*(dot(diff, diff)-R*R);
    if (D < 0) return std::nullopt;
    float alpha1 = (-dot(diff, ray.direct) + std::sqrt(D)) / dot(ray.direct, ray.direct);
    float alpha2 = (-dot(diff, ray.direct) - std::sqrt(D)) / dot(ray.direct, ray.direct);
    if (alpha1 > alpha2) std::swap(alpha1, alpha2);
    if (alpha1 < 0.0001 && alpha2 < 0.0001) return std::nullopt;
    if (alpha1 < 0.0001) return std::optional<sf::Vector3f>(ray.o + alpha2*ray.direct);
    return std::optional<sf::Vector3f>(ray.o + alpha1*ray.direct); // only the nearest hit point
}

Color Sphere::getColor() override {
    return clr;
}

sf::Vector3f Sphere::getNormal(sf::Vector3f point) override{
    return normalize(point - center);
}

bool Sphere::operator==(const Shape& sh)const override{
    const Sphere* tmp = dynamic_cast<const Sphere*>(&sh);
    if (tmp==NULL) return false;
    return tmp->R == R && tmp->center == center;
}