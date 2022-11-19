// just one method trace(Scene) - > pixels array
#include "../scene/scene.hpp"
#include <SFML/Window.hpp>


class Tracer{
private:
    Scene* scene;
    // 3d ray from dot on the screen
    Ray getRay(float x, float y);
    Color handlePixel(int x, int y);
    Color getIllumination(sf::Vector3f, Shape*);
    Color trace(const Ray&, int);

public:
    Tracer() = default;
    Tracer(Scene*);

    void traceScene(sf::Uint8*);
};