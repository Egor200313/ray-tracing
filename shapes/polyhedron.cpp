#include "polyhedron.hpp"
#include "plane.hpp"
#include "../utils/utils.hpp"
#include <optional>

Plane makePlane(Triangle tri){
    sf::Vector3f normal = cross(tri.vertex[1] - tri.vertex[0], tri.vertex[2] - tri.vertex[0]);
    float bias = dot(normal, tri.vertex[0]);
    return Plane(normal, -bias);
}

Polyhedron::Polyhedron(const std::vector<Triangle>& edges, const std::vector<sf::Vector3f>& normals): edges(edges), normals(normals){}

std::optional<sf::Vector3f> Polyhedron::hit(const Ray& ray){
    sf::Vector3f normalized_dir = normalize(ray.direct);
    sf::Vector3f best_point;
    float min_dist = 100000;
    bool found = false;
    for (int i = 0; i < edges.size(); ++i){
        Plane pl = makePlane(edges[i]);
        auto hit_obj = pl.hit(ray);
        if (hit_obj.has_value() && edges[i].contains(hit_obj.value()) && min_dist > dist(hit_obj.value(), ray.o)) {
            min_dist = dist(hit_obj.value(), ray.o);
            best_point = hit_obj.value();
            found = true;
        }
    }
    if (!found) return std::nullopt;
    return best_point;
}

Color Polyhedron::getColor(){
    return color;
}

sf::Vector3f Polyhedron::getNormal(sf::Vector3f point){
    for (int i = 0; i < edges.size(); ++i){
        if (edges[i].contains(point)) {
            return normals[i];
        }
    }
    throw 1;
}

bool Polyhedron::operator==(const Shape& sh) const{
    const Polyhedron* tmp = dynamic_cast<const Polyhedron*>(&sh);
    if (tmp==NULL) return false;
    return tmp->edges == edges;
}

bool Polyhedron::isPlane(){
    return false;
}

Material Polyhedron::getMaterial(){
    return material;
}

void Polyhedron::setMaterial(Material m){
    this->material = m;
}

void Polyhedron::setColor(Color c){
    this->color = c;
}