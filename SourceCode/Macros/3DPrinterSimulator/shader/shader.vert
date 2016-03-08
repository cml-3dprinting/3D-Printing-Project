attribute vec4 pos;
attribute float index;
attribute float alpha;

uniform mat4 mvp;
uniform mat4 m;
uniform float process;
uniform int cooling;
uniform float angle;

varying vec4 vv4colour;

float a, d;

void main() {

	if (process == -1) {
		vv4colour = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else if (process == -2) {
		vv4colour = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else {
		a = process - index < cooling ? (process - index) / cooling : 1;
		d = (1 - (m[0][2] * pos.x + m[1][2] * pos.y + m[2][2] * pos.z + m[3][2])) / 2;
		
		if (alpha == -1) vv4colour = vec4(0, 1, 0, 1.0);
		else if (alpha > angle) vv4colour = vec4(1, 0, 0, 1.0);
		else vv4colour = vec4(1, 1, 1, 1.0);

		// vv4colour = vec4(1.0 - d, a - d, a - d, 1.0);
		// vv4colour = vec4(1, 1 - alpha, 1 - alpha, 1.0);
		vv4colour = vec4(1.0 - d, a - d - alpha, a - d - alpha, 1.0);
	}

	gl_Position = mvp * pos;

}

