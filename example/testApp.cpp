#include "testApp.h"

int w = 320;
int h = 240;

//--------------------------------------------------------------
void testApp::setup(){

	g1.start(w, h, 30, true, "fingers.mov");
	g2.start(w, h, 30, true, "fingers.mov");
	g3.start(w, h, 30, true, "wrongFile.mov");
}

//--------------------------------------------------------------
void testApp::update(){
	g1.update();
	g2.update();
	g3.update();
}

//--------------------------------------------------------------
void testApp::draw(){

	g1.draw( 0, 0 );
	g2.draw( w, 0 );
	g3.draw( 2 * w, 0 );
}

