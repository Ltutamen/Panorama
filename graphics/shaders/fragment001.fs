#version 450

in mediump vec2 UV;

out mediump vec3 color;

uniform sampler2D exampleTexture;

void main() {
	color = texture(exampleTexture, UV).rgb;
}