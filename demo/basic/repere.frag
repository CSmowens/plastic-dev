#version 330 core
            
in vec3 Interpoled;

out vec4 Color;

void main()
{
    Color = vec4(Interpoled, 1.0);	
}
