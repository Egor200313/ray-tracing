#include "tracer.hpp"

Color getIllumination(sf::Vector3f point, Shape* shape, const Scene& scene){
    // Implementation of Phong shading
    Color ambient_intensity(100, 100, 100); // color

    Color diffuse_intensity(200, 200, 200); // shades on object
    Color specular_intensity(255, 255, 255); // blicks

    // material props
    float ambient_ratio = 0.7f;
    float diffuse_ratio = 0.5f;
    float specular_ratio = 0.5f;
    int shiness = 20;

    sf::Vector3f N = shape->getNormal(point);
    sf::Vector3f V = normalize(scene.camera - point);
    sf::Vector3f L = normalize(scene.light - point);
    sf::Vector3f R = normalize(N * dot(L,N) * (2.0f) - L);

    return ambient_intensity*ambient_ratio + diffuse_intensity*diffuse_ratio*dot(L, N) + specular_intensity*specular_ratio*std::pow(fmax(0.0, dot(R, V)), shiness);
}

Color trace(const Ray& ray, const Scene& scene) {
    auto first_hit_pair = nearest_hit(ray, scene.shapes);
    Shape* hitted_shape = first_hit_pair.first;
    auto point = first_hit_pair.second;
    if (hitted_shape == nullptr) return Color(0, 0, 0);

    return getIllumination(point, hitted_shape);

    /*Color res = hitted_shape->getColor();
    Shape* refracted_shape = nullptr;
    if (hitted_shape->isPlane()){
        sf::Vector3f refracted_dir = hitted_shape->getNormal(point) * dot(ray.direct,hitted_shape->getNormal(point)) * (-2.0f);
        refracted_dir = refracted_dir + ray.direct;

        Ray refracted_ray(point, refracted_dir);

        auto refracted_pair = nearest_hit(refracted_ray, shapes);
        refracted_shape = refracted_pair.first;
        auto refracted_point = refracted_pair.second;
        Ray to_light(point,  normalize(light - point));
        float intensity = light_inten(dot(hitted_shape->getNormal(point), to_light.direct)); // [-1, 1]
        
        if (refracted_shape == nullptr) return Color(255*intensity,255*intensity,255*intensity);

        hitted_shape = refracted_shape;
        point = refracted_point;
    }
    
    Ray to_light(point,  normalize(light - point));
    
    auto secondary_hit_pair = nearest_hit(to_light, shapes, hitted_shape); // check for shade
    float intensity = shade_inten(dot(hitted_shape->getNormal(point), to_light.direct)); // [-1, 1]
    sf::Vector3i reflected(light_power*intensity, light_power*intensity, light_power*intensity);
    if (secondary_hit_pair.first == nullptr) return hitted_shape->getColor() + reflected;

    
    float shade_intensity = shade_inten(dot(hitted_shape->getNormal(secondary_hit_pair.second), to_light.direct)); // [-1, 1]

    sf::Vector3i shade(-light_power*shade_intensity, -light_power*shade_intensity, -light_power*shade_intensity);
    res = hitted_shape->getColor();
    return res + shade + reflected;*/
}

Ray Tracer::getRay(float x, float y, int width, int height, sf::Vector3f camera) {
    sf::Vector3f screenDot (
        0.0,
        x - width / 2,
        height / 2 - y
    );
    return Ray(camera, normalize(screenDot - camera));
}


Color Tracer::handlePixel(int x, int y, const Scene&, int width, int height) {
    Ray ray = getRay(x, y, width, height, scene.camera);
    return trace(ray);
}