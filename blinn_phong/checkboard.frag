#version 330 core

void main(){
    // Output color = color of the texture at the specified UV
    int u = int(gl_FragCoord.x) / 40;
    int v = int(gl_FragCoord.y) / 40;
    if ((u + v) % 2 == 0) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 0.1);
    }
    else {
        gl_FragColor = vec4(0.0, 0.0, 1.0, 0.1);
    }
}