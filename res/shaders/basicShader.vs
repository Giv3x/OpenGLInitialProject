#version 430

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

void main() {
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(position, 1.0);
	texCoord0 = texCoord;
}