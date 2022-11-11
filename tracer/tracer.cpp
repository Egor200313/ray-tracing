#include "tracer.hpp"
#include "../shapes/shape.hpp"
#include "../utils/utils.cpp"
#include <vector>
#include <SFML/Graphics.hpp>

std::pair<Shape*, sf::Vector3f> nearest_hit(const Ray& ray, std::vector<Shape*> shapes, Shape* except = nullptr){
    float min_dist = 100000.0;
    Shape* obj = nullptr;
    sf::Vector3f hit_point;
    for (auto shape: shapes) {
        if (except != nullptr && *shape == *except) continue;
        auto point = shape->hit(ray);
        if (point.has_value() && dist(ray.o, point.value()) < min_dist && dist(ray.o, point.value()) > 0.1) {
            min_dist = dist(ray.o, point.value());
            obj = shape;
            hit_point = point.value();
        }
    }
    return {obj, hit_point};
}

Ray Tracer::getRay(float x, float y) {
    sf::Vector3f screenDot (
        0.0,
        x - scene->getScreenWidth() / 2,
        scene->getScreenHeight() / 2 - y
    );
    return Ray(scene->getCamera(), normalize(screenDot - scene->getCamera()));
}


Color Tracer::handlePixel(int x, int y) {
    Ray ray = getRay(x, y);
    return trace(ray);
}

Color Tracer::getIllumination(sf::Vector3f point, Shape* shape){
    // Implementation of Phong shading
    Color ambient_intensity(100, 100, 100); // color

    Material material = shape->getMaterial();

    Color diffuse_intensity = material.diffuse_intensity;
    Color specular_intensity = material.specular_intensity;

    // material props
    float ambient_ratio = material.ambient_ratio;
    float diffuse_ratio = material.diffuse_ratio;
    float specular_ratio = material.specular_ratio;
    int shiness = material.shiness;

    sf::Vector3f N = shape->getNormal(point);
    sf::Vector3f V = normalize(scene->camera - point);
    sf::Vector3f L = normalize(scene->lights[0] - point);
    sf::Vector3f R = normalize(N * dot(L,N) * (2.0f) - L);

    return ambient_intensity*ambient_ratio + diffuse_intensity*diffuse_ratio*dot(L, N) + specular_intensity*specular_ratio*std::pow(fmax(0.0, dot(R, V)), shiness);
}

Color Tracer::trace(const Ray& ray) {
    auto first_hit_pair = nearest_hit(ray, scene->objects);
    Shape* hitted_shape = first_hit_pair.first;
    auto point = first_hit_pair.second;
    if (hitted_shape == nullptr) return Color(0, 0, 0);

    return getIllumination(point, hitted_shape);
}

void Tracer::traceScene(sf::Uint8* pixels) {
        Color color;
        for (int x = 0; x < scene->getScreenWidth(); ++x) {
            for (int y = 0; y < scene->getScreenHeight(); ++y) {
                int index = (y * scene->getScreenWidth() + x) * 4;
                color = handlePixel(x, y);
                pixels[index] = color.r;
                pixels[index+1] = color.g;
                pixels[index+2] = color.b;
                pixels[index+3] = color.a;
            }
        }
    }