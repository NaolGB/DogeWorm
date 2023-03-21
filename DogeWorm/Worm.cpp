#include "Worm.h"

Worm::Worm() {
    ofSetCircleResolution(50);
    wormRadius = 20;
    wormPosition = glm::vec2(ofGetWidth() / 2, 100);
}
void Worm::update() {
    time = ofGetElapsedTimef();
}

void Worm::draw(float strength) {
    //The color of the worm is mapped against the strength (win/lose ration) passed by the caller
    float hue = 255 * ofMap(strength, -0.9, 1, 0, 1) / 150;
    ofFill();
    for (int i = wormPosition.y-150; i < wormPosition.y; i+=1) {

        //Control against out-of-screen movement
        if (wormPosition.x < 0) {
            wormPosition.x = 0;
        }
        if (wormPosition.x > ofGetWidth()) {
            wormPosition.x = ofGetWidth();
        }

        //The position of the head of the worm for calculation of win or loose
        if (i == wormPosition.y - 1) {
            wormHeadPosition = glm::vec2((wormPosition.x + (100 * sin(i*0.03 + time)) / 2), i);
        }
        
        //Draw the circles that form the worm, moving as a finction of sin
        ofSetColor(ofColor::fromHsb(hue*abs(i), 255, 255));
        ofDrawCircle((wormPosition.x + (100 * sin(i*0.03 + time)) / 2), i, wormRadius);
    }
}
