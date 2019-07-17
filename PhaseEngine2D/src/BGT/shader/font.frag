#version 330 core
in vec2 textcoord;

uniform sampler2D texture1;
uniform vec4 penColor;

void main()
{
	  gl_FragColor = penColor * vec4(1.0, 1.0, 1.0, texture(texture1, textcoord).r);
}