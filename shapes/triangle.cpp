#include "triangle.hpp"
#include "../utils/utils.hpp"
#include <cmath>

Triangle::Triangle(const std::vector<sf::Vector3f>& vertex): vertex(vertex){}

bool sameSide(sf::Vector3f p1, sf::Vector3f p2, sf::Vector3f a, sf::Vector3f b){
    sf::Vector3f cp1 = cross(b - a, p1 - a);
    sf::Vector3f cp2 = cross(b - a, p2 - a);
    if (dot(cp1, cp2) > 0.0000001) return true;
    return false;
}


bool Triangle::contains(sf::Vector3f point) const {
    sf::Vector3f area_v = cross(vertex[0] - vertex[1], vertex[2] - vertex[1]);
    float full_area = std::sqrt(dot(area_v, area_v));

    float predicted = 0;
    area_v = cross(vertex[1] - vertex[0], point - vertex[0]);
    predicted += std::sqrt(dot(area_v, area_v));

    area_v = cross(vertex[2] - vertex[1], point - vertex[1]);
    predicted += std::sqrt(dot(area_v, area_v));

    area_v = cross(vertex[0] - vertex[2], point - vertex[2]);
    predicted += std::sqrt(dot(area_v, area_v));
    
    if (predicted - full_area < 0.01) return true;
    return false;
    //return sameSide(point, vertex[0], vertex[1], vertex[2]) && sameSide(point, vertex[1], vertex[0], vertex[2]) && sameSide(point, vertex[2], vertex[1], vertex[0]);
}

bool Triangle::operator==(const Triangle& other) const{
    return other.vertex == vertex;
}