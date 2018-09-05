#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    blur.load("shader/blur.vert", "shader/blur.frag");
    bloom.load("shader/bloom.vert", "shader/bloom.frag");
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
    onePassFbo.allocate(ofGetWidth(), ofGetHeight());
    twoPassFbo.allocate(ofGetWidth(), ofGetHeight());
    
    gui.setup();
    gui.setPosition(10, 10);
    gui.add(strength.set("strength", 8.0, 0.0, 20.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
    
    ofClear(0, 0, 0, 0);
    cam.begin();
    
    ofRotateZDeg(30.0);
    
    ofSetColor(200, 200, 200, 255);
    ofDrawBox(100, 0, 300, 100);
    ofSetColor(0, 0, 200, 255);
    ofDrawSphere(-100, 0, 300, 100);
    
    cam.end();
    
    fbo.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // X方向のガウシアンブラー
    onePassFbo.begin();

    blur.begin();

    blur.setUniformTexture("tex", fbo.getTexture(), 0);
    blur.setUniform1i("horizontal", true);
    blur.setUniform1f("strength", strength);
    fbo.draw(0, 0);

    blur.end();

    onePassFbo.end();
//
    // Y方向のガウシアンブラー
    twoPassFbo.begin();

    blur.begin();
    blur.setUniformTexture("tex", onePassFbo.getTexture(), 0);
    blur.setUniform1i("horizontal", false);
    blur.setUniform1f("strength", strength);

    onePassFbo.draw(0, 0);

    blur.end();

    twoPassFbo.end();

    // ガウシアンブラーと元の描画内容を加算合成
    bloom.begin();
    bloom.setUniformTexture("tex", fbo.getTexture(), 0);
    bloom.setUniformTexture("blur", twoPassFbo.getTexture(), 1);

    fbo.draw(0, 0);

    bloom.end();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
