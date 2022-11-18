#include "cube.hpp"

Cube::Cube(const sf::Vector3f& left, float side_len){

    sf::Vector3f right = {left.x + side_len, left.y + side_len, left.z + side_len};

    sf::Vector3f p1 = {left.x, right.y, left.z};
    sf::Vector3f p2 = {right.x, right.y, left.z};
    sf::Vector3f p3 = {right.x, left.y, left.z};
    sf::Vector3f p4 = {right.x, left.y, right.z};
    sf::Vector3f p5 = {left.x, left.y, right.z};
    sf::Vector3f p6 = {left.x, right.y, right.z};

    //bottom
    Triangle v1({left,p1,p2});
    Triangle v2({left,p3,p2});
    //right
    Triangle v3({right,p2,p6});
    Triangle v4({p1,p2,p6});
    //front
    Triangle v5({left,p5,p6});
    Triangle v6({left,p1,p6});
    //left
    Triangle v7({left,p5,p4});
    Triangle v8({left,p5,p3});
    //top
    Triangle v9({right,p4,p6});
    Triangle v10({p4,p5,p6});

    normals = {
        {0.0, 0.0, -1.0},
        {0.0, 0.0, -1.0},
        {0.0, 1.0, 0.0},
        {0.0, 1.0, 0.0},
        {-1.0, 0.0, 0.0},
        {-1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, 1.0},
    };

    edges = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10};
}