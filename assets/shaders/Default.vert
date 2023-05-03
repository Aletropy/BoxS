#version 330 core

layout(location = 0) in vec4 a_Pos;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_ViewProjMatrix;

void main()
{
    v_Color = a_Color;
    gl_Position = u_ViewProjMatrix * a_Pos;
}