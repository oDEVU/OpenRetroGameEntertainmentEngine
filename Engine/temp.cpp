
#version 110

uniform vec4 c0;
uniform vec4 c1;
uniform vec4 c2;
uniform vec4 c3;
uniform float w0;
uniform float w1;
uniform float w2;
uniform float w3;

void main()
{
    int vertexNumber = 0;

if (gl_Color.r > 0.5)
    vertexNumber = 1;
else if (gl_Color.g > 0.5)
    vertexNumber = 2;
else if (gl_Color.b > 0.5)
    vertexNumber = 3;

vec4 color;
float weight;
if (vertexNumber == 0)
    {

    color = c0;
    weight = w0;
}
else if (vertexNumber == 1)
{

    color = c1;
    weight = w1;
}
else if (vertexNumber == 2)
{

    color = c2;
    weight = w2;
}
else if (vertexNumber == 3)
{

    color = c3;
    weight = w3;
}
gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
gl_TexCoord[0].z = weight;
gl_FrontColor = color;
}

