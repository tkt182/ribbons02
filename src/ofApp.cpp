#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofHideCursor();
    ribbon = new ofxTwistedRibbon();
    ofBackground(0, 0, 0);
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    myFbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    myGlitch.setup(&myFbo);
    
    _zMove = 0.0;
    _role = 0;
    _enableParticle = true;
    _enableRibbon   = false;
    _trackRibbon    = true;
    vboPartciles = new ofxVboParticles(5000, 100000);
    vboPartciles->friction = 0.001;
    particlePosition = ofVec3f(0, 0, 0);
    
    myGlitch.setFx(OFXPOSTGLITCH_GLOW, true);

}

//--------------------------------------------------------------
void ofApp::update(){
    ofVec3f position;
    float speed = 5.0;
    float radius = sin(ofGetElapsedTimef() * speed * 0.2) * 90 + 200;
    position.z = sin(ofGetElapsedTimef() * speed) * radius -_zMove;
    position.x  = cos(ofGetElapsedTimef() * speed) * radius;
    position.y  = sin(ofGetElapsedTimef() * speed * 1.3) * radius;
    
    if(_trackRibbon){
        particlePosition = position;
    }else{
        particlePosition.z = sin(ofGetElapsedTimef()) * 400;
        particlePosition.x  = cos(ofGetElapsedTimef()) * 400;
        particlePosition.y  = sin(ofGetElapsedTimef() / 2.0) * 100;
        particlePosition.z -= _zMove;
    }
    

    
    ofColor color;
    int hue = int(ofGetElapsedTimef() * 10) % 255;
    
    myFbo.begin();
    ofClear(0, 0, 0,255);
    ofPushMatrix();
    
    color.setHsb(hue, 120, 255, 200);
    
    ribbon->update(position, color);
    for (int i = 0; i < 40; i++) {
        ofVec3f position = particlePosition;
        ofVec3f velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
        ofColor color;
        color.setHsb(ofRandom(60, 160), 140, 220);
        //color.setHsb(ofRandom(60, 255), ofRandom(60, 255), ofRandom(60, 255));
        
        if(!_enableParticle){
            position = ofVec3f(0);
        }
        
        // add a particle
        //vboPartciles->addParticle(position, velocity, color);
        vboPartciles->addParticle(position, velocity, color);
    }
    vboPartciles->update();
    
    ofPopMatrix();
    
    cam.begin();
    //ofRotate(ofGetElapsedTimef() * 10, 1, 1, 0);
    cam.setPosition(0, 0, -_zMove + 500.0);
    ofPushMatrix();
    ofRotate(_role, 0, 1, -_zMove + 500.0);
    if (_enableRibbon) ribbon->draw();
    if (_enableParticle) vboPartciles->draw();
    ofPopMatrix();
    cam.end();
    
    myFbo.end();
    
    _role += 0.5;
    _zMove += 1.5;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /* Apply effects */
    myGlitch.generateFx();
    
    /* draw effected view */
    myFbo.draw(0, 0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
    
    if (key == 'q') myGlitch.toggleFx(OFXPOSTGLITCH_CONVERGENCE);
    if (key == 'w') myGlitch.toggleFx(OFXPOSTGLITCH_GLOW);
    if (key == 'e') myGlitch.toggleFx(OFXPOSTGLITCH_SHAKER);
    if (key == 'r') myGlitch.toggleFx(OFXPOSTGLITCH_CUTSLIDER);
    if (key == 't') myGlitch.toggleFx(OFXPOSTGLITCH_TWIST);
    if (key == 'y') myGlitch.toggleFx(OFXPOSTGLITCH_OUTLINE);
    if (key == 'u') myGlitch.toggleFx(OFXPOSTGLITCH_NOISE);
    if (key == 'i') myGlitch.toggleFx(OFXPOSTGLITCH_SLITSCAN);
    if (key == 'o') myGlitch.toggleFx(OFXPOSTGLITCH_SWELL);
    if (key == 'p') myGlitch.toggleFx(OFXPOSTGLITCH_INVERT);

    if (key == 'z'){
        _enableRibbon   = _enableRibbon ? false : true;
    }
    if (key == 'x'){
        _enableParticle = _enableParticle ? false : true;
    }
    if (key == 'c'){
        _trackRibbon = _trackRibbon ? false : true;
    }
    
    if (key == 'b'){
        //vboPartciles->deleteParticle();
        delete vboPartciles;
        vboPartciles = new ofxVboParticles(5000, 100000);
        vboPartciles->friction = 0.001;
        for (int i = 0; i < 40; i++) {
            ofVec3f position = particlePosition;
            ofVec3f velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
            ofColor color;
            color.setHsb(ofRandom(60, 160), 140, 220);
            //color.setHsb(ofRandom(60, 255), ofRandom(60, 255), ofRandom(60, 255));
            
            if(!_enableParticle){
                position = ofVec3f(0);
            }
            
            // add a particle
            //vboPartciles->addParticle(position, velocity, color);
            vboPartciles->addParticle(ofVec3f(0), velocity, color);
        }
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
