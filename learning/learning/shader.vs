#version 330 core
layout (location = 0) in vec3 aPos;   // λ�ñ���������λ��ֵΪ 0 
layout (location = 1) in vec2 aTexCoord; //�������������λ��ֵΪ2

out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    //ourColor = aColor; // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
	TexCoord = vec2(aTexCoord.x, 1-aTexCoord.y);
}