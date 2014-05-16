#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    setupGUI();
    setupValues();
    setupCams();
    
    ofEnableSmoothing();
    ofSetVerticalSync(true);
	ofBackground(255);
	ofSetFrameRate(60);
	ofEnableDepthTest();
	camera.setDistance(1500.0);
}
//--------------------------------------------------------------
void testApp::update()
{
    rotationDegrees = rotationDegrees + 360.0 * rotationHz/20.0;
	rom1Cam.update(rotationDegrees);
    rom2Cam.update(rotationDegrees);
    rom3Cam.update(rotationDegrees);
    romVCam.update(rotationDegrees);
    
    if (_AutoCamera == true)
    {
        camRotAngle += increaseAngleBy;
        
        if (camRotAngle >= 359) {
            camRotAngle = 0;
        }
    }
    
    updateGUIValues();
}
//--------------------------------------------------------------
void testApp::draw()
{
	ofEnableDepthTest(); //Enable z-buffering
	ofBackground(150); 	//Set a background
	ofPushMatrix();
    
	ofSetColor(textColour);
	
    ofPushMatrix();
	//easyCam
	camera.begin();
    if (_AutoCamera == true)
    {
        ofRotateY(camRotAngle);
    }
    else
    {
        ofRotateY(nicePicRotate);
    }
    
    ofPushMatrix();
    ofTranslate(0, -600,0);
    ofRotateZ(90);
    ofDrawGridPlane(1000);
    ofPopMatrix();
    if (_useCamera == false)
    {
        camera.disableMouseInput();
    }

	
	ofScale(1,-1,1);
	if (_lighting == true)
    {
        niceLight.enable(); //Enabling light source
    }
    else
    {
        niceLight.disable();
    }
    
	ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    ofPushMatrix();
    ofRotateZ(90);
    ofTranslate(0,0,200);
    ofPopMatrix();
	
    if (_drawCams == true)
    {
        rom1Cam.draw(rom1CamCol,true);
        rom2Cam.draw(rom2CamCol,true);
        rom3Cam.draw(rom3CamCol,true);
        romVCam.draw(romVCamCol,true);
    }
    
	if (_drawBowl == true)
    {
        drawBowl();
	}
    
    if (_drawAxels == true)
    {
        drawCentreCamAxle();
        drawBackCamAxle();
        drawFrontCamAxle();
    }
    
	camera.end();
	ofPopMatrix();
    ofPopMatrix();
    ofPopMatrix();

   /* ofPushMatrix();
    ofTranslate(-200, -450);
    rom1Cam.drawCamImage(ofPoint(ofGetWidth()-200, 10), rom1CamCol);
    rom2Cam.drawCamImage(ofPoint(ofGetWidth()-200, 410), rom2CamCol);
    ofPopMatrix();*/
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
   
	switch(key) {
		case 'h':
			guiTab->toggleVisible();
			break;
	}
}
//--------------------------------------------------------------
void testApp::exit()
{
    guiCams->saveSettings("GUI/camSettings.xml");
    gui->saveSettings("GUI/guiSetting.xml");
    //guiTab->saveSettings("GUI/guiTab.xml");
    delete guiCams;
    delete guiTab;
    delete gui;
    delete colorSampler;
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
    if (_importNewCam1 == true)
    {
        if (dragInfo.files.size() > 0) {
            rom1Cam.loadNewCam(dragInfo.files[0],rom1CamCentreOrigin);
        }
    }
    
    if (_importNewCam2 == true)
    {
        if (dragInfo.files.size() > 0) {
            rom2Cam.loadNewCam(dragInfo.files[0],rom2CamCentreOrigin);
        }
    }
   
    if (_importNewCam3 == true)
    {
        if (dragInfo.files.size() > 0) {
            rom3Cam.loadNewCam(dragInfo.files[0],rom3CamCentreOrigin);
        }
    }
    
    if (_importNewCam4 == true)
    {
        if (dragInfo.files.size() > 0) {
            romVCam.loadNewCam(dragInfo.files[0],romVCamCentreOrigin);
        }
    }
    else
    {
        cout << "Error: No Pts" << endl;
    }
}
//--------------------------------------------------------------
void testApp::updateGUIValues()
{
    ((ofxUINumberDialer *) gui->getWidget("CAM1_R"))->setValue(rom1Cam.whatIsCamRadiusAndPushRodTop().x);
    ((ofxUINumberDialer *) gui->getWidget("CAM2_R"))->setValue(rom2Cam.whatIsCamRadiusAndPushRodTop().x);
    ((ofxUINumberDialer *) gui->getWidget("CAM3_R"))->setValue(rom3Cam.whatIsCamRadiusAndPushRodTop().x);
    ((ofxUINumberDialer *) gui->getWidget("CAM4_R"))->setValue(romVCam.whatIsCamRadiusAndPushRodTop().x);
    ((ofxUINumberDialer *) gui->getWidget("CAM1_H"))->setValue(rom1Cam.whatIsCamRadiusAndPushRodTop().y);
    ((ofxUINumberDialer *) gui->getWidget("CAM2_H"))->setValue(rom2Cam.whatIsCamRadiusAndPushRodTop().y);
    ((ofxUINumberDialer *) gui->getWidget("CAM3_H"))->setValue(rom3Cam.whatIsCamRadiusAndPushRodTop().y);
    ((ofxUINumberDialer *) gui->getWidget("CAM4_H"))->setValue(romVCam.whatIsCamRadiusAndPushRodTop().y);
}
//--------------------------------------------------------------
void testApp::setupCams()
{
    rom1CamCentreOrigin = ofVec3f(500.0,700,-100);
    rom2CamCentreOrigin = ofVec3f((ofGetWidth() * 0.5) + 150.0,700.0,200.0);
    rom3CamCentreOrigin = ofVec3f((ofGetWidth() * 0.5) -150.0,700.0,200.0);
    romVCamCentreOrigin = ofVec3f((ofGetWidth() * 0.5),700.0,200.0);
    
    rom1Cam.loadCam("r7.xml", rom1CamCentreOrigin);
    rom2Cam.loadCam("r6.xml", rom2CamCentreOrigin);
    rom3Cam.loadCam("r9.xml", rom3CamCentreOrigin);
    romVCam.loadCam("UpCentre.xml", romVCamCentreOrigin);
}
//--------------------------------------------------------------
void testApp::setupValues()
{
    bowlCorners = 12;
	bowlBaseRadius = 250.0;
	bowlTopRadius = 280.0;
	bowlHeight = 60.0;
	bowlOriginX = rom1CamCentreOrigin.x;
	bowlOriginY = 0.0;
	bowlOriginZ = 0.0;
    camRotAngle = 0;
	coreWidth = 100.0;
	camAmpOld = 1.0;
    
	maxAmplitude = 50.0;
    
	drawnCam = 0;
	rotationHz = 0.01;
	n=0;
	exported=0;
	
    designBowl();
    
	mouseXOld = (int)(ofGetWidth() * 0.5);
	nicePicRotate = -30.0;
	increaseAngleBy = 0.5;
	cogSurface.loadImage( "sunflower.png" );
    
	nowTime = ofGetElapsedTimef();
	rotationDegrees = 0.0;
}
//--------------------------------------------------------------
void testApp::setupGUI()
{
    colorSampler = new ofImage();
    colorSampler->loadImage("GUI/colorSamplerImage.png");
    
    gui = new ofxUICanvas(0,38,590,600);
    gui->setName("Settings");
    gui->setTheme(OFX_UI_THEME_HAYLOCK);
    gui->addWidgetDown(new ofxUILabel("Settings", OFX_UI_FONT_LARGE));
    gui->addWidgetDown(new ofxUILabelToggle("Use Camera",false,LENGTH/1.5,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabelToggle("Auto Camera",false,LENGTH/1.5,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabelButton("Reset Camera",false,LENGTH/1.5,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabelToggle("Draw Bowl",false,LENGTH/1.5,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabelToggle("Draw Axels",true,LENGTH/1.5,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabelToggle("Draw Cams",true,LENGTH/1.5,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabelToggle("Draw Box",false,LENGTH/1.5,30,OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUILabelToggle("Draw Lighting",false,LENGTH/1.5,30,OFX_UI_FONT_SMALL));
    gui->addWidgetEastOf(new ofxUILabel("Cam 1 Radius", OFX_UI_FONT_MEDIUM),"Use Camera");
    gui->addWidgetEastOf(new ofxUINumberDialer(0, 500, 0.010, 3, "CAM1_R", OFX_UI_FONT_MEDIUM),"Cam 1 Radius");
    gui->addWidgetEastOf(new ofxUILabel("Cam 2 Radius", OFX_UI_FONT_MEDIUM),"Auto Camera");
    gui->addWidgetEastOf(new ofxUINumberDialer(0, 500, 0.010, 3, "CAM2_R", OFX_UI_FONT_MEDIUM),"Cam 2 Radius");
    gui->addWidgetEastOf(new ofxUILabel("Cam 3 Radius", OFX_UI_FONT_MEDIUM),"Reset Camera");
    gui->addWidgetEastOf(new ofxUINumberDialer(0, 500, 0.010, 3, "CAM3_R", OFX_UI_FONT_MEDIUM),"Cam 3 Radius");
    gui->addWidgetEastOf(new ofxUILabel("Cam 4 Radius", OFX_UI_FONT_MEDIUM),"Draw Bowl");
    gui->addWidgetEastOf(new ofxUINumberDialer(0, 500, 0.010, 3, "CAM4_R", OFX_UI_FONT_MEDIUM),"Cam 4 Radius");
    
    gui->addWidgetEastOf(new ofxUILabel("Cam 1 Pushrod H", OFX_UI_FONT_MEDIUM),"Draw Axels");
    gui->addWidgetEastOf(new ofxUINumberDialer(0, 1000, 0.010, 3, "CAM1_H", OFX_UI_FONT_MEDIUM),"Cam 1 Pushrod H");
    gui->addWidgetEastOf(new ofxUILabel("Cam 2 Pushrod H", OFX_UI_FONT_MEDIUM),"Draw Cams");
    gui->addWidgetEastOf(new ofxUINumberDialer(0, 1000, 0.010, 3, "CAM2_H", OFX_UI_FONT_MEDIUM),"Cam 2 Pushrod H");
    gui->addWidgetEastOf(new ofxUILabel("Cam 3 Pushrod H", OFX_UI_FONT_MEDIUM),"Draw Box");
    gui->addWidgetEastOf(new ofxUINumberDialer(0, 1000, 0.010, 3, "CAM3_H", OFX_UI_FONT_MEDIUM),"Cam 3 Pushrod H");
    gui->addWidgetEastOf(new ofxUILabel("Cam 4 Pushrod H", OFX_UI_FONT_MEDIUM),"Draw Lighting");
    gui->addWidgetEastOf(new ofxUINumberDialer(0, 1000, 0.010, 3, "CAM4_H", OFX_UI_FONT_MEDIUM),"Cam 4 Pushrod H");
    
    gui->addWidgetSouthOf(new ofxUILabel("Play Speed Millis", OFX_UI_FONT_MEDIUM),"Draw Lighting");
    gui->addWidgetRight(new ofxUINumberDialer(0, 2, 0.010, 3, "ROT_SPEED", OFX_UI_FONT_MEDIUM));
    ofAddListener(gui->newGUIEvent,this, &testApp::guiEvent);
    
    gui->setVisible(true);
    
    guiCams = new ofxUICanvas(0,38,590,600);
    guiCams->setName("Cams");
    guiCams->setTheme(OFX_UI_THEME_HAYLOCK);
    guiCams->addWidgetNorthOf(new ofxUILabel("Cams", OFX_UI_FONT_LARGE),"Cam 1 Color");
    guiCams->addWidgetDown(new ofxUIImageSampler(LENGTH/2, LENGTH/2, colorSampler, "CAM1_COL"));
    guiCams->addWidgetRight(new ofxUIImageSampler(LENGTH/2, LENGTH/2, colorSampler, "CAM2_COL"));
    guiCams->addWidgetRight(new ofxUIImageSampler(LENGTH/2, LENGTH/2, colorSampler, "CAM3_COL"));
    guiCams->addWidgetRight(new ofxUIImageSampler(LENGTH/2, LENGTH/2, colorSampler, "CAM4_COL"));
    guiCams->addWidgetNorthOf(new ofxUILabel("Cam 1 Color",OFX_UI_FONT_SMALL), "CAM1_COL");
    guiCams->addWidgetNorthOf(new ofxUILabel("Cam 2 Color",OFX_UI_FONT_SMALL), "CAM2_COL");
    guiCams->addWidgetNorthOf(new ofxUILabel("Cam 3 Color",OFX_UI_FONT_SMALL), "CAM3_COL");
    guiCams->addWidgetNorthOf(new ofxUILabel("Cam 4 Color",OFX_UI_FONT_SMALL), "CAM4_COL");
    guiCams->addWidgetSouthOf(new ofxUIIntSlider("Cam1Alpha",0,255,200,LENGTH/2,30), "CAM1_COL");
    guiCams->addWidgetSouthOf(new ofxUIIntSlider("Cam2Alpha",0,255,200,LENGTH/2,30), "CAM2_COL");
    guiCams->addWidgetSouthOf(new ofxUIIntSlider("Cam3Alpha",0,255,200,LENGTH/2,30), "CAM3_COL");
    guiCams->addWidgetSouthOf(new ofxUIIntSlider("Cam4Alpha",0,255,200,LENGTH/2,30), "CAM4_COL");
    guiCams->addWidgetDown(new ofxUILabelToggle("Import New 1",false,LENGTH/2,30,OFX_UI_FONT_SMALL));
    guiCams->addWidgetRight(new ofxUILabelToggle("Import New 2",false,LENGTH/2,30,OFX_UI_FONT_SMALL));
    guiCams->addWidgetRight(new ofxUILabelToggle("Import New 3",false,LENGTH/2,30,OFX_UI_FONT_SMALL));
    guiCams->addWidgetRight(new ofxUILabelToggle("Import New 4",false,LENGTH/2,30,OFX_UI_FONT_SMALL));
    ofAddListener(guiCams->newGUIEvent,this, &testApp::guiEvent);
    guiCams->autoSizeToFitWidgets();
    guiCams->setVisible(false);
    
    guiTab = new ofxUITabBar();
    guiTab->setTheme(OFX_UI_THEME_HAYLOCK);
    guiTab->setWidth(ofGetWidth());
    guiTab->setHeight(30);
    guiTab->addWidgetRight(new ofxUILabel("Cam Visualisation",OFX_UI_FONT_LARGE));
    guiTab->addFPS(OFX_UI_FONT_LARGE);
    guiTab->addCanvas(gui);
    guiTab->addCanvas(guiCams);
    ofAddListener(guiTab->newGUIEvent, this, &testApp::guiEvent);
    
    guiCams->loadSettings("GUI/camSettings.xml");
    gui->loadSettings("GUI/guiSetting.xml");
    
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
    cout << e.getName() << endl;
    if (e.getName() == "Import")
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
        guiCams->setVisible(toggle->getValue());
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
    else if (e.getName() == "Auto Camera")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _AutoCamera = toggle->getValue();
    }
    else if (e.getName() == "Reset Camera")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        nicePicRotate = 0.0;
    }
    else if (e.getName() == "Draw Bowl")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _drawBowl = toggle->getValue();
    }
    else if (e.getName() == "Draw Axels")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _drawAxels = toggle->getValue();
    }
    else if (e.getName() == "Draw Cams")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _drawCams = toggle->getValue();
    }
    else if (e.getName() == "Draw Lighting")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _lighting = toggle->getValue();
    }
    else if (e.getName() == "Import New 1")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _importNewCam1 = toggle->getValue();
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 2"))->setValue(false);
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 3"))->setValue(false);
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 4"))->setValue(false);
    }
    else if (e.getName() == "Import New 2")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _importNewCam2 = toggle->getValue();
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 1"))->setValue(false);
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 3"))->setValue(false);
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 4"))->setValue(false);
    }
    else if (e.getName() == "Import New 3")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _importNewCam3 = toggle->getValue();
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 1"))->setValue(false);
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 2"))->setValue(false);
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 4"))->setValue(false);
    }
    else if (e.getName() == "Import New 4")
    {
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
        _importNewCam4 = toggle->getValue();
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 1"))->setValue(false);
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 2"))->setValue(false);
        ((ofxUILabelToggle *) guiCams->getWidget("Import New 3"))->setValue(false);
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
    else if(e.widget->getName() == "CAM1_COL")
    {
        ofxUIImageSampler *sampler = (ofxUIImageSampler *) e.widget;
        rom1CamCol.r = sampler->getColor().r;
        rom1CamCol.g = sampler->getColor().g;
        rom1CamCol.b = sampler->getColor().b;
    }
    else if(e.widget->getName() == "CAM2_COL")
    {
        ofxUIImageSampler *sampler = (ofxUIImageSampler *) e.widget;
        rom2CamCol.r = sampler->getColor().r;
        rom2CamCol.g = sampler->getColor().g;
        rom2CamCol.b = sampler->getColor().b;
    }
    else if(e.widget->getName() == "CAM3_COL")
    {
        ofxUIImageSampler *sampler = (ofxUIImageSampler *) e.widget;
        rom3CamCol.r = sampler->getColor().r;
        rom3CamCol.g = sampler->getColor().g;
        rom3CamCol.b = sampler->getColor().b;
    }
    else if(e.widget->getName() == "CAM4_COL")
    {
        ofxUIImageSampler *sampler = (ofxUIImageSampler *) e.widget;
        romVCamCol.r = sampler->getColor().r;
        romVCamCol.g = sampler->getColor().g;
        romVCamCol.b = sampler->getColor().b;
    }
    else if(e.widget->getName() == "Cam1Alpha")
    {
        ofxUIIntSlider *slider = (ofxUIIntSlider *) e.widget;
        rom1CamCol.a = slider->getValue();
    }
    else if(e.widget->getName() == "Cam2Alpha")
    {
        ofxUIIntSlider *slider = (ofxUIIntSlider *) e.widget;
        rom2CamCol.a = slider->getValue();
    }
    else if(e.widget->getName() == "Cam3Alpha")
    {
        ofxUIIntSlider *slider = (ofxUIIntSlider *) e.widget;
        rom3CamCol.a = slider->getValue();
    }
    else if(e.widget->getName() == "Cam4Alpha")
    {
        ofxUIIntSlider *slider = (ofxUIIntSlider *) e.widget;
        romVCamCol.a = slider->getValue();
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
//--------------------------------------------------------------
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
//--------------------------------------------------------------
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
//--------------------------------------------------------------
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
//--------------------------------------------------------------
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
//--------------------------------------------------------------
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

