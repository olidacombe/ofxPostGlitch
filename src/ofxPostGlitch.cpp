//
//  ofxPostGlitch.cpp
//
//  Created by maxilla inc. on 2013/02/01.
//  modified by olidacombe in fork
//

#include "ofxPostGlitch.h"

void ofxPostGlitch::setup(ofFbo *buffer_){
	targetBuffer = buffer_;
	buffer_size.set(buffer_->getWidth(), buffer_->getHeight());
	ShadingBuffer.allocate(buffer_size.x,buffer_size.y);
    plane.set(buffer_size.x, buffer_size.y, 2, 2);
}

/*
void ofxPostGlitch::setFbo(ofFbo *buffer_){
	targetBuffer = buffer_;
	buffer_size.set(buffer_->getWidth(), buffer_->getHeight());
	ShadingBuffer.allocate(buffer_size.x,buffer_size.y);
    plane.set(buffer_size.x, buffer_size.y, 2, 2);
}
*/

void ofxPostGlitch::loadShaders(const string& dir)
{
    shaderDir = dir;
    ofDirectory searchDirectory(dir);
    searchDirectory.allowExt("vert");
    searchDirectory.listDir();

    togShaders.clear();

    cout << "Shaders found:" << endl << endl;
    //const string dirPrefix = searchDirectory.getAbsolutePath() + "/";
    const string dirPrefix = shaderDir + "/";
    for(ofFile vertShader : searchDirectory)
    {
        cout << vertShader.getBaseName() << endl;
        cout << dirPrefix + vertShader.getBaseName() << endl;
        togShaders.emplace_back(shared_ptr<toggleableShader>(new toggleableShader(dirPrefix + vertShader.getBaseName())));
    }
}

void ofxPostGlitch::setFx(const int& index, bool shadingState) {
    try {
        togShaders.at(index)->setShading(shadingState);
    } catch(const std::out_of_range& e) {
        // we don't have a shader at that index
    }
}

void ofxPostGlitch::toggleFx(const int& index) {
    try {
        togShaders.at(index)->toggleShading();
        cout << "toggled shader " << index << endl;
    } catch(const std::out_of_range& e) {
        // we don't have a shader at that index
    }
}

void ofxPostGlitch::apply(){
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
			//tsh.setUniformTexture	("image"		,*targetBuffer,0);
			tsh.setUniformTexture("tex0", *targetBuffer, targetBuffer->getTexture().getTextureData().textureID);
            tsh.setUniform2i("resolution", buffer_size.x, buffer_size.y);
			tsh.setUniform1f("time", ofGetElapsedTimef());
            //tsh.setUniform2f("resolution", buffer_size.x, buffer_size.y);
            /*
			tsh.setUniform1i("trueWidth",buffer_size.x);
			tsh.setUniform1i("trueHeight",buffer_size.y);
			tsh.setUniform1f("rand", ofRandom(1));
			tsh.setUniform1f("mouseX", ofGetMouseX());
			tsh.setUniform1f("mouseY", ofGetMouseY());
			tsh.setUniform1f("val1", ShadeVal[0]);
			tsh.setUniform1f("val2", ShadeVal[1]);
			tsh.setUniform1f("val3", ShadeVal[2]);
			tsh.setUniform1f("val4", ShadeVal[3]);
			tsh.setUniform2fv("blur_vec", v);
            */

			ShadingBuffer.begin();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // this bullshit should be avoided somehow
                ofPushMatrix();
                ofTranslate(buffer_size.x / 2, buffer_size.y / 2);
                    plane.draw();
                ofPopMatrix();

			ShadingBuffer.end();
			tsh.end();

			targetBuffer->begin();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ShadingBuffer.draw(0, 0, buffer_size.x, buffer_size.y);
			targetBuffer->end();
        }
    }
}
