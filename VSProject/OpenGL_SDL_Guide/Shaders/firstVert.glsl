#version 150

in vec3 position;
in vec3 color;
in vec2 texcoord;

out vec3 fragColor;
out vec2 fragTexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	fragTexcoord = texcoord;
    fragColor = color;
	mat4 modelViewMatrix = proj * view * model;
	vec4 posV4 = vec4(position, 1.0);
    gl_Position = modelViewMatrix * posV4;
}
