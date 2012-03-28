#pragma once

#include "ofMain.h"
#include "ofxFailSafeVideoGrabber.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
	
		ofxFailSafeVideoGrabber g1, g2, g3;
		
};
