precision highp float;

// no sampler2DRect in gles2
uniform sampler2D image;
uniform float rand;

//varying vec4 gl_FragCoord;

void main ()
{
    vec2 texCoord = vec2(gl_FragCoord.x , gl_FragCoord.y);

    // not texture2D
    vec4 col = texture2D(image,texCoord);
    vec4 col_r = texture2D(image,texCoord + vec2(-35.0*rand,0));
    vec4 col_l = texture2D(image,texCoord + vec2( 35.0*rand,0));
    vec4 col_g = texture2D(image,texCoord + vec2( -7.5*rand,0));
    

    col.b = col.b + col_r.b*max(1.0,sin(gl_FragCoord.y*1.2)*2.5)*rand;
    col.r = col.r + col_l.r*max(1.0,sin(gl_FragCoord.y*1.2)*2.5)*rand;
    col.g = col.g + col_g.g*max(1.0,sin(gl_FragCoord.y*1.2)*2.5)*rand;

    gl_FragColor.rgba = col.rgba;
}
