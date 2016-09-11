#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"
#include "ofxTwistedRibbon.h"
#include "ofxVboParticles.h"

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    float _zMove;
    float _role;
    
    ofxTwistedRibbon *ribbon;
    ofxVboParticles *vboPartciles;
    ofVec3f particlePosition;
    ofEasyCam cam;
    
    ofFbo			myFbo;
    
    /*Addon instance*/
    ofxPostGlitch	myGlitch;
    
    bool _enableParticle;
    bool _enableRibbon;
    
    bool _trackRibbon;
    
};
