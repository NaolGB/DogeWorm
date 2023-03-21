//The worm is the user controlled object that moves to get food
#pragma once

#include "ofMain.h"

class Worm {
public:
    Worm();

    void update();
    void draw(float strength);

    float wormRadius, time;
    glm::vec2 wormPosition, wormHeadPosition;
};
