//
//  camClass.h
//  camVisualisor
//
//  Created by David Haylock on 14/05/2014.
//
//

#ifndef __camVisualisor__camClass__
#define __camVisualisor__camClass__

#include <iostream>
#include "ofMain.h"
#include "ofxXmlSettings.h" // To load the points into the Cam's

#define MAX_NUM_PTS 2000

class Cam {
    public:
    
    Cam(){     }
    ~Cam(){     }
    
    //void setup(string absFilePath);//));
    void loadCam(string absFilePath,ofVec3f pos);
    void loadNewCam(string absFilePath,ofVec3f pos);
    void update(float rotationDeg);
    void draw(ofColor c,bool drawRods);
    void drawCamImage(ofPoint drawHere,ofColor c);
    ofVec2f whatIsCamRadiusAndPushRodTop();
    
    ofxXmlSettings camCoordsFile;
    vector <ofVec3f> camPts;
    
    ofVec3f dataPointCentre;
    ofMesh camMesh;
    ofVbo camVbo;
    
    int importlastTagNumber;
    int importPointCount;
    int importLineCount;

    float camRadius;
    float rotationDegrees;
    float pushRodRadius;
	float pushRodHeight;
	float pushRodTop;
    
    ofCylinderPrimitive pushRod;
    ofCylinderPrimitive guideRod;
};


#endif /* defined(__camVisualisor__camClass__) */
