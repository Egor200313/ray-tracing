#include "material.hpp"

Material::Material(sf::Vector3f ambient, sf::Vector3f diffuse, sf::Vector3f specular, int shiness): 
ambient_ratio(ambient), diffuse_ratio(diffuse), specular_ratio(specular), shiness(shiness){}