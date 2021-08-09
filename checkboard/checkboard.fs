#version 450 core

out vec4 color;

void main(){
    // Output color = color of the texture at the specified UV
    int u = int(gl_FragCoord.x) / 40;
    int v = int(gl_FragCoord.y) / 40;
    if ((u + v) % 2 == 0) {
        color = vec4(0.0, 0.0, 0.0, 0.1);
    }
    else {
        color = vec4(0.0, 0.0, 1.0, 0.1);
    }
}