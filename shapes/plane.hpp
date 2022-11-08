#include "shape.hpp"

class Plane: public Shape {
public:
    sf::Vector3f normal;
    float bias;
    Plane() = default;
    Plane(sf::Vector3f normal, float bias);

    std::optional<sf::Vector3f> hit(const Ray& ray) override;
    Color getColor() override;

    sf::Vector3f getNormal(sf::Vector3f) override;
    bool isPlane() override;

    bool operator==(const Shape& sh)const override;
};