#version 330 core

uniform float scaleX;
uniform float flipY;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 perspective;
uniform vec3 lightdir;
uniform vec3 lightcolor;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

out vec3 fragNormal;
out vec3 fraglightdir;
out vec3 fraglightcolor;

// By Inigo Quilez
mat3 adjugate(in mat4 m) {
    return mat3(cross(m[1].xyz, m[2].xyz), 
                cross(m[2].xyz, m[0].xyz), 
                cross(m[0].xyz, m[1].xyz));
}

void main() {
	gl_Position = perspective * view * transform * vec4(aPos, 1.0);
	gl_Position.x /= scaleX;
	gl_Position.y *= flipY;

	fragNormal = adjugate(transform) * normal;
	fraglightdir = lightdir;
	fraglightcolor = lightcolor;
}