#type vertex
#version 110

uniform mat4 MVP;
uniform float vTime;
attribute vec3 vCol;
attribute vec3 vPos;
varying vec3 color;
varying vec3 position;
varying float time;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    color = vCol;
    position = gl_Position.xyz;
    time = vTime;
}

#type fragment
#version 110
varying vec3 color;
varying vec3 position;
varying float time;

void main()
{
    gl_FragColor = cos(vec4(color, abs(time)) + vec4(position, 0.0) * time * 0.1);
}