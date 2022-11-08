// just one method trace(Scene) - > pixels array
#include "../scene/scene.hpp"

class Tracer{
private:
    // 3d ray from dot on the screen
    Ray getRay(float x, float y, int width, int height, sf::Vector3f camera) {
        sf::Vector3f screenDot (
            0.0,
            x - width / 2,
            height / 2 - y
        );
        return Ray(camera, normalize(screenDot - camera));
    }


    Color handlePixel(int x, int y, const Scene&, int width, int height) {
        Ray ray = getRay(x, y, width, height, scene.camera);
        return trace(ray);
    }

public:
    Tracer() = default;

    void traceScene(const Scene& scene, sf::Uint8* pixels, int width, int height) {
        Color color;
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                int index = (y*width + x) * 4;
                color = handlePixel(x, y, scene);
                pixels[index] = color.r;
                pixels[index+1] = color.g;
                pixels[index+2] = color.b;
                pixels[index+3] = color.a;
            }
        }
    }

}