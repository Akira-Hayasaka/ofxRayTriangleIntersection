#include "testApp.h"

void testApp::setup()
{
    glEnable(GL_DEPTH_TEST);
    
    FaceTri tri;
    tri.v0 = ofPoint(ofGetWidth()/2, ofGetHeight()/2/2, -1000);
    tri.v1 = ofPoint(ofGetWidth()/2-200, ofGetHeight()/2+(ofGetHeight()/2/2), -1000);
    tri.v2 = ofPoint(ofGetWidth()/2+200, ofGetHeight()/2+(ofGetHeight()/2/2), -1000);                
    tris.push_back(tri);
    
    Ray ray;
    ray.rayOrig.set(0, 0, 0);
    ray.rayEnd.set(0, 0, -2000);
    rays.push_back(ray);
}

void testApp::update()
{
    rays.at(0).rayOrig.set(mouseX, mouseY, 0);
    rays.at(0).rayEnd.set(mouseX, mouseY, -2000);    
    ofVec3f rayDir = rays.at(0).rayEnd;
    rayDir -= rays.at(0).rayOrig;
    rtIntersect.checkMeshIntersection(rays, tris);
}

void testApp::draw()
{
    rtIntersect.drawDebug();
}

void testApp::keyPressed(int key){}
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y ){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}