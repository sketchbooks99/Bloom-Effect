#version 150
precision mediump float;

uniform sampler2DRect tex;
uniform sampler2DRect blur;

in vec2 vTexCoord;

out vec4 vFragColor;

void main() {
    const float gamma = 2.2;
    vec3 p = texture(tex, vTexCoord).rgb;
    vec3 b = texture(blur, vTexCoord).rgb;
    
    p += b;
    
    vec3 result = vec3(1.0) - exp(-p * 1.0);
    result = pow(result, vec3(1.0 / gamma));
    vFragColor = vec4(result, 1.0);
}

