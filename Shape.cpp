#include <SFML/Graphics.hpp>
#include <optional>
#include <cmath>
#include <vector>


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