attribute vec4 position;                                // set automatically by OF
attribute vec2 texcoord;                                // set automatically by OF
uniform mat4 modelViewProjectionMatrix; // set automatically by OF

varying vec2 texcoord0;

void main()
{
        gl_Position = modelViewProjectionMatrix * position;
        texcoord0 = texcoord;
}


/*
//This is the internal RPi vert shader for reference
precision lowp float;

attribute vec4 position;
attribute vec4 color;
attribute vec4 normal;
attribute vec2 texcoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

varying vec4 colorVarying;
varying vec2 texCoordVarying;

uniform float usingTexture;
uniform float usingColors;

uniform vec4 globalColor;

void main(){
        gl_Position = modelViewProjectionMatrix * position;
        if(usingTexture>.5) texCoordVarying = (textureMatrix*vec4(texcoord.x,texcoord.y,0,1)).xy;
        if(usingColors>.5) colorVarying = color*globalColor;
        else colorVarying = globalColor;
}
*/
