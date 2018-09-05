#version 150
precision mediump float;

uniform sampler2DRect tex;
uniform bool horizontal;
uniform float strength;

float weight[5] = float[](0.382928, 0.241732, 0.060598, 0.005977, 0.000229);

in vec2 vTexCoord;

out vec4 vFragColor;

void main() {
    vec3 color = vec3(0.0);
    color += texture(tex, vTexCoord + vec2(0.0, 0)).rgb * weight[0];
    if(horizontal) {
        for(int i = 1; i < 5; i++) {
            color += texture(tex, vTexCoord + vec2(strength * i, 0.0)).rgb * weight[i];
            color += texture(tex, vTexCoord - vec2(strength * i, 0.0)).rgb * weight[i];
        }
    } else {
        for(int i = 1; i < 5; i++) {
            color += texture(tex, vTexCoord + vec2(0.0, strength * i)).rgb * weight[i];
            color += texture(tex, vTexCoord - vec2(0.0, strength * i)).rgb * weight[i];
        }
    }
    
    vFragColor = vec4(color.rgb, 1.0);
}
