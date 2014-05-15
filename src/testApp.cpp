#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    
    setupGUI();
    
    ofEnableSmoothing();
    ofSetVerticalSync(true);
	ofBackground(255);
	ofSetFrameRate(60);
	ofEnableDepthTest();
	camera.setDistance(1000.0);
	
	textColour = ofColor(50.0);
	camCentreColour = ofColor(200.0, 150.0, 150.0, 150.0);
	bowlColour = ofColor(80.0, 80.0, 240.0, 150.0);
	bowlSidesColour = ofColor(240.0, 180.0, 200.0, 120.0);
	camFRColour = ofColor(150.0, 200.0, 150.0, 150.0);
	camFLColour = ofColor(150.0, 150.0, 200.0, 150.0);
	camFCColour = ofColor(170.0, 170.0, 170.0, 150.0);
	axleColour = ofColor(100.0, 100.0, 100.0, 20.0);
	pushRodColour =ofColor(100.0, 100.0, 100.0, 100.0);
	
	testPoints= 200;
	coreWidth = 100.0;
	camAmpOld = 1.0;
    
	maxAmplitude = 50.0;
	
	pushRodRadius = 2.0;
	pushRodHeight = 400.0;
	pushRodTop = 0.0;
	
    rom1CamCentreOrigin = ofVec3f(500.0,700,-100);
    rom2CamCentreOrigin = ofVec3f((ofGetWidth() * 0.5) + 150.0,700.0,200.0);
    rom3CamCentreOrigin = ofVec3f((ofGetWidth() * 0.5) -150.0,700.0,200.0);
    romVCamCentreOrigin = ofVec3f((ofGetWidth() * 0.5),700.0,200.0);
  
    
    rom1Cam.setupPts("Reverse.xml", rom1CamCentreOrigin);
    rom2Cam.setupPts("Reverse.xml", rom2CamCentreOrigin);
    rom3Cam.setupPts("Reverse.xml", rom3CamCentreOrigin);
    romVCam.setupPts("Reverse.xml", romVCamCentreOrigin);
    
    
	/*camFROriginX =  (ofGetWidth() * 0.5) + 150.0;
	camFROriginY = 700.0;
	camFROriginZ = 200.0;*/
    /*
	camFLOriginX =  (ofGetWidth() * 0.5) -150.0;
	camFLOriginY = 700.0;
	camFLOriginZ = 200.0;
	*/
	camFCOriginX =  (ofGetWidth() * 0.5);
	camFCOriginY = 700.0;
	camFCOriginZ = 200.0;
	
	camBROriginX =  (ofGetWidth() * 0.5) +100.0;
	camBROriginY = 750.0;
	camBROriginZ = -330.0;
	
	bowlCorners = 12;
	bowlBaseRadius = 250.0;
	bowlTopRadius = 280.0;
	bowlHeight = 60.0;
	bowlOriginX = rom1CamCentreOrigin.x;
	bowlOriginY = 0.0;
	bowlOriginZ = 0.0;
	//camPts = rom1Cam.setupPts("Reverse.xml", rom1CamCentreOrigin);
	
	drawnCam = 0;
	rotationHz = 0.01;
	n=0;
	exported=0;
	
	mouseXOld = (int)(ofGetWidth() * 0.5);
	nicePicRotate = -30.0;

//	camCentreVisMesh.enableColors();
	
	cogSurface.loadImage( "sunflower.png" );

	nowTime = ofGetElapsedTimef();
	rotationDegrees = 0.0;
	
	//make cams so they're ready to be drawn
	//designCentreCam(camPts);
	designBowl();
	designFRCam();
	designFLCam();
	designFCCam();
   
}

void testApp::draw() {
	
	ofEnableDepthTest(); //Enable z-buffering
	ofBackground(255); 	//Set a background
	ofPushMatrix();
    
	ofSetColor(textColour);
	
    ofPushMatrix();
	//easyCam
	camera.begin();
	ofRotateY(nicePicRotate);
	//camera.disableMouseInput();
	
	ofScale(1,-1,1);
	niceLight.enable(); //Enabling light source
	ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    ofPushMatrix();
    ofRotateZ(90);
    ofTranslate(0,0,200);
    //ofDrawGridPlane(1000);
    ofPopMatrix();
	
    drawCentreCamAxle();
    drawFrontCamAxle();
	//drawBackCamAxle();
	//drawCams();
    //drawCentreCam();
    rom1Cam.draw(ofColor(255,0,0,125),true);
    rom2Cam.draw(ofColor(255,255,0,125),true);
    rom3Cam.draw(ofColor(0,0,255,125), true);
    romVCam.draw(ofColor(40,40,40,125),true);
	//drawFRCam();
	//drawFLCam();
	//drawFCCam();
	//drawPushRods();
	drawBowl();
	//drawGuideRods();
	
    
	
	camera.end();
	ofPopMatrix();
    ofPopMatrix();
    /*ofPushStyle();
    stringstream str;
    str << "Cam Watcher" << endl;
    str << "Current Number of Cams: " << 3 << endl;
    str << "Current Rotation Angle: " << rotationDegrees << endl;
    str << "Viewing Angle: " << ofToString (nicePicRotate) << " degrees" << endl;
    str << testRodPos << endl;
    str << camReportRadius << endl;
    
    ofSetColor(255, 255, 255, 255);
    ofDrawBitmapStringHighlight(str.str(), 5,15);
    ofPopStyle();*/
}
//--------------------------------------------------------------
void testApp::update()
{
    rotationDegrees = rotationDegrees + 360.0 * rotationHz/20.0;
	rom1Cam.update(rotationDegrees);
    rom2Cam.update(rotationDegrees);
    rom3Cam.update(rotationDegrees);
    romVCam.update(rotationDegrees);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key) {
   /*
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
        case 's':
            
            break;
        case 'w':
            
            break;
        case '1':
            
            break;
        case '2':
            
            break;
        case '3':
            
            break;
        case '4':
            
            break;
			
		case ' ':  //spacebar sets rotation to zero
			nicePicRotate = 0.0;
			break;
		default:
			break;
	}
    */
}
//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
    
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
	
}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    
	if (_camRot == true) {
    if (x > mouseXOld) nicePicRotate = nicePicRotate + 1.5;
	if (x < mouseXOld) nicePicRotate = nicePicRotate - 1.5;
	mouseXOld = x;
    }
    else
    {
        
    }
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    
    
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    
}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    
}
//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
    
}
//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
    
    
}
//--------------------------------------------------------------
void testApp::setupGUI()
{
    gui = new ofxUICanvas(0,38,800,800);
    gui->setName("Default");
    gui->setTheme(OFX_UI_THEME_HAYLOCK);
    gui->addWidgetDown(new ofxUILabel("Default", OFX_UI_FONT_LARGE));
    gui->addWidgetDown(new ofxUILabelToggle("Use Camera",false,LENGTH/2,30,OFX_UI_FONT_SMALL));
    gui->addWidgetRight(new ofxUILabelToggle("Stop Camera",false,LENGTH/2,30,OFX_UI_FONT_SMALL));
    gui->addWidgetRight(new ofxUILabelButton("Reset Camera",false,LENGTH/2,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabelToggle("Hide Preview",true,LENGTH,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabelToggle("Hide Live",true,LENGTH,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabel("Play Speed Millis", OFX_UI_FONT_SMALL));
    gui->addWidgetRight(new ofxUINumberDialer(0, 2, 0.010, 3, "ROT_SPEED", OFX_UI_FONT_MEDIUM));
    ofAddListener(gui->newGUIEvent,this, &testApp::guiEvent);
    gui->autoSizeToFitWidgets();
    gui->setVisible(true);
    
    guiImport = new ofxUICanvas(0,38,800,800);
    guiImport->setName("Import");
    guiImport->setTheme(OFX_UI_THEME_HAYLOCK);
    guiImport->addWidgetDown(new ofxUILabel("Import", OFX_UI_FONT_LARGE));
    ofAddListener(guiImport->newGUIEvent,this, &testApp::guiEvent);
    guiImport->autoSizeToFitWidgets();
    guiImport->setVisible(false);
    
    guiTab = new ofxUITabBar();
    guiTab->setTheme(OFX_UI_THEME_HAYLOCK);
    guiTab->setWidth(ofGetWidth());
    guiTab->setHeight(30);
    guiTab->addWidgetRight(new ofxUILabel("Cam Visualisation",OFX_UI_FONT_LARGE));
    guiTab->addFPS(OFX_UI_FONT_LARGE);
    guiTab->addCanvas(gui);
    guiTab->addCanvas(guiImport);

    ofAddListener(guiTab->newGUIEvent, this, &testApp::guiEvent);
    
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
    cout << e.getName() << endl;
    if (e.getName() == "Import")
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
        guiImport->setVisible(toggle->getValue());
    }
    else if(e.getName() == "Default")
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
        gui->setVisible(toggle->getValue());
    }
    else if (e.getName() == "Use Camera")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _camRot= toggle->getValue();
    }
    else if (e.getName() == "Stop Camera")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _camRot= toggle->getValue();
    }
    else if (e.getName() == "Reset Camera")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _camRot= toggle->getValue();
    }
    else if (e.getName() == "Hide Preview")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
  
    }
    else if (e.getName() == "Hide Live")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        
    }
    else if (e.getName() == "ROT_SPEED")
    {
        ofxUINumberDialer * dial = (ofxUINumberDialer *) e.widget;
        rotationHz = dial->getValue();
    }
}

//Draw the centre cam axle
//This runs along y=camCentreOriginY, z = 0
void testApp::drawCentreCamAxle()
{
	ofSetColor(axleColour);
	centreAxle.set(6.0, ofGetWidth()-100.0); //radius and height
	
	ofPushMatrix();
    ofTranslate((ofGetWidth() -100) * 0.5, rom1CamCentreOrigin.y, rom1CamCentreOrigin.z);//move pivot to centre of shape
    ofRotateZ(90.0);//rotate from centre
    centreAxle.draw();
	ofPopMatrix();
}


//Draw the front cam axle
//This runs along y=camFOriginY, z = amFOriginZ
void testApp::drawFrontCamAxle(){
	
	ofSetColor(axleColour);
	frontAxle.set(6.0, ofGetWidth()-100.0); //radius and height
	
	ofPushMatrix();
	ofTranslate((ofGetWidth() -100) * 0.5, rom2CamCentreOrigin.y, rom2CamCentreOrigin.z);//move pivot to centre of shape
	ofRotateZ(90.0);//rotate from centre
	frontAxle.draw();
	ofPopMatrix();
}
//This runs along y=camFLOriginY, z = 0
/*void testApp::drawGuideRods(){
	
	guideRod.set(6.0, 50.0); //radius and height
	
	
	//Draw guide rod for centre cam
	ofSetColor(camCentreColour.r,camCentreColour.g, camCentreColour.b, 60.0);
	ofPushMatrix();
    ofTranslate(camCentreOrigin.x, camCentreOrigin.y - 300.0, camCentreOrigin.z);//move pivot to centre of shape
    guideRod.draw();
	ofPopMatrix();
	
	//Draw guide rod for FR
	ofSetColor(camFRColour.r,camFRColour.g, camFRColour.b, 60.0);
	ofPushMatrix();
	ofTranslate(camFROriginX, camFROriginY - 300.0, camFROriginZ);//move pivot to centre of shape
	guideRod.draw();
	ofPopMatrix();
	
	//Draw guide rod for FL
	ofSetColor(camFLColour.r,camFLColour.g, camFLColour.b, 60.0);
	ofPushMatrix();
	ofTranslate(camFLOriginX, camFLOriginY - 300.0, camFLOriginZ);//move pivot to centre of shape
	guideRod.draw();
	ofPopMatrix();
	
	//Draw guide rod for FC
	ofSetColor(camFCColour.r,camFCColour.g, camFCColour.b, 60.0);
	ofPushMatrix();
	ofTranslate(camFCOriginX, camFCOriginY - 300.0, camFCOriginZ);//move pivot to centre of shape
	guideRod.draw();
	ofPopMatrix();
	
	
}
*/

//Draw the front cam axle
//This runs along y=camFLOriginY, z = 0
void testApp::drawBackCamAxle(){
	
	/*ofSetColor(axleColour);
     camBackAxle.set(6.0, ofGetWidth()-100.0); //radius and height
     
     ofPushMatrix();
     ofTranslate((ofGetWidth() -100)* 0.5, camBLOriginY, camBLOriginZ);//move pivot to centre of shape
     ofRotateZ(90.0);//rotate from centre
     camBackAxle.draw();
     ofPopMatrix();*/
}

//Draw and rotate front right
void testApp::drawFRCam(){
	
	//rotationDegrees = rotationDegrees + 360.0 * rotationHz/30.0;
	
    
	//Front right cam
	ofSetColor(camFRColour);
	ofPushMatrix();
	ofTranslate(camFROriginX, camFROriginY, camFROriginZ);//move pivot to centre of shape
	ofRotateX(rotationDegrees);//rotate from centre
	ofRotateY(90.0);
	ofTranslate(-camFROriginX, -camFROriginY, -camFROriginZ);//move pivot to centre of shape
	camFRVisMesh.draw();
	ofPopMatrix();
	
    
}

//Draw and rotate front left cam
void testApp::drawFLCam(){
	
	//rotationDegrees = rotationDegrees + 360.0 * rotationHz/30.0;
	
	
	//Front right cam
	ofSetColor(camFLColour);
	ofPushMatrix();
	ofTranslate(camFLOriginX, camFLOriginY, camFLOriginZ);//move pivot to centre of shape
	ofRotateX(rotationDegrees);//rotate from centre
	ofRotateY(90.0);
	ofTranslate(-camFLOriginX, -camFLOriginY, -camFLOriginZ);//move pivot to centre of shape
	camFLVisMesh.draw();
	ofPopMatrix();
	
}

//Draw and rotate front centre cam
void testApp::drawFCCam(){
	
	//rotationDegrees = rotationDegrees + 360.0 * rotationHz/30.0;
	
	
	//Front right cam
	ofSetColor(camFCColour);
	ofPushMatrix();
	ofTranslate(camFCOriginX, camFCOriginY, camFCOriginZ);//move pivot to centre of shape
	ofRotateX(rotationDegrees);//rotate from centre
	ofRotateY(90.0);
	ofTranslate(-camFCOriginX, -camFCOriginY, -camFCOriginZ);//move pivot to centre of shape
	camFCVisMesh.draw();
	ofPopMatrix();
	
}


/*Draw and rotate all the cams
void testApp::drawCentreCam(){
	
	rotationDegrees = rotationDegrees + 360.0 * rotationHz/20.0;
	//Centre cam
	ofSetColor(camCentreColour);
	ofPushMatrix();
    
    ofTranslate(camCentreOriginX, camCentreOriginY, camCentreOriginZ);//move pivot to centre of shape
    ofRotateX(rotationDegrees);//rotate from centre
    ofRotateY(90.0);
    //ofRotateX(180);
    ofTranslate(-camCentreOriginX, -camCentreOriginY, -camCentreOriginZ);//move pivot to centre of shape
    
    ofScale(1,1,1);
    camCentreVisMesh.draw();
	
    ofPopMatrix();
}
*/

//Draw the bowl
void testApp::drawBowl(){
	
	//Bowl bass
    ofDrawBitmapString("push rod: " + ofToString(pushRodTop), 5, 65);
	ofPushMatrix();
	
	//ofTranslate(bowlOriginX, camCentreRadius, bowlOriginZ);//move pivot to centre of shape
	ofTranslate(0, pushRodTop, 0);//move pivot to centre of shape
	//ofRotateX(12.0);//rotate from centre
	//ofRotateY(90.0);
	
	ofSetColor(bowlColour);
	bowlVisMesh.draw();
	
	ofSetColor(bowlSidesColour);
	bowlSidesVisMesh.draw();
	ofPopMatrix();
	
}

/*
void testApp::drawPushRods(){
	
	//Find the point on the cam that's active
	float angleToFind = fmod(270.0 - rotationDegrees, 360.0);
	int indexToFind = (int)( (angleToFind * (1.0 * (testPoints))/360.0)) - 1;
	if (indexToFind < 0) indexToFind = indexToFind + testPoints;
	ofDrawBitmapString("Cam rotation: " + ofToString(angleToFind), 5, 45);
    
    //Find the point on the cam that's active
	float tangleToFind = fmod(270.0 - rotationDegrees, 360.0);
	int tindexToFind = (int)( (tangleToFind * (1.0 * camPts.size())/360.0)) - 1;
	if (tindexToFind < 0) tindexToFind = tindexToFind + camPts.size();
    
	
	//Draw the centre push rod
	ofSetColor(pushRodColour);
	float camRadiuss = dataPointCentre[tindexToFind];
	pushRodCentre.set(pushRodRadius, pushRodHeight); //radius an height
	pushRodCentre.setPosition(camCentreOriginX, camCentreOriginY - (0.5 * pushRodHeight) - camRadiuss, camCentreOriginZ);
	pushRodCentre.draw();
	pushRodTop = camCentreOriginY - pushRodHeight - camRadiuss;
    testRodPos = ofToString(pushRodTop) + " " + ofToString(camRadiuss);
	
	//Draw FR pushrod
	float camRadius = dataPointFR[indexToFind];
	pushRodFR.set(pushRodRadius, pushRodHeight); //radius an height
	pushRodFR.setPosition(camFROriginX, camFROriginY - (0.5 * pushRodHeight) - camRadius, camFROriginZ);
	pushRodFR.draw();
	pushRodTop = camFROriginY - pushRodHeight - camRadius;
	
	//Draw FL pushrod
	camRadius = dataPointFL[indexToFind];
	pushRodFL.set(pushRodRadius, pushRodHeight); //radius an height
	pushRodFL.setPosition(camFLOriginX, camFLOriginY - (0.5 * pushRodHeight) - camRadius, camFLOriginZ);
	pushRodFL.draw();
	pushRodTop = camFROriginY - pushRodHeight - camRadius;
	camReportRadius = ofToString(camRadius);
	
	//Draw FC pushrod
	float pushRodFCHeight = pushRodHeight - 120.0;
	float pushRodFCRadius = pushRodRadius + 2.0;
	camRadius = dataPointFC[indexToFind];
	pushRodFC.set(pushRodFCRadius, pushRodFCHeight); //radius an height
	pushRodFC.setPosition(camFCOriginX, camFCOriginY - (0.5 * pushRodFCHeight) - camRadius, camFCOriginZ);
	pushRodFC.draw();
	pushRodTop = camFCOriginY - pushRodFCHeight - camRadius;
}
*/



//Design the bowl
void testApp::designBowl(){
	
	
	
	//work out the value of each dataPoint of the base
	for (int i=0; i<bowlCorners; i++)
	{
		
		float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * bowlCorners);
		float camX = bowlOriginX + (bowlBaseRadius * sin(angle));
		float camY = bowlOriginY;
		float camZ = bowlOriginZ + (bowlBaseRadius * cos(angle));
		
		ofVec3f thisPoint(camX, camY, camZ);
		dataVectorBowl[i]=thisPoint;
		
		//making the simple cut mesh
		bowlCutMesh.addVertex(thisPoint);
	}
	
	
	//now work out the value of each dataPoint of the top
	for (int i=0; i<bowlCorners; i++)
	{
		
		float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * bowlCorners);
		float camX = bowlOriginX + (bowlTopRadius * sin(angle));
		float camY = bowlOriginY - bowlHeight;
		float camZ = bowlOriginZ + (bowlTopRadius * cos(angle));
		
		ofVec3f thisPoint(camX, camY, camZ);
		dataVectorBowl[i+bowlCorners]=thisPoint;
		
		
		//making the simple cut mesh
		bowlCutMesh.addVertex(thisPoint);
	}
	
	
	
	//now use these test points to make a mesh using triangles:
	
	//the bowl origin
	ofVec3f bowlCentre(bowlOriginX, bowlOriginY, bowlOriginZ);
	
	
	//base of bowl
	for (int i=0; i<bowlCorners; i++)
	{
		bowlVisMesh.addVertex(bowlCentre);
		
		
		bowlVisMesh.addVertex(dataVectorBowl[i]);
		if (i<bowlCorners-1) bowlVisMesh.addVertex(dataVectorBowl[(i+1)]);
		else bowlVisMesh.addVertex(dataVectorBowl[0]);
	}
	
	
	
	//sides of
	for (int i=0; i<bowlCorners; i++)
	{
        
		
		bowlSidesVisMesh.addVertex(dataVectorBowl[i]);
		bowlSidesVisMesh.addVertex(dataVectorBowl[(i+bowlCorners)]);
		if (i<bowlCorners-1) bowlSidesVisMesh.addVertex(dataVectorBowl[(i+bowlCorners+1)]);
		else bowlSidesVisMesh.addVertex(dataVectorBowl[i + 1]);
		
		bowlSidesVisMesh.addVertex(dataVectorBowl[i]);
		if (i<bowlCorners-1)
		{
			bowlSidesVisMesh.addVertex(dataVectorBowl[i +1]);
			bowlSidesVisMesh.addVertex(dataVectorBowl[i +bowlCorners+1]);
		}
		else
		{
			bowlSidesVisMesh.addVertex(dataVectorBowl[0]);
			bowlSidesVisMesh.addVertex(dataVectorBowl[bowlCorners]);
		}
        
	}
	
	//Then set up the indices for the mesh
	bowlSidesVisMesh.setupIndicesAuto();
	//setNormals(camFLVisMesh);			//Set normals to the surface
	
	
	
}


/*Design the FL cam
void testApp::designCentreCam(vector<ofVec3f> pts)
{
    camCentreVisMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    //work out the value of each dataPointFL
	for (int i=0; i<pts.size(); i++)
	{
		//float camAmplitude = (coreWidth + 0.5 * maxAmplitude *
						//	  (1.0 + sin(2.0 * (1.0 *pts[i].x) * M_PI * pts.size() * 0.0001)));
        
		dataPointCentre[i] = pts[i].z;
    
		//float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * pts.size());
		//float camX = camCentreOriginX + (camAmplitude * cos(angle));
		//float camY = camCentreOriginY + (camAmplitude * sin(angle));
		//float camZ = camCentreOriginZ;
		
		//ofVec3f thisPoint(camX, camY, camZ);
		//dataVectorCentre[i] = thisPoint;
		
		//making the simple cut mesh
		//camCentreCutMesh.addVertex(thisPoint);
	}
	
	
	//now use these test points to make a mesh using triangles:
	
	//the cog origin
	ofVec3f camCentrePoint(camCentreOriginX, camCentreOriginY, camCentreOriginZ);
	
	
	//now draw the cam triangle by triangle
	for (int i=0; i<pts.size(); i++)
	{
        dataVectorCentre[i] = ofVec3f(pts[i].x,pts[i].y,camCentreOriginZ);
        camCentreVisMesh.addVertex(camCentrePoint);
        
        camCentreVisMesh.addVertex(dataVectorCentre[i]);
        
        if (i>0) camCentreVisMesh.addVertex(dataVectorCentre[i-1]);
        else camCentreVisMesh.addVertex(dataVectorCentre[i
                                                         ]);
	}
	
	//Then set up the indices for the mesh
	camCentreVisMesh.setupIndicesAuto();
	//setNormals(camFLVisMesh);			//Set normals to the surface

}
*/
//Design the FR cam
void testApp::designFRCam(){
	
    
	//work out the value of each dataPointFL
	for (int i=0; i<testPoints; i++)
	{
		
		//float camAmplitude = (coreWidth + 0.5 * maxAmplitude *
        // (1.0 + sin(2.0 * (1.0 *i) * M_PI * testPoints * 0.00015)));
		
		float camAmplitude = (coreWidth + 0.5 * maxAmplitude *
							  (1.0 + sin(2.0 * (1.0 *i) * M_PI * testPoints * 0.0001)));
		
		
//		/dataPointFR[i] = camAmplitude;
		
		float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * testPoints);
		float camX = camFROriginX + (camAmplitude * cos(angle));
		float camY = camFROriginY + (camAmplitude * sin(angle));
		float camZ = camFROriginZ;
		
		ofVec3f thisPoint(camX, camY, camFROriginZ);
		dataVectorFR[i]=thisPoint;
		
		//making the simple cut mesh
		camFRCutMesh.addVertex(thisPoint);
	}
	
	
	//now use these test points to make a mesh using triangles:
	
	//the cog origin
	ofVec3f camCentre(camFROriginX, camFROriginY, camFROriginZ);
	
	
	//now draw the cam triangle by triangle
	for (int i=0; i<testPoints; i++)
	{
		camFRVisMesh.addVertex(camCentre);
		
		
		camFRVisMesh.addVertex(dataVectorFR[i]);
		if (i>0) camFRVisMesh.addVertex(dataVectorFR[(i-1)]);
		else camFRVisMesh.addVertex(dataVectorFR[testPoints-1]);
	}
	
	//Then set up the indices for the mesh
	camFRVisMesh.setupIndicesAuto();
	//setNormals(camFLVisMesh);			//Set normals to the surface
	
	
	
}


//Design the FR cam
void testApp::designFLCam(){
	
	
	//work out the value of each dataPointFL
	for (int i=0; i<testPoints; i++)
	{
		float camAmplitude = (coreWidth + 0.5 * maxAmplitude *
							  (1.0 + sin(2.0 * (1.0 *i) * M_PI * testPoints * 0.00015)));
		
		dataPointFL[i] = camAmplitude;
		
		float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * testPoints);
		float camX = camFLOriginX + (camAmplitude * cos(angle));
		float camY = camFLOriginY + (camAmplitude * sin(angle));
		float camZ = camFLOriginZ;
		
		ofVec3f thisPoint(camX, camY, camFLOriginZ);
		dataVectorFL[i]=thisPoint;
		
		//making the simple cut mesh
		camFLCutMesh.addVertex(thisPoint);
	}
	
	
	//now use these test points to make a mesh using triangles:
	
	//the cog origin
	ofVec3f camCentre(camFLOriginX, camFLOriginY, camFLOriginZ);
	
	
	//now draw the cam triangle by triangle
	for (int i=0; i<testPoints; i++)
	{
		camFLVisMesh.addVertex(camCentre);
		
		
		camFLVisMesh.addVertex(dataVectorFL[i]);
		if (i>0) camFLVisMesh.addVertex(dataVectorFL[(i-1)]);
		else camFLVisMesh.addVertex(dataVectorFL[testPoints-1]);
	}
	
	//Then set up the indices for the mesh
	camFLVisMesh.setupIndicesAuto();
	//setNormals(camFLVisMesh);			//Set normals to the surface
	
	
	
}


//Design the FR cam
void testApp::designFCCam(){
	
	
	//work out the value of each dataPointFL
	for (int i=0; i<testPoints; i++)
	{
		float camAmplitude = (coreWidth + 0.5 * maxAmplitude *
							  (1.0 + sin(2.0 * (1.0 *i) * M_PI * testPoints * 0.00004)));
		
		dataPointFC[i] = camAmplitude;
		
		float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * testPoints);
		float camX = camFCOriginX + (camAmplitude * cos(angle));
		float camY = camFCOriginY + (camAmplitude * sin(angle));
		float camZ = camFCOriginZ;
		
		ofVec3f thisPoint(camX, camY, camFCOriginZ);
		dataVectorFC[i]=thisPoint;
		
		//making the simple cut mesh
		camFCCutMesh.addVertex(thisPoint);
	}
	
	
	//now use these test points to make a mesh using triangles:
	
	//the cog origin
	ofVec3f camCentre(camFCOriginX, camFCOriginY, camFCOriginZ);
	
	
	//now draw the cam triangle by triangle
	for (int i=0; i<testPoints; i++)
	{
		camFCVisMesh.addVertex(camCentre);
		
		
		camFCVisMesh.addVertex(dataVectorFC[i]);
		if (i>0) camFCVisMesh.addVertex(dataVectorFC[(i-1)]);
		else camFCVisMesh.addVertex(dataVectorFC[testPoints-1]);
	}
	
	//Then set up the indices for the mesh
	camFCVisMesh.setupIndicesAuto();
	//setNormals(camFLVisMesh);			//Set normals to the surface
	
	
	
}
//Design the BR cam
void testApp::designCamBR(){
	
	
	//work out the value of each dataPointFL
	for (int i=0; i<testPoints; i++)
	{
		float camAmplitude = (coreWidth + 0.5 * maxAmplitude *
							  (1.0 + sin(2.0 * (1.0 *i) * M_PI * testPoints * 0.00015)));
		
		dataPointBR[i] = camAmplitude;
		
		float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * testPoints);
		float camX = camBROriginX + (camAmplitude * cos(angle));
		float camY = camBROriginY + (camAmplitude * sin(angle));
		float camZ = camBROriginZ;
		
		ofVec3f thisPoint(camX, camY, camBROriginZ);
		dataVectorBR[i]=thisPoint;
		
		//making the simple cut mesh
		camBRCutMesh.addVertex(thisPoint);
	}
	
	
	//now use these test points to make a mesh using triangles:
	
	//the cog origin
	ofVec3f camCentre(camBROriginX, camBROriginY, camBROriginZ);
	
	
	//now draw the cam triangle by triangle
	for (int i=0; i<testPoints; i++)
	{
		camBRVisMesh.addVertex(camCentre);
		
		
		camBRVisMesh.addVertex(dataVectorBR[i]);
		if (i>0) camBRVisMesh.addVertex(dataVectorBR[(i-1)]);
		else camBRVisMesh.addVertex(dataVectorBR[testPoints-1]);
	}
	
	//Then set up the indices for the mesh
	camBRVisMesh.setupIndicesAuto();
	//setNormals(camFLVisMesh);			//Set normals to the surface
	
	
	
}



///Universal function which sets normals for the triangle mesh
void setNormals( ofMesh &mesh ){
	
	//The number of the vertices
	int nV = mesh.getNumVertices();
	
	//The number of the triangles
	int nT = mesh.getNumIndices() / 3;
	
	vector<ofPoint> norm( nV );		//Array for the normals
	
	//Scan all the triangles. For each triangle add its
	//normal to norm's vectors of triangle's vertices
	for (int t=0; t<nT; t++) {
		
		//Get indices of the triangle t
		int i1 = mesh.getIndex( 3 * t );
		int i2 = mesh.getIndex( 3 * t + 1 );
		int i3 = mesh.getIndex( 3 * t + 2 );
		
		//Get vertices of the triangle
		const ofPoint &v1 = mesh.getVertex( i1 );
		const ofPoint &v2 = mesh.getVertex( i2 );
		const ofPoint &v3 = mesh.getVertex( i3 );
		
		//Compute the triangle's normal
		ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
		
		//Accumulate it to norm array for i1, i2, i3
		norm[ i1 ] += dir;
		norm[ i2 ] += dir;
		norm[ i3 ] += dir;
	}
	
	//Normalize the normal's length
	for (int i=0; i<nV; i++) {
		norm[i].normalize();
	}
	
	//Set the normals to mesh
	mesh.clearNormals();
	mesh.addNormals( norm );
}

