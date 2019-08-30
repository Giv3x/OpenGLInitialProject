#version 430

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 lightIntensity;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec4 eyeCoords;
varying vec3 modeledNormal;
varying vec3 toCameraVector;

void main() {
	eyeCoords = modelMatrix * vec4(position, 1.0);
	toCameraVector = (inverse(viewMatrix) * vec4(0, 0, 0, 1.0)).xyz - eyeCoords.xyz;
	modeledNormal = normalize(vec4(normal, 1.0)).xyz;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
	texCoord0 = texCoord;
}