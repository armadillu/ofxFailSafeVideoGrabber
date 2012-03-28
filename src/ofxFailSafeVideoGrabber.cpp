/*
 *  ofxFailSafeVideoGrabber.cpp
 *  emptyExample
 *
 *  Created by Oriol Ferrer Mesià on 28/03/12.
 *  Copyright 2012 uri.cat. All rights reserved.
 *
 */

#include "ofxFailSafeVideoGrabber.h"

ofxFailSafeVideoGrabber::ofxFailSafeVideoGrabber(){
	what = NOTHING;
	w = h = -1;
}

ofxFailSafeVideoGrabber::~ofxFailSafeVideoGrabber(){}


void ofxFailSafeVideoGrabber::start( int desiredW, int desiredH, int desiredFrameRate, bool createTexture, string backupMoviePath_ ){
	
	backupMoviePath = backupMoviePath_;
	w = desiredW;
	h = desiredH;
	frameRate = desiredFrameRate;
	useTexture = createTexture;
	
 	bool gotCamera = camera.initGrabber(desiredW, desiredH, createTexture);
	
	if (gotCamera){		////////////////////////////////////////////////////////// VIDEO GRABBER
		
		arrangeCamera();

	}else{		
		
		if ( backupMoviePath_.length() > 0){	

			movie.setUseTexture(useTexture);
			bool movieOK = movie.loadMovie(backupMoviePath);
			
			if (movieOK){	//////////////////////////////////////////////////// MOVIE PLAYER			
				
				arrangeMovie();				
				
			}else{	//////////////////////////////////////////////////////////// IMAGE				
				
				arrangeImage();
			}
			
		}else{	//////////////////////////////////////////////////////////////// IMAGE				
			
			arrangeImage();
		}				
	}
}

void ofxFailSafeVideoGrabber::arrangeCamera(){
	camera.setDesiredFrameRate( frameRate );
	what = CAMERA;
}


void ofxFailSafeVideoGrabber::arrangeMovie(){
	movie.setLoopState(OF_LOOP_NORMAL);
	movie.play();
	what = MOVIE;
}

void ofxFailSafeVideoGrabber::arrangeImage(){
	what = IMAGE;
	image.setUseTexture(useTexture);
	image.allocate(w, h, OF_IMAGE_COLOR);
}

void ofxFailSafeVideoGrabber::updateImage(){

	int totalPixels = w * h ;
	unsigned char * pixels = image.getPixels();
	for (int i = 0; i < totalPixels; i++){
		unsigned char val = ofRandom(255);
		pixels[i*3] = pixels[i*3+1] = pixels[i*3+2] = val;
	}
	if (useTexture) image.update();
}

void ofxFailSafeVideoGrabber::update(){
	switch (what) {
		case NOTHING: return;
		case CAMERA: camera.update(); break;
		case MOVIE: movie.update(); break;
		case IMAGE: updateImage(); break;
	}
}

void ofxFailSafeVideoGrabber::draw(float x, float y){
	if ( what == NOTHING) return;
	draw(x, y, w, h);
}

void ofxFailSafeVideoGrabber::draw(float x, float y, float w, float h){
	switch (what) {
		case NOTHING: return;
		case CAMERA: camera.draw(x, y, w, h); break;
		case MOVIE: movie.draw(x, y, w, h); break;
		case IMAGE: image.draw(x, y, w, h); break;
	}
}

bool ofxFailSafeVideoGrabber::isUsingCamera(){
	return what == CAMERA;
}

bool ofxFailSafeVideoGrabber::isUsingMovie(){
	return what == MOVIE;
}

float ofxFailSafeVideoGrabber::getHeight(){
	return h;
}

float ofxFailSafeVideoGrabber::getWidth(){
	return w;
}

bool ofxFailSafeVideoGrabber::isFrameNew(){
	switch (what) {
		case NOTHING: return false;
		case CAMERA: return camera.isFrameNew();
		case MOVIE: return movie.isFrameNew();
		case IMAGE: return true;
	}
}

ofTexture& ofxFailSafeVideoGrabber::getTextureReference(){
	switch (what) {
		case NOTHING: return image.getTextureReference();
		case CAMERA: return camera.getTextureReference();
		case MOVIE: return movie.getTextureReference();
		case IMAGE: return image.getTextureReference();
	}
}

unsigned char* ofxFailSafeVideoGrabber::getPixels(){
	switch (what) {
		case NOTHING: return NULL;
		case CAMERA: return camera.getPixels();
		case MOVIE: return movie.getPixels();
		case IMAGE: return image.getPixels();
	}
}

ofVideoGrabber * ofxFailSafeVideoGrabber::getVideoGrabber(){
	return &camera;
}

ofVideoPlayer * ofxFailSafeVideoGrabber::getVideoPlayer(){
	return &movie;
}

ofImage * ofxFailSafeVideoGrabber::getImage(){
	return &image;
}

void ofxFailSafeVideoGrabber::videoSettings(){
	if (what==CAMERA) camera.videoSettings();
}
