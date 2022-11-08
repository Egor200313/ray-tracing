#include "color.hpp"

Color::Color operator+ (const sf::Vector3i& a){
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

Color::Color operator* (const float& ratio){
    int red = r * ratio;
    int green = g * ratio;
    int blue = b * ratio;
    return Color(red, green, blue, this->a);
}

Color operator+ (const Color& c1, const Color& c2) {
    int red = c1.r + c2.r;
    int green = c1.g + c2.g;
    int blue = c1.b + c2.b;;
    if (c1.r + c2.r > 255) red = 255;
    if (c1.g + c2.g > 255) green = 255;
    if (c1.b + c2.b > 255) blue = 255;
    if (c1.r + c2.r < 0) red = 0;
    if (c1.g + c2.g < 0) green = 0;
    if (c1.b + c2.b < 0) blue = 0;
    return Color(red, green, blue, c1.a + c2.a);
}