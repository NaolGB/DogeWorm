#include "Food.h"

//Speed refers to the rate at which the food crosses the screen

GoodFood::GoodFood() {
    foodRadius = ofRandom(20, 50);
    foodPosition = glm::vec2(ofRandom(ofGetWidth()), ofGetHeight()+foodRadius);
}

void GoodFood::update() {
    foodPosition.y -= speed;
}

void GoodFood::draw() {
    ofNoFill();
    ofSetColor(37, 209, 123);
    ofDrawCircle(foodPosition, foodRadius);
}

BadFood::BadFood() {
    foodRadius = ofRandom(20, 50);
    foodPosition = glm::vec2(ofRandom(ofGetWidth()), ofGetHeight() + foodRadius);
}

void BadFood::update() {
    foodPosition.y -= speed;
}

void BadFood::draw() {
    ofNoFill();
    ofSetColor(239, 51, 65);
    ofDrawCircle(foodPosition, foodRadius);
}
