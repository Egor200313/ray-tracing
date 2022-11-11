#include "../color/color.hpp"

struct Material{
    Color diffuse_intensity = Color(200, 200, 200);
    Color specular_intensity = Color(255, 255, 255);

    float ambient_ratio = 0.7f;
    float diffuse_ratio = 0.5f;
    float specular_ratio = 0.5f;
    float shiness = 20;

    Material& operator=(const Material& other) = default;
    Material() = default;
};

const Material cmat = Material();