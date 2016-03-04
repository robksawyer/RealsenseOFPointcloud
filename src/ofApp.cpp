#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1280, 720);
    mRSSDK = RSDevice::createUniquePtr();
    if (!mRSSDK->init())
    {
        ofLogError("Unable to create ofxRSSDK object");
        exit();
    }
    
    mRSSDK->initRgb(RGBRes::VGA,30);
    mRSSDK->initDepth(DepthRes::QVGA, 30, false);
    mRSSDK->enablePointCloud(CloudRes::FULL_RES);
    mRSSDK->setPointCloudRange(100.0f,1000.0f);
    
    mRSSDK->start();
    setupCamera();

}

//--------------------------------------------------------------
void ofApp::update(){
    mRSSDK->update();
    
    mCloudMesh.clear();
    mCloudMesh.setMode(OF_PRIMITIVE_POINTS);
    mCloudMesh.enableColors();
    
    //TODO: Figure out a better way to work with BGRA pixels
    vector<ofVec3f> pointCloud = mRSSDK->getPointCloud();
    for(vector<ofVec3f>::iterator p=pointCloud.begin();p!=pointCloud.end();++p)
    {
        mCloudMesh.addVertex(*p);
        ofColor c = mRSSDK->getColorFromDepthSpace(*p);
        mCloudMesh.addColor(ofColor(c.b,c.g,c.r));
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(ofColor::black);
    ofSetColor(ofColor::white);
    
    mCamera.begin();
    mCloudMesh.draw();
    mCamera.end();
}

//--------------------------------------------------------------
void ofApp::exit()
{
    mRSSDK->stop();
}

//--------------------------------------------------------------
void ofApp::setupCamera()
{
    mCamera.setFov(45.0f);
    mCamera.setAspectRatio(ofGetWindowWidth() / (float)ofGetWindowHeight());
    mCamera.setNearClip(100);
    mCamera.setFarClip(5000);
    
    mCamera.setGlobalPosition(ofVec3f(0, 0, 0));
    mCamera.lookAt(ofVec3f(0, 0, 100), ofVec3f(0, 1, 0));
    mCamera.setAutoDistance(true);
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
