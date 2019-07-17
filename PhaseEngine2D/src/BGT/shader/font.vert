#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 textCoord;
uniform mat4 projection;
out vec2 textcoord;
void main()
{
	textcoord = textCoord;
    gl_Position = projection * vec4(aPos,0.0f,1.0f);
}