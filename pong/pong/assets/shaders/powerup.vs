void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// store the texture coordinates, for use in the fragment shader
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}