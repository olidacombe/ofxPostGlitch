precision highp float; // this will make the default precision high

varying vec2 texcoord0;
uniform sampler2D tex0;

void main()
{
    gl_FragColor = texture2D(tex0, texcoord0);
}


/*
//This is the internal RPi vert shader for reference
precision lowp float;

uniform sampler2D src_tex_unit0;

uniform float usingTexture;
uniform float bitmapText;

varying vec4 colorVarying;
varying vec2 texCoordVarying;

void main(){
        vec4 tex;
        if(usingTexture>.5){
                tex = texture2D(src_tex_unit0, texCoordVarying);
                if(bitmapText>.5 && tex.a < 0.5){
                        discard;
                }else{
                        gl_FragColor = colorVarying*tex;
                }
        }else{
                gl_FragColor = colorVarying;
        }
}
*/
