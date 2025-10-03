#version 330 core

uniform float scaleX;
uniform float flipY;
uniform mat4 rotate;
uniform mat4 translate;
uniform mat4 view;
uniform mat4 perspective;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

out vec3 fragNormal;

void main() {
	gl_Position = perspective * view * translate * rotate * vec4(aPos, 1.0);
	gl_Position.x /= scaleX;
	gl_Position.y *= flipY;

	fragNormal = (rotate * vec4(normal, 1.0)).xyz;
}