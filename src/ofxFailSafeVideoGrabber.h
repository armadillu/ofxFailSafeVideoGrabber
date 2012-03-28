/*
 *  ofxFailSafeVideoGrabber.h
 *  emptyExample
 *
 *  Created by Oriol Ferrer Mesià on 28/03/12.
 *  Copyright 2012 uri.cat. All rights reserved.
 *
 */

/** ofxFailSafeVideoGrabber
 
 Simple OpenFrameworks Addon intended to be a fail-safe replacement for ofVideoGrabber. 
 It will mostly wrap it, but if there's no camera available, a safety measure will be taken 
 so you can still run the project. A backup movie file will be used (if provided by the user) 
 if no videoGrabber is available, and as a last resort, if a movie file is not available either, 
 an ofImage with pixel noise will be provided. 
 
 **/

#pragma once

#include "ofMain.h"

class ofxFailSafeVideoGrabber{

public:

	enum UsingWhat{ NOTHING = 0, CAMERA , MOVIE, IMAGE };
	
	ofxFailSafeVideoGrabber();
	~ofxFailSafeVideoGrabber();
	
	void start( int desiredW, int desiredH, int desiredFrameRate, bool createTexture, string backupMoviePath = "");
	void update();
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);

	bool isUsingCamera();
	bool isUsingMovie();
	
	float getHeight();
	float getWidth();
	bool isFrameNew();

	ofTexture& getTextureReference();
	unsigned char* getPixels();
	
	ofVideoGrabber * getVideoGrabber();
	ofVideoPlayer * getVideoPlayer();
	ofImage * getImage();
	
	void videoSettings();

private:
	
	void arrangeCamera();
	void arrangeMovie();
	void arrangeImage();
	
	void updateImage();

	UsingWhat			what;
	string				backupMoviePath;
	int					frameRate;
	int					w, h;
	bool				useTexture;

	ofVideoGrabber 		camera;	//first option, normal video grabber
	ofVideoPlayer 		movie;	//second option, if cam fails and usr provided a valid file
	ofImage				image;	//3rd option, if no file, offer a texture + pixels
		
};