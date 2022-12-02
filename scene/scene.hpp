#include "../shapes/shape.hpp"
#include "../lighting/lightEmittor.hpp"
#include <vector>

class Scene{
private:
    std::vector<Shape*> objects;
    std::vector<LightEmittor> lights;
    sf::Vector3f camera;
    struct screen{
        int width;
        int height;
    };
    screen screen;
public:
    Scene() = default;
    Scene(const Scene&) = delete; // not copiable

    void addObject(Shape*);
    void addObjects(std::vector<Shape*>);

    void addLight(LightEmittor);
    void setCamera(sf::Vector3f);
    void setScreen(int, int);

    int getScreenWidth();
    int getScreenHeight();
    sf::Vector3f getCamera();

    std::vector<Shape*> getObjects();
    std::vector<LightEmittor> getLights();
    friend class Tracer;
};