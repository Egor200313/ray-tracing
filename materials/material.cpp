#include "material.hpp"

Material::Material(sf::Vector3f ambient, sf::Vector3f diffuse, sf::Vector3f specular, int shiness): 
ambient_ratio(ambient), diffuse_ratio(diffuse), specular_ratio(specular), shiness(shiness){}

Material::Material(sf::Vector3f ambient, sf::Vector3f diffuse, sf::Vector3f specular, int shiness, float reflect_ratio): 
ambient_ratio(ambient), diffuse_ratio(diffuse), specular_ratio(specular), shiness(shiness), reflect_ratio(reflect_ratio){}

Material::Material(sf::Vector3f ambient, sf::Vector3f diffuse, sf::Vector3f specular, int shiness, float reflect_ratio, float ref): 
ambient_ratio(ambient), diffuse_ratio(diffuse), specular_ratio(specular), shiness(shiness), reflect_ratio(reflect_ratio), refract_ratio(ref){}