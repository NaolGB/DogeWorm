//Food is the object that adds as a reward or punishment when collided to by the worm
//There are two types of food (GoodFood - reward, and BadFood - punishment)
#pragma once

#include "ofMain.h"

class GoodFood {
public:
    GoodFood();

    void update();
    void draw();

    glm::vec2 foodPosition;
    float foodRadius, speed;
};

class BadFood {
public:
    BadFood();

    void update();
    void draw();

    glm::vec2 foodPosition;
    float foodRadius, speed;
};
