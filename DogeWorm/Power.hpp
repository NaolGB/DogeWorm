//Power is the score recording system
//It also draws the score board at the top right corner as a bar

#pragma once

#include "ofMain.h"

class Power {
public:
    Power() {}

    void draw(float strength);

    float power;
};
