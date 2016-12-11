//
//  ofxPostGlitch.cpp
//
//  Created by maxilla inc. on 2013/02/01.
//

#include "ofxPostGlitch.h"

void ofxPostGlitch::setup(ofFbo *buffer_){
	targetBuffer = buffer_;
	buffer_size.set(buffer_->getWidth(), buffer_->getHeight());
	ShadingBuffer.allocate(buffer_size.x,buffer_size.y);
}

void ofxPostGlitch::setFbo(ofFbo *buffer_){
	targetBuffer = buffer_;
	buffer_size.set(buffer_->getWidth(), buffer_->getHeight());
	ShadingBuffer.allocate(buffer_size.x,buffer_size.y);
}

void ofxPostGlitch::setFx(const int& index, bool enabled) {

}

/*
void ofxPostGlitch::setFx(ofxPostGlitchType type_, bool enabled){
	bShading[type_] = enabled;
}

void ofxPostGlitch::toggleFx(ofxPostGlitchType type_){
	bShading[type_] ^= true;
}

bool ofxPostGlitch::getFx(ofxPostGlitchType type_){
	return bShading[type_];
}
*/

void ofxPostGlitch::generateFx(){
	if (targetBuffer == NULL){
		ofLog(OF_LOG_WARNING, "ofxFboFX --- Fbo is not allocated.");
		return;
	}

	static int step = ofRandom(4,15);
	float v[2];
	v[0] = ofRandom(3);v[1] = ofRandom(3);
	if (ofGetFrameNum() % step == 0){
		step = ofRandom(10,30);
		ShadeVal[0] = ofRandom(100);
		ShadeVal[2] = ofRandom(100);
		ShadeVal[3] = ofRandom(100);
	}

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255);
	glClearColor(0, 0, 0, 0.0);

    for(shared_ptr<ofxPostGlitch::toggleableShader> togShader : togShaders)
    {
        if(togShader->isShading())
        {
            ofShader& tsh = togShader->getShader();
            
			tsh.begin();
			tsh.setUniformTexture	("image"		,*targetBuffer,0);
			tsh.setUniform1i		("trueWidth"	,buffer_size.x);
			tsh.setUniform1i		("trueHeight"	,buffer_size.y);
			tsh.setUniform1f		("rand"			,ofRandom(1));
			tsh.setUniform1f		("mouseX"		,ofGetMouseX());
			tsh.setUniform1f		("mouseY"		,ofGetMouseY());
			tsh.setUniform1f		("val1"			,ShadeVal[0]);
			tsh.setUniform1f		("val2"			,ShadeVal[1]);
			tsh.setUniform1f		("val3"			,ShadeVal[2]);
			tsh.setUniform1f		("val4"			,ShadeVal[3]);
			tsh.setUniform1f		("timer"		,ofGetElapsedTimef());
			tsh.setUniform2fv		("blur_vec"		,v);

			ShadingBuffer.begin();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ofRect(0, 0, buffer_size.x, buffer_size.y);
			ShadingBuffer.end();
			tsh.end();

			targetBuffer->begin();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ShadingBuffer.draw(0, 0,buffer_size.x,buffer_size.y);
			targetBuffer->end();
        }
    }
}
