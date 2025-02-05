#version 410

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;


out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentUV;

uniform mat4 cameraMatrix;

void main() {
    gl_Position.xy = (cameraMatrix * vec4(vertexPosition, 0.0, 1.0)).xy;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    fragmentColor = vertexColor;

    fragmentPosition = vertexPosition;

    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y); // flips UV axis
}