#version 150

uniform float flucScale;
uniform sampler2D texTexture;
uniform sampler2D texGameOver;
uniform int texUnit;

in vec3 fragColor;
in vec2 fragTexcoord;

out vec4 outColor;

void main()
{
	vec4 texPixColor = texture(texTexture, fragTexcoord);
	if(texUnit == 1)
	{
		texPixColor = texture(texGameOver, fragTexcoord);
	}

	texPixColor = texPixColor * vec4(fragColor, 1.0);

	outColor = texPixColor;
}
