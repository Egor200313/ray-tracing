#include "tracer.hpp"
#include "../shapes/shape.hpp"
#include "../utils/utils.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <thread>

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
    return trace(ray, 3);
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

sf::Vector3f Tracer::refracted_dir(const Ray& ray, sf::Vector3f normal, float n2) { // it works correctly
    float n1 = ray.refraction_value;
    normal = normalize(normal);
    sf::Vector3f norm_dir = normalize(ray.direct);
    float cos = -dot(norm_dir, normal);
    float nr = n1 / n2;
    return nr*norm_dir + static_cast<float>(nr*cos - std::sqrt(1.0 - nr*nr*(1.0-cos*cos)))*normal;
}

Color Tracer::trace(const Ray& ray, int depth) {
    auto first_hit_pair = nearest_hit(ray, scene->objects);
    Shape* hitted_shape = first_hit_pair.first;
    auto point = first_hit_pair.second;
    if (hitted_shape == nullptr) return Color(0, 0, 0);

    Color local_color;
    Ray to_light = Ray(point, scene->lights[0] - point);
    auto intersect = nearest_hit(to_light, scene->objects, hitted_shape);
    if (intersect.first != nullptr) local_color = Color(0,0,0);
    
    else local_color = getIllumination(point, hitted_shape);

    float r = hitted_shape->getMaterial().reflect_ratio;
    sf::Vector3f N = hitted_shape->getNormal(point);

    float n_new = hitted_shape->getMaterial().refract_ratio;
    float n_cur = ray.refraction_value;
    
    if (n_new != 1.0){
        sf::Vector3f refracted = refracted_dir(ray, N, n_new);
        
        Ray new_ray = Ray(point, refracted, n_new);
        
        auto exit = nearest_hit(new_ray, scene->objects);
        if (exit.first == nullptr) { 
            return local_color;
        }
        auto exit_point = exit.second;
        sf::Vector3f exitN = hitted_shape->getNormal(exit_point);
        refracted = refracted_dir(new_ray, -exitN, 1.0);
        
        Ray out(exit_point, refracted, 1.0);
        local_color = local_color * 0.8 + trace(out, depth);
    }


    if (depth <= 0 || r <= 0.0) {
        return local_color;
    }
    
    

    
    sf::Vector3f reflected = N * dot(N,ray.direct) * (-2.0f) + ray.direct;
    Ray reflected_ray = Ray(point, reflected);

    return local_color * (1 - r) + trace(reflected_ray, depth - 1) * r;
}

void Tracer::traceScene(sf::Uint8* pixels) {

    auto partial_trace = [pixels, this](int x_start, int y_start){
        Color color;
        for (int x = x_start; x < scene->getScreenWidth(); x+=2) {
            for (int y = y_start; y < scene->getScreenHeight(); y+=2) {
                int index = (y * scene->getScreenWidth() + x) * 4;
                color = handlePixel(x, y);
                pixels[index] = color.r;
                pixels[index+1] = color.g;
                pixels[index+2] = color.b;
                pixels[index+3] = color.a;
            }
        }
    };

    std::thread t1(partial_trace, 0, 0);
    std::thread t2(partial_trace, 1, 0);
    std::thread t3(partial_trace, 0, 1);
    std::thread t4(partial_trace, 1, 1);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}