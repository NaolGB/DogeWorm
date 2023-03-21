#include "Power.h"

void Power::draw(float strength) {
    //The surrounding outline
    ofSetColor(255);
    ofNoFill();
    ofDrawRectRounded(glm::vec2(2 * (ofGetWidth() / 3), 10), ofGetWidth() / 3 - 10, 30, 9);

    //The internal bar
    ofFill();
    //The width and color of the bar is mapped against the strength (win/lose ration) passed by the caller
    float diff = ofMap(strength, -0.9, 1, 0, ofGetWidth() / 3 - 20);
    if (diff > ofGetWidth() / 3 - 20) {
        diff = ofGetWidth() / 3 - 20;
    }

    if (strength >= 0) {
        ofSetColor(37, 209 *strength , 123);
    }
    else {
        ofSetColor(239 * abs(strength), 51, 65);
    }
    ofDrawRectRounded(glm::vec2(2 * (ofGetWidth() / 3) + 5, 15), diff, 20, 6);
}
