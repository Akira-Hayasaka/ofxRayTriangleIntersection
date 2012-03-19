#include "testApp.h"

void testApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    // we need GL_TEXTURE_2D for our models coords.
    ofDisableArbTex();

    if(model.loadModel("astroBoy_walk.dae",true)){
    	model.setAnimation(0);
    	model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.75 , 0);

        meshes.clear();
        materials.clear();
        texes.clear();
        numIndice = 0;
        for (int i = 0; i < model.getNumMeshes(); i++)
        {
            meshes.push_back(model.getMesh(i));
            materials.push_back(model.getMaterialForMesh(i));
            texes.push_back(model.getTextureForMesh(i));    
            numIndice += meshes.at(i).getNumIndices();            
        }
    	position = model.getPosition();
    	normScale = model.getNormalizedScale();
    	scale = model.getScale();
    	sceneCenter = model.getSceneCenter();
    }

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    light.enable();
    ofEnableSeparateSpecularLight();


	bAnimate		= false;
	bAnimateMouse 	= false;
	animationTime	= 0.0;
    
    numIndice = 0;
    bDrawMesh = true;
}

void testApp::update()
{

	if( bAnimate )
    {
		animationTime += ofGetLastFrameTime();
		if( animationTime >= 1.0 ){
			animationTime = 0.0;
		}
	    model.setNormalizedTime(animationTime);
        meshes.clear();
        materials.clear();
        texes.clear();     
        numIndice = 0;
        for (int i = 0; i < model.getNumMeshes(); i++)
        {        
            meshes.push_back(model.getCurrentAnimatedMesh(i));
            materials.push_back(model.getMaterialForMesh(i));
            texes.push_back(model.getTextureForMesh(i));               
            numIndice += meshes.at(i).getNumIndices();
        }
	}


	if( bAnimateMouse )
    {
	    model.setNormalizedTime(animationTime);
        meshes.clear();
        materials.clear();
        texes.clear();                
        numIndice = 0;
        for (int i = 0; i < model.getNumMeshes(); i++)
        {        
            meshes.push_back(model.getCurrentAnimatedMesh(i));
            materials.push_back(model.getMaterialForMesh(i));
            texes.push_back(model.getTextureForMesh(i));                           
            numIndice += meshes.at(i).getNumIndices();            
        }
	}

    vector<Ray> rays;
    for (int i = 0; i < RAYNUM; i++)
    {
        Ray ray;
        ray.rayOrig.set(mouseX+ofRandom(-100,100), mouseY+ofRandom(-100,100), 1000);
        ray.rayEnd.set(mouseX+ofRandom(-100,100), mouseY+ofRandom(-100,100), -2000);    
        rays.push_back(ray);
    }
    vector<FaceTri> faces = getFace();
    rtIntersect.checkMeshIntersection(rays, faces);
}


void testApp::draw()
{
    ofBackground(50, 50, 50, 0);
    ofSetColor(255, 255, 255, 255);
    
    if (bDrawMesh) 
    {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
        glEnable(GL_NORMALIZE);
        ofPushMatrix();

            ofTranslate(position);
            ofRotate(180, 0, 0, 1);
            ofTranslate(-sceneCenter.x, -sceneCenter.y, sceneCenter.z);
            ofScale(normScale , normScale, normScale);
            ofScale(scale.x,scale.y,scale.z);
            glGetFloatv(GL_MODELVIEW_MATRIX, m);  

            for (int i = 0; i < meshes.size(); i++)
            {
                texes.at(i).bind();
                materials.at(i).begin();
                meshes.at(i).drawWireframe();
                materials.at(i).end();
                texes.at(i).unbind();
            }

        ofPopMatrix();
        glPopAttrib();
    }
    else
    {
        rtIntersect.drawDebug();     
    }

    ofDrawBitmapString("push 'f' key to see intersections", 10, 15);
    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 30);
    ofDrawBitmapString("drag to control animation with mouseY", 10, 45);
    ofDrawBitmapString("num animations for this model: " + ofToString(model.getAnimationCount()), 10, 60);
    ofDrawBitmapString("num indices: " + ofToString(numIndice), 10,75);
}

void testApp::keyPressed(int key)
{
    switch (key) 
    {
		case ' ':
			bAnimate = !bAnimate;
			break;
        case 'f':
            bDrawMesh = !bDrawMesh;
            if (!bDrawMesh) ofHideCursor();
            else ofShowCursor;
            break;
        default:
            break;
    }
}

void testApp::mouseDragged(int x, int y, int button)
{
	bAnimateMouse = true;
	animationTime = float(y)/float(ofGetWidth());
}

void testApp::mouseReleased(int x, int y, int button)
{
	bAnimateMouse = false;
}

vector<FaceTri> testApp::getFace()
{
    vector<FaceTri> res;
    for (int i = 0; i < meshes.size(); i++)
    {
        vector<ofIndexType>& indices = meshes.at(i).getIndices();
        ofVec3f* vertsPtr = meshes.at(i).getVerticesPointer();
        for (int j = 0; j < indices.size(); j+=3)
        {
            FaceTri tri;
            tri.v0 = fixGeometry(vertsPtr[indices.at(j + 0)]);
            tri.v1 = fixGeometry(vertsPtr[indices.at(j + 1)]);
            tri.v2 = fixGeometry(vertsPtr[indices.at(j + 2)]);
            res.push_back(tri);
        }
    }
    return res;
}

ofPoint testApp::fixGeometry(ofPoint v)
{
    ofMatrix4x4 mat(m);
    ofPoint transformed = v * mat;
    transformed.y *= -1;
    transformed += ofPoint(ofGetWidth()/2, ofGetHeight()/2, 650); // ???
    return transformed;
}

void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y ){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}

