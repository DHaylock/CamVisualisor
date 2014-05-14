#pragma once

#include "ofMain.h"
//#include "ofxDxfExport.h"
#define MAX_NUM_PTS 200

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void turnMainCam();
	void drawCentreCamAxle();
	void drawFrontCamAxle();
	void drawBackCamAxle();
	void drawCams();
	void drawCentreCam();
	void drawFRCam();
	void drawFLCam();
	void drawFCCam();
	void drawGuideRods();
	void drawPushRods();
	void drawBowl();
    
    
	
	void designCentreCam();
	void designFRCam();
	void designFLCam();
	void designFCCam();
	void designCamBR();
	void designBowl();
    
	ofLight niceLight;
	
	ofColor textColour;
	ofColor camCentreColour;
	ofColor camFRColour;
	ofColor camFLColour;
	ofColor camFCColour;
	ofColor axleColour;
	ofColor pushRodColour;
	ofColor bowlColour;
	ofColor bowlSidesColour;
	
	
	//Data points and meshes for bowl
	ofMesh bowlVisMesh;
	ofMesh bowlCutMesh;
	float dataPointBowlSides[MAX_NUM_PTS]; //the data point (i.e. amplitude)
	ofVec3f dataVectorBowlSides[MAX_NUM_PTS]; //the data point as an x, y, z vector
	ofMesh bowlSidesVisMesh;
	ofMesh bowlSidesCutMesh;
	float dataPointBowl[MAX_NUM_PTS]; //the data point (i.e. amplitude)
	ofVec3f dataVectorBowl[MAX_NUM_PTS]; //the data point as an x, y, z vector
	float bowlOriginX;
	float bowlOriginY;
	float bowlOriginZ;
	
	//Data points and meshes for cams
	ofMesh camCentreVisMesh;
	ofMesh camCentreCutMesh;
	float dataPointCentre[MAX_NUM_PTS]; //the data point (i.e. amplitude)
	ofVec3f dataVectorCentre[MAX_NUM_PTS]; //the data point as an x, y, z vector
	float camCentreOriginX;
	float camCentreOriginY;
	float camCentreOriginZ;
    
	
	ofMesh camFRVisMesh;
	ofMesh camFRCutMesh;
	float dataPointFR[MAX_NUM_PTS]; //the data point (i.e. amplitude)
	ofVec3f dataVectorFR[MAX_NUM_PTS]; //the data point as an x, y, z vector
	float camFROriginX;
	float camFROriginY;
	float camFROriginZ;
	
	ofMesh camFLVisMesh;
	ofMesh camFLCutMesh;
	float dataPointFL[MAX_NUM_PTS]; //the data point (i.e. amplitude)
	ofVec3f dataVectorFL[MAX_NUM_PTS]; //the data point as an x, y, z vector
	float camFLOriginX;
	float camFLOriginY;
	float camFLOriginZ;
	
	ofMesh camFCVisMesh;
	ofMesh camFCCutMesh;
	float dataPointFC[MAX_NUM_PTS]; //the data point (i.e. amplitude)
	ofVec3f dataVectorFC[MAX_NUM_PTS]; //the data point as an x, y, z vector
	float camFCOriginX;
	float camFCOriginY;
	float camFCOriginZ;
	
	ofMesh camBRVisMesh;
	ofMesh camBRCutMesh;
	float dataPointBR[MAX_NUM_PTS]; //the data point (i.e. amplitude)
	ofVec3f dataVectorBR[MAX_NUM_PTS]; //the data point as an x, y, z vector
	float camBROriginX;
	float camBROriginY;
	float camBROriginZ;
	
	ofImage cogSurface;
	
	ofCylinderPrimitive centreAxle;
	ofCylinderPrimitive frontAxle;
	ofCylinderPrimitive camBackAxle;
	ofCylinderPrimitive guideRod;
	ofCylinderPrimitive pushRodCentre;
	ofCylinderPrimitive pushRodFR;
	ofCylinderPrimitive pushRodFL;
	ofCylinderPrimitive pushRodFC;
	
	float camAmpOld;
	int bowlCorners;
	float bowlBaseRadius;
	float bowlTopRadius;
	float bowlHeight;
	
	float pushRodRadius;
	float pushRodHeight;
	float pushRodTop;
	
    
	float rotationHz;
	
	
	int testPoints;
	int coreWidth;
	int maxAmplitude;
	int drawnCam;
	float nowTime;
	float rotationDegrees;
	int n;
	int exported;
	
	int mouseXOld; //used for dragging around the screen
	float nicePicRotate;
	//ofLine littleKine;
	
    // ofxDxfExport myDxf;
    
	//easy cam setup:
	bool bShowHelp;
	ofEasyCam camera; // add mouse controls for camera movement
    
    
};

//Universal function which sets normals
//for the triangle mesh
void setNormals( ofMesh &mesh );
