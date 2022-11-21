#pragma once
#include "shape.hpp"
#include "triangle.hpp"

class Polyhedron: public Shape{
protected:
    std::vector<Triangle>edges;
    std::vector<sf::Vector3f>normals;
    Color color = Color(255, 255, 255);
    Material material;
public:
    Polyhedron() = default;
    Polyhedron(const std::vector<Triangle>& edges, const std::vector<sf::Vector3f>& normals);
    std::optional<sf::Vector3f> hit(const Ray&);
    Color getColor();
    sf::Vector3f getNormal(sf::Vector3f);

    bool operator==(const Shape& s) const;

    bool isPlane();

    Material getMaterial();
    void setMaterial(Material m);
    void setColor(Color c);
};