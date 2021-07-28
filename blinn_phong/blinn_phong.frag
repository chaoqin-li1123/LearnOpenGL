#version 330 core

in VS_OUT
{
    in vec3 vertex_position_camera_space;
    in vec2 uv;
    in vec3 normal_camera_space;
} fs_in;

uniform sampler2D texture_sampler;
uniform vec3 light_position_camera_space;
uniform vec3 light_color;

void main(){
    // Output color = color of the texture at the specified UV
    vec3 material_color = texture(texture_sampler, fs_in.uv).rgb;

    // Caculate ambient component
    vec3 ambient = 0.05 * material_color * light_color;

    vec3 light_direction = normalize(light_position_camera_space - fs_in.vertex_position_camera_space);
    vec3 normal_direction = normalize(fs_in.normal_camera_space);
    vec3 view_direction = normalize(vec3(0.0) - fs_in.vertex_position_camera_space);

    // Calculate diffuse component.
    float diffuse_factor = max(dot(normal_direction, light_direction), 0.0);
    vec3 diffuse = diffuse_factor * material_color * light_color;

    // Caculate specular component.
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float cos_alpha = max(dot(normal_direction, halfway_direction), 0.0);
    float specular_factor = 0.0;
    if (cos_alpha > 0.0) specular_factor = pow(cos_alpha, 32.0);
    vec3 specular = specular_factor * vec3(0.3);


    gl_FragColor = vec4(specular + diffuse + ambient, 0.0);
}