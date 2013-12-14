#version 150

uniform float flucScale;
uniform sampler2D texKitten;
uniform sampler2D texPuppy;

in vec3 fragColor;
in vec2 fragTexcoord;

out vec4 outColor;

void main()
{
	vec4 catPixColor = texture(texKitten, fragTexcoord);
	vec4 dogPixColor = texture(texPuppy, fragTexcoord);

	catPixColor = catPixColor * vec4(fragColor, 1.0);
	dogPixColor = dogPixColor * vec4(fragColor, 1.0);

	outColor = mix(catPixColor, dogPixColor, flucScale);
}
