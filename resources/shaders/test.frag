#version 330 core

in VS_OUT{
    vec4 color;
    vec3 normal;
    vec3 position;
    vec2 uv;
}v2f;

uniform sampler2D tex1;

out vec4 FragColor;

void main()
{
    // diffuse
    vec3 direction = vec3(-0.9,-1.0,-0.4);

    vec3 norm = normalize(v2f.normal);
    vec3 lightDir = normalize(-direction);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0);
    vec3 ambient = vec3(0.1);

    FragColor = vec4(diffuse + ambient, 1.0);

    FragColor = texture(tex1, v2f.uv);

    //FragColor = vec4((Normal + 1)/2, 1.0);
}