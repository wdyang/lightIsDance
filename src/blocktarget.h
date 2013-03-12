/*
 *  blocktarget.h
 *  MovieGrabber
 *
 *  Created by Weidong Yang on 10/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#include "ofMain.h"
#include "ofxOsc.h"
#include <string>

#define		xy2idx(x, y)		((x) + (camWidth)  *(y))

using std::string;

class blocktarget{
public:
	float videoMult;
	float home_x, home_y, x, y, vx, vy;
	float homeDrag;
	int width, height, camWidth, camHeight;
	//char targetword[255];
	string targetword;
	
	ofxOscSender *sender;
	
	float threshold;
	float sumchange;
	//testApp *parentApp;
	blocktarget(float x0, float y0, int width0, int height0, int camWidth0, int camHeight0, ofxOscSender *sender0){
		home_x=x0;	home_y=y0;
		x=x0;		y=y0;
		vx=0;		vy=0;
		width=width0; height=height0;
		sender=sender0;
		
		threshold = 20;
		homeDrag = -0.2;
		camWidth=camWidth0;
		camHeight=camHeight0;
		//parentApp= (testApp&) testappointer;
	}
	void draw(int alpha);
		
	float changedValue(unsigned char * video);
	void updateposition();
	
};


