float light_inten(float intensity) {
    return std::pow(intensity, 4);
}

float shade_inten(float x) {
    return (x+1.0)*(x+1.0) - 1.0;
}


Color trace(const Ray& ray) {
    auto first_hit_pair = nearest_hit(ray, shapes);
    Shape* hitted_shape = first_hit_pair.first;
    auto point = first_hit_pair.second;
    sf::Vector3i l = {light_power, light_power, 4*light_power};
    if (hitted_shape == nullptr) return Color(0, 0, 0);

    Color res = hitted_shape->getColor();
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
    return res + shade + reflected;
}