#version 330 core

in vec3 fraglightdir;
in vec3 fraglightcolor;
in vec3 fragNormal;
out vec4 fragColor;

vec3 gamma(vec3 light) {
	return pow(light, vec3(0.4));
}

void main() {
	vec3 diffuselight = max(vec3(0.), dot(fragNormal, normalize(fraglightdir)) * fraglightcolor) + 0.03;

	fragColor = vec4(gamma(diffuselight), 1.0);
}