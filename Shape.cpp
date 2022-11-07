#include <SFML/Graphics.hpp>
#include <optional>
#include <cmath>
#include <vector>

float dot(const sf::Vector3f& v1, const sf::Vector3f& v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

float dist(const sf::Vector3f& v1, const sf::Vector3f& v2) {
    sf::Vector3f diff = v1 - v2;
    return std::sqrt(dot(diff, diff));
}

sf::Vector3f normalize(sf::Vector3f v){
    float len = std::sqrt(dot(v, v));
    return v / len;
}

struct Ray{
    sf::Vector3f o;
    sf::Vector3f direct;
    Ray() = default;
    Ray(const sf::Vector3f& o, const sf::Vector3f& dir):o(o), direct(dir){}
    Ray(float x0, float y0, float z0, float v1, float v2, float v3){
        o.x = x0;
        o.y = y0;
        o.z = z0;
        direct.x = v1;
        direct.y = v2;
        direct.z = v3;
    }
    Ray(const Ray& r) = default;
};

struct Color{
    int r, g, b;
    int a = 255;
    Color() = default;
    Color(int r, int g, int b, int a): r(r), g(g), b(b), a(a){}
    Color(int r, int g, int b): r(r), g(g), b(b){}
    Color(const Color& c) = default;

    Color operator+ (const sf::Vector3i& a){
        int red = r + a.x;
        int green = g + a.y;
        int blue = b + a.z;
        if (red < 0) red = 0;
        if (red > 255) red = 255;
        if (green < 0) green = 0;
        if (green > 255) green = 255;
        if (blue < 0) blue = 0;
        if (blue > 255) blue = 255;
        return Color(red, green, blue, this->a);
    }
};

Color operator+ (const Color& c1, const Color& c2) {
    int red = c1.r + c2.r;
    int green = c1.g + c2.g;
    int blue = c1.b + c2.b;;
    if (c1.r + c2.r > 255) red = 255;
    if (c1.g + c2.g > 255) green = 255;
    if (c1.b + c2.b > 255) blue = 255;
    return Color(red, green, blue, c1.a + c2.a);
}

class Shape {
  public:
    virtual std::optional<sf::Vector3f> hit(const Ray&) = 0;
    virtual Color getColor() = 0;
    virtual sf::Vector3f getNormal(sf::Vector3f) = 0;

    virtual bool operator==(const Shape& s) const = 0;

    virtual bool isPlane() = 0;
};



class Sphere: public Shape {
  public:
    sf::Vector3f center;
    float R;
    Color clr;
    Sphere() = default;
    Sphere(float x0, float y0, float z0, float R){
        center.x = x0;
        center.y = y0;
        center.z = z0;
        this->R = R;
        clr = Color(0, 0, 0);
    }
    Sphere(float x0, float y0, float z0, float R, Color c){
        center.x = x0;
        center.y = y0;
        center.z = z0;
        this->R = R;
        clr = c;
    }
    Sphere(const Sphere& s) = default;

    void setColor(Color c) {
        clr = c;
    }

    bool isPlane() override{
        return false;
    }

    std::optional<sf::Vector3f> hit(const Ray& ray) override{
        sf::Vector3f diff = ray.o - center;
        float D = dot(diff, ray.direct)*dot(diff, ray.direct) - dot(ray.direct, ray.direct)*(dot(diff, diff)-R*R);
        if (D < 0) return std::nullopt;
        float alpha1 = (-dot(diff, ray.direct) + std::sqrt(D)) / dot(ray.direct, ray.direct);
        float alpha2 = (-dot(diff, ray.direct) - std::sqrt(D)) / dot(ray.direct, ray.direct);
        if (alpha1 > alpha2) std::swap(alpha1, alpha2);
        if (alpha1 < 0.0001 && alpha2 < 0.0001) return std::nullopt;
        if (alpha1 < 0.0001) return std::optional<sf::Vector3f>(ray.o + alpha2*ray.direct);
        return std::optional<sf::Vector3f>(ray.o + alpha1*ray.direct); // only the nearest hit point
    }

    Color getColor()override {
        return clr;
    }

    sf::Vector3f getNormal(sf::Vector3f point) override{
        return normalize(point - center);
    }

    bool operator==(const Shape& sh)const override{
        const Sphere* tmp = dynamic_cast<const Sphere*>(&sh);
        if (tmp==NULL) return false;
        return tmp->R == R && tmp->center == center;
    }
};

class Plane: public Shape {
public:
    sf::Vector3f normal;
    float bias;
    Plane() = default;
    Plane(sf::Vector3f normal, float bias): normal(normal), bias(bias){}

    std::optional<sf::Vector3f> hit(const Ray& ray) override{
        float alpha = (-bias - dot(normal, ray.o)) / dot(normal, ray.direct);
        if (alpha < 0.0) return std::nullopt;
        return std::optional<sf::Vector3f>(ray.o + alpha*ray.direct);
    }

    Color getColor() override{
        return Color(100, 100, 100);
    }

    sf::Vector3f getNormal(sf::Vector3f) override{
        return normal;
    }

    bool isPlane() override{
        return true;
    }

    bool operator==(const Shape& sh)const override{
        const Plane* tmp = dynamic_cast<const Plane*>(&sh);
        if (tmp==NULL) return false;
        return tmp->bias == bias && tmp->normal == normal;
    }
};

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