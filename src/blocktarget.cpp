/*
 *  blocktarget.cpp
 *  MovieGrabber
 *
 *  Created by Weidong Yang on 10/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "blocktarget.h"
void blocktarget::draw(int alpha){
	ofSetColor(255,255,255,alpha);   // red, 50% transparent
	ofRect(x/videoMult,y/videoMult,width/videoMult,height/videoMult);
	char tmpStr[255];
	
	memcpy(tmpStr,targetword.c_str(),targetword.size());
	tmpStr[targetword.size()]=0;
	ofSetColor(255,255,255,255);   // red, 50% transparent

	ofDrawBitmapString(tmpStr, x/videoMult,y/videoMult+10);
};

float blocktarget::changedValue(unsigned char * video){
	sumchange = 0;
	
	float xoffset=0; 
	float yoffset=0;
	for (int iy=0; iy<height; iy++)
		for (int ix=0; ix<width; ix++){
			int idx=xy2idx(ix+x, iy+y)*3;
			int delta=(video[idx]+video[idx+1]+video[idx+2]);
			sumchange+=delta;
			xoffset+=(ix-(width-1)/2.)*delta/50.; //the touch power
			yoffset+=(iy-(height-1)/2.)*delta/50.;
			//xoffset=0; yoffset=0;
		}
	//sumchange=10.1;
	sumchange=sumchange/width/height-threshold;
	if (sumchange<0) sumchange=0;
	
	if (sumchange>2){
		ofxOscMessage m;
		m.setAddress( "/camid" );
		//m.addIntArg( id );
		char tmpStr[255];
		memcpy(tmpStr,targetword.c_str(),targetword.size());
			tmpStr[targetword.size()]=0;
		m.addStringArg(tmpStr);
		//m.addFloatArg( sumchange );
		//m.addFloatArg( ofGetElapsedTimef() );
		sender->sendMessage( m );
	}
	
	vx=vx*0.95+xoffset/width/height;
	vy=vy*0.95+yoffset/width/height;
	return sumchange;
};

void blocktarget::updateposition(){
	x-=vx;
	y-=vy;
	if(x>(camWidth-width-1)) {
		vx=-vx; 
		x=2*(camWidth-width)-x-2;
	}
	else if (x<width+1) {
		vx=-vx; 
		x=2*(width)-x+2;
	}
	if(y>(camHeight-height-1)) {
		vy=-vy; 
		y=2*(camHeight-height)-y-2;
	}
	else if (y<height+1) {
		vy=-vy;
		y=2*(height)-y+2;
	}
	
	float r2=sqrt(((home_x-x)*(home_x-x)+(home_y-y)*(home_y-y)+1.));
	vx+=(home_x-x)*homeDrag/r2;
	vy+=(home_y-y)*homeDrag/r2;
	

};