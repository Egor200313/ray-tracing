#include "../shapes/shape.hpp"
#include <vector>

class Scene{
private:
    std::vector<Shape*> objects;
    std::vector<sf::Vector3f> lights;
    sf::Vector3f camera;
    struct screen{
        int width;
        int height;
    };
public:
    Scene() = default;
    Scene(const Scene&) = delete; // not copiable

    void addObject(Shape*);
    void addObjects(std::vector<Shape*>);

    void addLight(sf::Vector3f);
    void setCamera(sf::Vector3f);
    void setScreen(int, int);

    int getScreenWidth();
    int getScreenHeight();
    sf::Vector3f getCamera();

    std::vector<Shape*> getObjects();
    std::vector<sf::Vector3f> getLights();
    friend class Tracer;
};