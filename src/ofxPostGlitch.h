//
//  ofxPostGlitch.h
//
//  Created by maxilla inc. on 2013/02/01.
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

    ofxPostGlitch() : ofxPostGlitch("Shaders")
    {
        //ofxPostGlitch("Shaders");
    }

	ofxPostGlitch(const string& searchDir)
    {
		targetBuffer = nullptr;
        loadShaders(searchDir);
        /*
		shader[0].load("Shaders/convergence");
		shader[1].load("Shaders/glow");
		shader[2].load("Shaders/shaker");
		shader[3].load("Shaders/cut_slider");
		shader[4].load("Shaders/twist");
		shader[5].load("Shaders/outline");
		shader[6].load("Shaders/noise");
		shader[7].load("Shaders/slitscan");
		shader[8].load("Shaders/swell");
		shader[9].load("Shaders/invert");
		shader[10].load("Shaders/crHighContrast");
		shader[11].load("Shaders/crBlueraise");
		shader[12].load("Shaders/crRedraise");
		shader[13].load("Shaders/crGreenraise");
		shader[14].load("Shaders/crRedinvert");
		shader[15].load("Shaders/crBlueinvert");
		shader[16].load("Shaders/crGreeninvert");
        */
	}

    void loadShaders(const string& dir);

	/* Initialize & set target Fbo */
	void setup(ofFbo* buffer_);

	/* Set target Fbo */
	void setFbo(ofFbo* buffer_);

    void setFx(const int& index, bool enabled);
    void toggleFx(const int& index);

	/* Switch each effects on/off */
	//void setFx(ofxPostGlitchType type_,bool enabled);

	/* Toggle each effects on/off */
	//void toggleFx(ofxPostGlitchType type_);

	/* Return current effect's enabled info*/
	//bool getFx(ofxPostGlitchType type_);

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
