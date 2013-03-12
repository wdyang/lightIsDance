#ifndef _TEST_APP
#define _TEST_APP

#include <string>

using std::string;

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

#include "blocktarget.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void resized(int w, int h);

		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		ofTexture			videoTexture;
		unsigned char *		videoMirrored;
		unsigned char *     previousFrame;
		unsigned char *     differenceFrame;
		ofTexture           differenceTexture;
	
		int					displayWidth;
		int					displayHeight;
		int 				camWidth;
		int 				camHeight;
		float				videoMult;
		bool				DRAWCHANGE;
	int			framecnt;

		ofxOscSender sender;
		blocktarget		*	mytarget[100];
		int					numtarget;
		int linescale(float x0, float lowin, float highin, int lowout, int highout){
			int xout=(x0-lowin)*(highout-lowout)/(highin-lowin)+lowout;
			if (xout<lowout) xout=lowout;
			else if (xout>highout) xout=highout;
			return xout;
		
		}
	void setupTargets();
	
};
#endif
