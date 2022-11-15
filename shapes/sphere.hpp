#include "shape.hpp"

class Sphere: public Shape {
  public:
    sf::Vector3f center;
    float R;
    Color clr;
    Material mat;
    Sphere() = default;
    Sphere(float x0, float y0, float z0, float R);
    Sphere(float x0, float y0, float z0, float R, Color c);
    Sphere(const Sphere& s) = default;

    void setColor(Color c);
    void setMaterial(Material);

    bool isPlane() override;
    std::optional<sf::Vector3f> hit(const Ray& ray) override;
    Color getColor() override ;
    sf::Vector3f getNormal(sf::Vector3f point) override;
    Material getMaterial() override;

    bool operator==(const Shape& sh)const override;
};