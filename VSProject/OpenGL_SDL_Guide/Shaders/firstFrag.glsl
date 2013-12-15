#version 150

uniform float flucScale;
uniform sampler2D texTexture;
uniform sampler2D texGameOver;

in vec3 fragColor;
in vec2 fragTexcoord;

out vec4 outColor;

void main()
{
	vec4 texPixColor = texture(texTexture, fragTexcoord);
	//vec4 gameOverPixColor = texture(texGameOver, fragTexcoord);

	texPixColor = texPixColor * vec4(fragColor, 1.0);
	//gameOverPixColor = gameOverPixColor * vec4(fragColor, 1.0);

	//outColor = mix(texPixColor, gameOverPixColor, flucScale);
	outColor = texPixColor;
}
