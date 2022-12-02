#include "lightEmittor.hpp"

LightEmittor::LightEmittor(sf::Vector3f pos, Color a, Color d, Color s): 
position(pos), ambient_intensity(a), diffuse_intensity(d), specular_intensity(s){}