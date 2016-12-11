//
//  ofxPostGlitch.h
//
//  Created by maxilla inc. on 2013/02/01.
//  Modified by olidacombe in fork 
//
//

#ifndef __ofxPostGlitchExample__ofxPostGlitch__
#define __ofxPostGlitchExample__ofxPostGlitch__

#include "ofMain.h"
#include "TerminalListener.h"

class ofxPostGlitch{
public:

    class toggleableShader
    {
    public:
        toggleableShader(const string& shaderPath) : shading(false)
        {
            shader.load(shaderPath);
        }
        ofShader& getShader() { return shader; }
        bool isShading() { return shading; }
        void toggleShading() { shading = !shading; }
        void setShading(bool state) { shading = state; }
    private:
        bool shading;
        ofShader shader;
    };

    ofxPostGlitch() : ofxPostGlitch("Shaders") {}

	ofxPostGlitch(const string& searchDir)
    {
		targetBuffer = nullptr;
        loadShaders(searchDir);
	}

    void loadShaders(const string& dir);

	/* Initialize & set target Fbo */
	void setup(ofFbo* buffer_);

	/* Set target Fbo */
	void setFbo(ofFbo* buffer_);

    void setFx(const int& index, bool enabled);
    void toggleFx(const int& index);

	/* Apply enable effects to target Fbo */
	void generateFx();

protected:
    string shaderDir;
    vector<shared_ptr<toggleableShader>> togShaders;
	ofFbo*		targetBuffer;
	ofFbo		ShadingBuffer;
	ofPoint		buffer_size;
	float ShadeVal[4];
};

#endif /* defined(__ofxPostGlitchExample__ofxPostGlitch__) */
