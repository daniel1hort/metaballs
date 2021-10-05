#version 400 core

out vec2 uv;
//uniform float deltaTime;
vec2 quadVertices[4];

void main(){
	quadVertices[0] = vec2(-1.0, -1.0);
	quadVertices[1] = vec2(1.0, -1.0);
	quadVertices[2] = vec2(-1.0, 1.0);
	quadVertices[3] = vec2(1.0, 1.0);

	gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);
	uv = gl_Position.xy * 0.5 + 0.5;
}
