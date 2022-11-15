#include "shape.hpp"

class Plane: public Shape {
public:
    sf::Vector3f normal;
    float bias;
    Material mat;
    Color color;
    Plane() = default;
    Plane(sf::Vector3f normal, float bias, Color color = Color(100, 100, 100));

    std::optional<sf::Vector3f> hit(const Ray& ray) override;
    Color getColor() override;

    sf::Vector3f getNormal(sf::Vector3f) override;
    bool isPlane() override;

    bool operator==(const Shape& sh)const override;

    Material getMaterial() override;
    void setMaterial(Material m);
   
};