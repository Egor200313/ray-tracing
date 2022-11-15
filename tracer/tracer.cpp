#include "tracer.hpp"
#include "../shapes/shape.hpp"
#include "../utils/utils.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>

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

Tracer::Tracer(Scene* scene){
    this->scene = scene;
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
    //Color ambient_intensity(100, 100, 100); // color
    Color ambient_intensity = shape->getColor();

    Material material = shape->getMaterial();

    Color diffuse_intensity = material.diffuse_intensity;
    Color specular_intensity = material.specular_intensity;

    // material props
    sf::Vector3f k_a = material.ambient_ratio;
    sf::Vector3f k_d = material.diffuse_ratio;
    sf::Vector3f k_s = material.specular_ratio;
    int shiness = material.shiness;

    sf::Vector3f N = shape->getNormal(point);
    sf::Vector3f V = normalize(scene->camera - point);
    sf::Vector3f L = normalize(scene->lights[0] - point);
    sf::Vector3f R = normalize(N * dot(L,N) * (2.0f) - L);

    float diff_dot = fmax(0.0, dot(L, N));
    float pos_diff_dot = (diff_dot > 0.00000001 ? 1.0 : 0.0);

    return Color(
                fmin(255, ambient_intensity.r*k_a.x + diffuse_intensity.r*k_d.x*diff_dot + specular_intensity.r*k_s.x*pos_diff_dot*std::pow(fmax(0.0, dot(R, V)), shiness)),
                fmin(255, ambient_intensity.g*k_a.y + diffuse_intensity.g*k_d.y*diff_dot + specular_intensity.g*k_s.y*pos_diff_dot*std::pow(fmax(0.0, dot(R, V)), shiness)),
                fmin(255, ambient_intensity.b*k_a.z + diffuse_intensity.b*k_d.z*diff_dot + specular_intensity.b*k_s.z*pos_diff_dot*std::pow(fmax(0.0, dot(R, V)), shiness))
                );

}

Color Tracer::trace(const Ray& ray) {
    auto first_hit_pair = nearest_hit(ray, scene->objects);
    Shape* hitted_shape = first_hit_pair.first;
    auto point = first_hit_pair.second;
    if (hitted_shape == nullptr) return Color(0, 0, 0);

    Ray to_light = Ray(point, scene->lights[0] - point);
    auto intersect = nearest_hit(to_light, scene->objects, hitted_shape);
    if (intersect.first != nullptr) return Color(0,0,0);

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