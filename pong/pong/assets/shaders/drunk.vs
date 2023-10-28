// uniforms to keep track of time and amplitude and if drunk mode is on
uniform float time;
uniform bool drunk;
uniform float amplitude;

// store the offset for the vertex
vec2 offset;

// an array of 4 "random" numbers to assign to each vertex
float a[4] = float[4](0.62, 0.39, -0.83, -0.154);
  
// an array for the direction of each axis in each corner, to make sure the sin/cos waves never leave the window
vec2 b[4] = vec2[4](
vec2(1, 1),
vec2(1, -1),
vec2(-1, 1),
vec2(-1, -1)
);

void main()
{
	// default offset of 0
	offset = vec2(0.0f, 0.0f);
	
	// if drunk mode is on
	if(drunk)
	{
		// find the "random" value based on the vertex id
		float randomValue = a[gl_VertexID];
		
		// find the axis direction for the vertex to avoid leaving the window
		vec2 signCorrection = b[gl_VertexID];
		
		// frequency of waves
		float frequency = 5.0;
		
		// calculate the offset in x and y for the vertex, using time, amplitude and frequency, use sign correction to avoid it leaving the window
		offset = vec2((sin(randomValue * frequency * time) + signCorrection.x) * amplitude, (cos(randomValue * frequency * time) + signCorrection.y) * amplitude);
	}
	
	// transform the vertex position using a transformation matrix
    gl_Position = gl_ModelViewProjectionMatrix * mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, offset.x, offset.y, 0.0, 1.0) * gl_Vertex;

	// store the texture coordinates, for use in the fragment shader
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}