//
//  camClass.cpp
//  camVisualisor
//
//  Created by David Haylock on 14/05/2014.
//
//

#include "camClass.h"
//--------------------------------------------------------------
vector <ofVec3f> Cam::setupPts(string absFilePath,ofVec3f pos)
{
    //Copy Across the origin pt
    dataPointCentre = pos;
    
    
    camMesh.enableColors();
    camMesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    //Load the pts File
    if (camCoordsFile.loadFile(absFilePath))
    {
        cout << "Loaded: " << absFilePath <<  endl;
        importlastTagNumber = 0;
        importPointCount = 0;
        importLineCount = 0;
        
        int numOfPtsTags = camCoordsFile.getNumTags("CAMCOORDS:PT");
        
        if (numOfPtsTags > 0) {
            camCoordsFile.pushTag("CAMCOORDS",numOfPtsTags-1);

            //Search For Number of PTS
            int numOfPTs = camCoordsFile.getNumTags("PT");
            
            if (numOfPTs > 0) {
                int totalToRead = MIN(numOfPTs, MAX_NUM_PTS);
                
                //Cycle through the PT and find VIX (special point from cam creator
                for(int i = 0; i < totalToRead; i++){
                    
                    //Maths 'n' Shit
                    float r = camCoordsFile.getValue("PT:VIX", 0, i);
                    float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * numOfPTs);

                    //Make Circle Points
                    float xScale = pos.x + (r * cos(angle));
                    float yScale = pos.y + (r * sin(angle));
                    float zScale = r;
                    
                    //Put points into a container
                    camPts.push_back(ofVec3f(xScale,yScale,zScale));
                }
            }
            
            //Add Points to the Mesh
            for (int i = 0; i < camPts.size(); i++) {
                camMesh.addVertex(ofVec3f(camPts[i].x,camPts[i].y,dataPointCentre.z));
            }
            //Setup Vertice Fill
            camVbo.setMesh(camMesh, GL_STATIC_DRAW);
        }
    }
    //Can't Load file
    else
    {
        cout << "Failed to Load File" << endl;
    }
    pushRodRadius = 2.0;
	pushRodHeight = 400.0;
	pushRodTop = 0.0;
    guideRod.set(6.0, 50.0);
    return camPts;
}


//--------------------------------------------------------------
void Cam::update(float rotationDeg)
{
    //Visual Rotate by degrees
    rotationDegrees = rotationDeg;
    //Find the point on the cam that's active
    float tangleToFind = fmod(270.0 - rotationDegrees, 360.0);
    int tindexToFind = (int)( (tangleToFind * (1.0 * camPts.size())/360.0)) - 1;
    if (tindexToFind < 0) tindexToFind = tindexToFind + camPts.size();
    
    float camRadiuss = camPts[tindexToFind].z;
    pushRod.set(pushRodRadius, pushRodHeight); //radius an height
    pushRod.setPosition(dataPointCentre.x, dataPointCentre.y - (0.5 * pushRodHeight) - camRadiuss, dataPointCentre.z);
    pushRodTop = dataPointCentre.y - pushRodHeight - camRadiuss;
}

//--------------------------------------------------------------
void Cam::draw(ofColor c,bool drawRods)
{
    ofPushMatrix();
    ofTranslate(dataPointCentre);//move pivot to centre of shape
    ofRotateX(rotationDegrees);//rotate from centre
    ofRotateY(90.0);
    ofPushMatrix();
    ofTranslate(-dataPointCentre);
    ofSetColor(c);
    camVbo.draw(GL_POLYGON, 0, camPts.size());
    ofSetColor(255);
    camMesh.drawWireframe();
    ofPopMatrix();
    ofPopMatrix();
    
    ofSetColor(0, 60.0);
	ofPushMatrix();
    ofTranslate(dataPointCentre.x, dataPointCentre.y - 300.0, dataPointCentre.z);//move pivot to centre of shape
    guideRod.draw();
	ofPopMatrix();
    
    pushRod.draw();
    
}