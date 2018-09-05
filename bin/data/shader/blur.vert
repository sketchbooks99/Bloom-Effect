#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;

in vec2 texcoord;
in vec4 color;
in vec4 position;
in vec4 normal;

out vec2 vTexCoord;

void main() {
    vTexCoord = texcoord;
    gl_Position = modelViewProjectionMatrix * position;
}
