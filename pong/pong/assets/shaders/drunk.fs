uniform sampler2D texture;

void main() {
    // Get the texture coordinates
    vec2 texCoord = vec2(gl_TexCoord[0].x, 1 - gl_TexCoord[0].y);

    // Get the color of the pixel at the texture coordinates
    vec4 color = texture2D(texture, texCoord);
    gl_FragColor = color;
} 