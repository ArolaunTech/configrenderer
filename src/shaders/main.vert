#version 330 core

uniform float flipY;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

out vec3 fragNormal;

void main() {
	gl_Position = vec4(aPos, 1.0);
	gl_Position.y *= flipY;

	fragNormal = normal;
}