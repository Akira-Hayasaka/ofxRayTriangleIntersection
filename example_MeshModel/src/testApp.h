#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

#include "ofxRayTriangleIntersection.h"

#define RAYNUM 10

class testApp : public ofBaseApp{

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

private:
    bool    bAnimate;
    bool    bAnimateMouse;
    float   animationTime;
    ofxAssimpModelLoader model;

    vector<ofVboMesh>   meshes;
    vector<ofMaterial>  materials;
    vector<ofTexture>   texes;
    ofPoint             position;
    float               normScale;
    ofPoint             scale;
    ofPoint             sceneCenter;
    ofLight             light;
    
    
    ofxRayTriangleIntersection  rtIntersect;    
    
    vector<FaceTri> getFace();
    ofPoint         fixGeometry(ofPoint v);
    GLfloat         m[16];
    
    // debug
    int numIndice;
    bool bDrawMesh;
};

#endif
