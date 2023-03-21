//The game is drawn in the App.cpp, the mechanics is in the hasEaten() method
#pragma once

#include "ofMain.h"
#include "Worm.h"
#include "Food.h"
#include "Power.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

        void hasEaten();
        
        float goodChance, badChance, time, eatGood, eatBad;
        float badFoodSize, goodFoodSize;

        Worm w;
        vector<GoodFood> goodfoods;
        vector<BadFood> badfoods;

        Power p;
};
