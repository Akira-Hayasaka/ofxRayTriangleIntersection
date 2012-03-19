//
//  ofxRayTriangleIntersection.h
//
//  Created by Akira Hayasaka on 3/17/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#ifndef emptyExample_ofxRayTriangleIntersection_h
#define emptyExample_ofxRayTriangleIntersection_h

#include "ofMain.h"

class IntersectInfo 
{
public:
    IntersectInfo() 
    {
        bIntersect = false;
    }
    
    bool bIntersect;
    ofPoint intersectPos;
    float distance;
};

class Ray
{
public:
    ofPoint rayOrig;
    ofPoint rayEnd;      
};

class FaceTri
{
public:
    FaceTri()
    {
        bHit = false;
    }
    
    bool    bHit;
    ofPoint v0;
    ofPoint v1;
    ofPoint v2;
};

class ofxRayTriangleIntersection
{
public:
    
    vector<IntersectInfo> checkMeshIntersection(vector<Ray> p_rays, vector<FaceTri> p_faces)
    {
        faces.clear();
        rays.clear();
        intersecctInfos.clear();
        
        faces = p_faces;
        rays = p_rays;
        
        for (int j = 0; j < rays.size(); j++)
        {
            Ray ray = rays.at(j);
            ofVec3f rayDir = ray.rayEnd;
            rayDir -= ray.rayOrig;
            
            for (int i = 0; i < faces.size(); i++)
            {
                vector<ofPoint> verts;
                verts.push_back(faces.at(i).v0);
                verts.push_back(faces.at(i).v1);
                verts.push_back(faces.at(i).v2);        
                IntersectInfo intersecctInfo = judgeRayTri(ray.rayOrig, rayDir, verts);
                intersecctInfos.push_back(intersecctInfo);
                
                if (intersecctInfo.bIntersect)
                {
                    faces.at(i).bHit = true;
                    break;
                }
            }
        }
        return intersecctInfos;
    }    
    
    void drawDebug()
    {
        ofPushStyle();
        for (int i = 0; i < faces.size(); i++)
        {   
            if (faces.at(i).bHit)
            {
                ofSetColor(ofColor::magenta);                
            }
            else
            {
                ofSetColor(ofColor::yellow);                
            }
            glBegin(GL_TRIANGLES);
            glVertex3f(faces.at(i).v0.x, faces.at(i).v0.y, faces.at(i).v0.z);
            glVertex3f(faces.at(i).v1.x, faces.at(i).v1.y, faces.at(i).v1.z);
            glVertex3f(faces.at(i).v2.x, faces.at(i).v2.y, faces.at(i).v2.z);            
            glEnd();        
        }
        ofPopStyle();
        
        ofPushStyle();
        
        ofSetColor(ofColor::blue);
        for (int i = 0; i < rays.size(); i++)
        {
            ofLine(rays.at(i).rayOrig, rays.at(i).rayEnd);    
        }
        
        ofPopStyle();          
    }
    
    vector<IntersectInfo>   intersecctInfos;
    vector<Ray>             rays; 
    vector<FaceTri>         faces;
    
private:
    
    IntersectInfo judgeRayTri(ofVec3f rayStart, ofVec3f rayDir, vector<ofVec3f> tri)
    {
        IntersectInfo result;   
        
        rayDir.normalize();
        
        ofVec3f triNorm = getNormal(tri);
        float vn = rayDir.dot(triNorm);
        
        ofVec3f aa = rayStart - tri.at(0);
        float xpn = aa.dot(triNorm);
        float distance = -xpn / vn;
        
        if (distance < 0) return result; // behind ray origin. fail
        
        ofPoint hitPos(rayDir.x * distance + rayStart.x,
                       rayDir.y * distance + rayStart.y,
                       rayDir.z * distance + rayStart.z);
        
        ofVec3f hit00 = hitPos - tri.at(0);
        ofVec3f hit01 = tri.at(1) - tri.at(0);
        ofVec3f cross0 = hit00.cross(hit01);
        if (cross0.dot(triNorm) > 0.000000001) return result;; // not in tri. fail
        
        ofVec3f hit10 = hitPos - tri.at(1);
        ofVec3f hit11 = tri.at(2) - tri.at(1);        
        ofVec3f cross1 = hit10.cross(hit11);        
        if (cross1.dot(triNorm) > 0.000000001) return result;; // not in tri. fail        
        
        ofVec3f hit20 = hitPos - tri.at(2);
        ofVec3f hit21 = tri.at(0) - tri.at(2);        
        ofVec3f cross2 = hit20.cross(hit21);        
        if (cross2.dot(triNorm) > 0.000000001) return result;; // not in tri. fail
        
        // intersect!
        result.bIntersect = true;
        result.intersectPos = hitPos;
        result.distance = distance;
        return result;
        
    }    
    
    ofVec3f getNormal(vector<ofVec3f> pverts)
    {
        ofVec3f t0 = pverts.at(1)-pverts.at(0);
        ofVec3f t1 = pverts.at(2)-pverts.at(0);
        ofVec3f normal = t0.getCrossed(t1);
        normal.normalize();
        return  normal;
    }
    
};

#endif
