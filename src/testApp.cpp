#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){

	displayWidth   =640;
	displayHeight    =480;
	videoMult		=0.5;
	camWidth 		= displayWidth*videoMult;	// try to grab at this size.
	camHeight 		= displayHeight*videoMult;
	DRAWCHANGE		=true;

	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);

	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	previousFrame = new unsigned char[camWidth*camHeight*3];
    differenceFrame = new unsigned char[camWidth*camHeight*3];
	videoMirrored = new unsigned char[camWidth*camHeight*3];

	videoTexture.allocate(camWidth,camHeight, GL_RGB);
    differenceTexture.allocate(camWidth,camHeight, GL_RGB);
	ofSetFrameRate(30);
	framecnt=0;
	
	sender.setup( HOST, PORT );
	setupTargets();
}


//--------------------------------------------------------------
void testApp::update(){

	ofBackground(100,100,100);

	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();

		for (int iy=0; iy<camHeight; iy++){
			int idxin=3*iy*camWidth;
			int idxmirror = 3*(iy+1)*camWidth -3;
			for (int ix=0; ix<camWidth; ix++){
				for(int icolor=0; icolor<3; icolor++)
					videoMirrored[idxmirror+icolor]=pixels[idxin+icolor];
				idxin+=3; idxmirror-=3;
			}
		}
		for (int i = 0; i < totalPixels; i++){
		//	videoInverted[i] = 255 - pixels[i];
		//	differenceFrame[i]=abs(pixels[i]-previousFrame[i]);
	//		previousFrame[i]=pixels[i];
			differenceFrame[i]=abs(videoMirrored[i]-previousFrame[i]);
			previousFrame[i]=videoMirrored[i];
		}
		
		
		videoTexture.loadData(videoMirrored, camWidth,camHeight, GL_RGB);
        differenceTexture.loadData(differenceFrame, camWidth,camHeight, GL_RGB);

	//differenceFrame=videoTexture-previousFrame;

	}

}

//--------------------------------------------------------------
void testApp::draw(){
	char tempStr[255];
	ofSetColor(0xffffff);
	//vidGrabber.draw(20+displayWidth,0);
	//videoTexture.draw(20+displayWidth,20+camHeight,camWidth,camHeight);
    //differenceTexture.draw(0, 0, displayWidth, displayHeight);
	videoTexture.draw(0, 0, displayWidth, displayHeight);
    //differenceTexture.draw(20+displayWidth,20+camHeight,camWidth,camHeight);
	//ofSetColor(0x000000);
	sprintf(tempStr, "FrameRate is %f width %d height %d framecnt %d", ofGetFrameRate(), camWidth, camHeight, framecnt++);
	ofDrawBitmapString(tempStr, 50,ofGetHeight()-50);
	ofFill();
	ofEnableAlphaBlending();
	if (framecnt>60){
	for (int i1=0; i1<numtarget; i1++){
		float targetchange=mytarget[i1]->changedValue(differenceFrame);
		int drawalpha=linescale(targetchange, 0, 60, 20, 200);
		mytarget[i1]->draw(drawalpha);
		if(DRAWCHANGE){
			sprintf(tempStr, "%4.2f", targetchange);
			ofDrawBitmapString(tempStr, (mytarget[i1]->x)/videoMult,(mytarget[i1]->y+10)/videoMult);
		}
		mytarget[i1]->updateposition();
	}
	}
	ofDisableAlphaBlending();

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	// in fullscreen mode, on a pc at least, the
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...

	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}


}


//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

void testApp::setupTargets(){
	numtarget = 6;
	string jmena[6]; //note: the [] appears after the variable
	
	//populate array:
    jmena[0] = "Dream";
    jmena[1] = "Dance";
    jmena[2] = "likes to";
    jmena[3] = "life";
    jmena[4] = "travel";
    jmena[5] = "be free";

	
	for (int i1=0; i1<numtarget; i1++){
		mytarget[i1] = new blocktarget(10+i1*50, 30, 30, 20, camWidth, camHeight, &sender);
		mytarget[i1]->targetword=jmena[i1];
		mytarget[i1]->videoMult=videoMult;
	}
	
}

