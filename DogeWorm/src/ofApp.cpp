#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //Initial chances of adding new food
    goodChance = 0.02;
    badChance = 0.02;

    //Initail scores
    eatGood = 0;
    eatBad = 0;

    //Initial foods added to the vector
    for (int i = 0; i < 1; i++) {
        GoodFood gf;
        gf.speed = 1;
        goodfoods.push_back(gf);

        BadFood bf;
        bf.speed = 1;
        badfoods.push_back(bf);
    }
}

void ofApp::hasEaten() {
    //Check whether the head of the wom is fully inside a food
    //Change score and remove the food if head is in the food
    for (int i = 0; i < goodfoods.size(); i++) {
        if (\
            w.wormHeadPosition.y + w.wormRadius <= goodfoods[i].foodPosition.y + goodfoods[i].foodRadius\
            and\
            w.wormHeadPosition.y - w.wormRadius >= goodfoods[i].foodPosition.y - goodfoods[i].foodRadius\
            and\
            w.wormHeadPosition.x + w.wormRadius <= goodfoods[i].foodPosition.x + goodfoods[i].foodRadius\
            and\
            w.wormHeadPosition.x - w.wormRadius >= goodfoods[i].foodPosition.x - goodfoods[i].foodRadius) {
                eatGood += 1;
                goodfoods.erase(goodfoods.begin() + i);
                goodFoodSize = goodfoods.size();
        }
    }

    for (int i = 0; i < badfoods.size(); i++) {
        if (\
            w.wormHeadPosition.y + w.wormRadius <= badfoods[i].foodPosition.y + badfoods[i].foodRadius\
            and\
            w.wormHeadPosition.y - w.wormRadius >= badfoods[i].foodPosition.y - badfoods[i].foodRadius\
            and\
            w.wormHeadPosition.x + w.wormRadius <= badfoods[i].foodPosition.x + badfoods[i].foodRadius\
            and\
            w.wormHeadPosition.x - w.wormRadius >= badfoods[i].foodPosition.x - badfoods[i].foodRadius) {
                eatBad += 1;
                badfoods.erase(badfoods.begin() + i);
                badFoodSize = badfoods.size();
        }
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef();
    w.update();

    //7 Seconds left for How-to-play at the begining
    //Update the food objects and remove delete the ones off screen
    if (time > 7) {
        for (int i = 0; i < goodfoods.size(); i++) {
            //Update food location
            goodfoods[i].update();

            //Remove foods outside the screen
            if (goodfoods[i].foodPosition.y + goodfoods[i].foodRadius < 0) {
                goodfoods.erase(goodfoods.begin() + i);
                goodFoodSize = goodfoods.size();
            }
        }

        for (int i = 0; i < badfoods.size(); i++) {
            //Update food location
            badfoods[i].update();

            //Remove foods outside the screen
            if (badfoods[i].foodPosition.y + badfoods[i].foodRadius < 0) {
                badfoods.erase(badfoods.begin() + i);
                badFoodSize = badfoods.size();
            }
        }
    }
    

    //Add new food based on chance of good and bad chance
    if (ofRandom(10) <= goodChance) {
        GoodFood gf;
        gf.speed = 1;
        goodfoods.push_back(gf);
    }

    if (ofRandom(10) <= badChance) {
        BadFood bf;
        bf.speed = 1;
        badfoods.push_back(bf);
    }

    //Add speed
    for (int i = 0; i < goodfoods.size(); i++) {
        goodfoods[i].speed = ofMap(time, 7, 15 * 60, 1, 50);
    }

    for (int i = 0; i < badfoods.size(); i++) {
        badfoods[i].speed = ofMap(time, 7, 15 * 60, 1, 50);
    }

    //Add chance new food
    goodChance = ofMap(time, 7, 5 * 60, 0.02, 1);
    badChance = ofMap(time, 7, 3 * 60, 0.02, 1);


    //Check the eating (win or loose)
    hasEaten();

    //Check game-over
    if (eatBad > eatGood) {
        if (eatGood == 0 and eatBad >= 9) {
            goodfoods.clear();
            badfoods.clear();
            goodChance = -1;
            badChance = -1;
        }
        if (eatGood > 0 and (eatGood / eatBad) - 1 <= -0.9) {
            goodfoods.clear();
            badfoods.clear();
            goodChance = -1;
            badChance = -1;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetLineWidth(2);

    //How-to-play at the begining (7 secs)
    if (time < 7) {
        string line1 = "How To Play\n------------\n\n";
        string line2 = "       Control your worm with 'a' for left and 'd' for right.\n\n";
        string line3 = "Insert your worm's head completely in a green circle to gain points.\n";
        string line4 = "   Inserting your worm's head in a red circle losses you a point.\n\n";
        string line5 = "    You loose the game if your gain/loose ratio reaches 0.9.\n";

        string label = line1 + line2 + line3 + line4 + line5;
        ofDrawBitmapStringHighlight(label, ofGetWidth()/2 - 300, ofGetHeight()/2 -100);
    }

    //Main game
    else if(time > 7 and goodChance > -1){
        if (eatBad > 0) {
            w.draw(((eatGood+1) / eatBad) - 1);
        }
        else {
            w.draw(0.5);
        }

        for (int i = 0; i < goodfoods.size(); i++) {
            goodfoods[i].draw();
        }

        for (int i = 0; i < badfoods.size(); i++) {
            badfoods[i].draw();
        }

        //Update the score bar
        if (eatBad > 0) {
            p.draw(((eatGood+1) / eatBad) - 1);
        }
        else {
            p.draw(1);
        }

        //Text score board
        string line = "Win, Loose: " + to_string(int(eatGood)) + ", " + to_string(int(eatBad));

        ofDrawBitmapStringHighlight(line, 20, 20);

    }

    //Game-over
    else {
        string line = "Game Over! Win, Loose: " + to_string(int(eatGood)) + ", " + to_string(int(eatBad));

        ofDrawBitmapStringHighlight(line, ofGetWidth()/2 - 50, ofGetHeight()/2);
    }

    

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //Control movement (interactivity)
    if (key == 'a' or key == 'A') {
        w.wormPosition.x -= 7;
    }
    if (key == 'd' or key == 'D') {
        w.wormPosition.x += 7;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
