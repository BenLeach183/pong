uniform sampler2D texture;
uniform float time;

void main() {
    // Get the texture coordinates
    vec2 texCoord = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y);

    // Get the color of the pixel at the texture coordinates
    vec4 color = texture2D(texture, texCoord);

	// create vec4 to store the colour
    vec4 rainbowColor = vec4(1.0);

	// calculate colour based on texture coordinates and time
    float speed = 4.0; // Speed of the color change
    rainbowColor.r = abs(sin(gl_TexCoord[0].x * (speed - 0.39) * time) + cos(gl_TexCoord[0].y * speed * time));
    rainbowColor.g = abs(sin(gl_TexCoord[0].x * (speed + 0.33) * time) + cos(gl_TexCoord[0].y * (speed + 0.62) * time));
    rainbowColor.b = abs(sin(gl_TexCoord[0].x * (speed + 0.67) * time) + cos(gl_TexCoord[0].y * (speed - 0.154) * time));

    float intensity = 1.0; // Adjust the color intensity
    rainbowColor *= intensity;

	// mix the rainbow colour with the texture colour as output
    gl_FragColor = (rainbowColor * color) / 2.0;
}