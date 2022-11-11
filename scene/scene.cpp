#include "scene.hpp"

void Scene::addObject(Shape* shape){
    this->objects.push_back(shape);
}

void Scene::addObjects(std::vector<Shape*> objects){
    this->objects = objects;
}

void void Scene::addLight(sf::Vector3f light){
    this->lights.push_back(light);
}

void Scene::setCamera(sf::Vector3f cam){
    this->camera = cam;
}

void Scene::setScreen(int width, int height){
    this->screen.width = width;
    this->screen.height = height;
}

int Scene::getScreenWidth(){
    return this->screen.width;
}

int Scene::getScreenHeight(){
    return this->screen.height;
}

sf::Vector3f Scene::getCamera(){
    return this->camera;
}

std::vector<Shape*> Scene::getObjects(){
    return this->objects;
}

std::vector<sf::Vector3f> Scene::getLights() {
    return this->lights;
}