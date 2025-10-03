#version 330 core

uniform float scaleX;
uniform float flipY;
uniform mat4 rotate;
uniform mat4 translate;
uniform mat4 view;
uniform mat4 perspective;
uniform vec3 lightdir;
uniform vec3 lightcolor;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

out vec3 fragNormal;
out vec3 fraglightdir;
out vec3 fraglightcolor;

void main() {
	gl_Position = perspective * view * translate * rotate * vec4(aPos, 1.0);
	gl_Position.x /= scaleX;
	gl_Position.y *= flipY;

	fragNormal = (rotate * vec4(normal, 1.0)).xyz;
	fraglightdir = lightdir;
	fraglightcolor = lightcolor;
}