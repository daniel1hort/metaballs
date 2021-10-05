#version 330 core

#define PI 3.1415926535
#define epsilon 0.001
#define MAX_CIRCLES 1000

in vec2 uv;
uniform float deltaTime;
uniform float elapsedTime;
uniform float aspectRatio;

uniform vec3[MAX_CIRCLES] circles;
uniform int circleCount;

float ratioDistance(in vec2 p1, in vec2 p2, in float aspectRatio){
	return sqrt(pow(p1.x - p2.x, 2) * pow(aspectRatio, 2) + pow(p1.y - p2.y, 2));
}
float ratioDistanceSquare(in vec2 p1, in vec2 p2, in float aspectRatio){
	return (pow(p1.x - p2.x, 2) * pow(aspectRatio, 2) + pow(p1.y - p2.y, 2));
}

float roughCircle(in vec2 pos, in float r, in float bt){
	float dist = sqrt(pow(uv.x - pos.x, 2) * pow(aspectRatio, 2) + pow(uv.y - pos.y, 2));
	return 1.0 - step(bt*.5, abs(dist - r));
}
float smoothCircle(in vec2 pos, in float r, in float bt){
	float dist = sqrt(pow(uv.x - pos.x, 2) * pow(aspectRatio, 2) + pow(uv.y - pos.y, 2));
	return 1.0 - smoothstep(0.0, bt, abs(dist - r));
}

float fillRoughCircle(in vec2 pos, in float r){
	float dist = sqrt(pow(uv.x - pos.x, 2) * pow(aspectRatio, 2) + pow(uv.y - pos.y, 2));
	return 1.0 - step(r, abs(dist - r));
}

void main(){
	vec3 green = vec3(0.0, 0.5, 0.0);

	float radius = 0.15;
	float border = 3.0*epsilon;

	float value = 0;
	for(int i = 0; i < MAX_CIRCLES; i++){
		if(i >= circleCount) break;
		value += pow(circles[i].z, 2)/ratioDistanceSquare(uv, circles[i].xy, aspectRatio);
	}
	value = step(1.0, value);

	vec3 col = green*value;
	for(int i = 0; i < MAX_CIRCLES; i++){
		if(i >= circleCount) break;
		col = mix(col, vec3(1.0,0.0,0.0), smoothCircle(circles[i].xy, circles[i].z, border));
		col = mix(col, vec3(1.0,0.0,0.0), fillRoughCircle(circles[i].xy, 0.003));
	}

	gl_FragColor = vec4(col,1.0);
}
