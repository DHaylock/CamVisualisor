#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "camClass.h"

#define MAX_NUM_PTSs 2000
#define LENGTH 255

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
    void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
    // David's Methods
    void setupGUI();
    void guiEvent(ofxUIEventArgs &e);
    void setupValues();
    void setupCams();
    void updateGUIValues();
    string testRodPos;
    string camReportRadius;
    
    vector<ofVec3f> camPts;
    
    ofxUICanvas *gui;
    ofxUITabBar *guiTab;
    ofxUICanvas *guiCams;
    ofxUICanvas *guiCamera;
    
    ofImage *colorSampler;
    
    Cam rom1Cam;
    Cam rom2Cam;
    Cam rom3Cam;
    Cam romVCam;
    
    ofVec3f rom1CamCentreOrigin;
    ofVec3f rom2CamCentreOrigin;
    ofVec3f rom3CamCentreOrigin;
    ofVec3f romVCamCentreOrigin;
    
    float camRotAngle;
    float increaseAngleBy;
    
    bool _camRot;
    bool _drawBowl;
    bool _drawAxels;
    bool _drawBox;
    bool _drawCams;
    bool _resetCamera;
    bool _useCamera;
    bool _AutoCamera;
    bool _lighting;
    bool _importNewCam1;
    bool _importNewCam2;
    bool _importNewCam3;
    bool _importNewCam4;
    
    ofColor rom1CamCol;
    ofColor rom2CamCol;
    ofColor rom3CamCol;
    ofColor romVCamCol;
    
    // Sarah's Methods
    void turnMainCam();
	void drawCentreCamAxle();
	void drawFrontCamAxle();
	void drawBackCamAxle();
	void drawBowl();
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
	float dataPointBowlSides[MAX_NUM_PTSs]; //the data point (i.e. amplitude)
	ofVec3f dataVectorBowlSides[MAX_NUM_PTSs]; //the data point as an x, y, z vector
	ofMesh bowlSidesVisMesh;
	ofMesh bowlSidesCutMesh;
	float dataPointBowl[MAX_NUM_PTSs]; //the data point (i.e. amplitude)
	ofVec3f dataVectorBowl[MAX_NUM_PTSs]; //the data point as an x, y, z vector
	float bowlOriginX;
	float bowlOriginY;
	float bowlOriginZ;

	ofImage cogSurface;
	
	ofCylinderPrimitive centreAxle;
	ofCylinderPrimitive frontAxle;
	ofCylinderPrimitive camBackAxle;
	;
	
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
