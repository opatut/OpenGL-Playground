uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float total_time;
bool infinite = true;

float PI = 2.0 * asin(1.0);

struct WaveEmitter {
	vec2 mPosition; // = vec2(0.5, 0.5);
	float mAmplitude; // = 0.01;	// factor of final displacement
	float mVelocity; // = 0.05;		// screens per second
	float mWavelength; // = 0.3;	// screens

};

float GetPeriodTime(WaveEmitter emitter) {
    return emitter.mWavelength / emitter.mVelocity;
}

float emitter_size = 3.0;
WaveEmitter emitter[3];


float GetPhase(vec2 point, WaveEmitter emit, float time) {
	float distance = sqrt( pow(point.x - emit.mPosition.x,2) + pow(point.y - emit.mPosition.y, 2) );
	if (!infinite && distance / emit.mVelocity >= time) {
		return 0.0;
	} else {
		return sin((time / GetPeriodTime(emit) - distance / emit.mWavelength) * 2 * PI);
	}
}

vec2 transformCoord(vec2 orig) {
	vec2 final = orig;
	for(int i = 0; i < emitter_size; ++i) {
		vec2 rel = orig - emitter[i].mPosition;
		float fac = GetPhase(orig, emitter[i], total_time) * emitter[i].mAmplitude;
		final += fac * rel;
	}
	return final;
}

vec4 transformColor(vec4 c, vec2 p) {
	float fac = 0;
	float a = 0;
	for(int i = 0; i < emitter_size; ++i) {
		fac += GetPhase(p, emitter[i], total_time) * emitter[i].mAmplitude;
		a = emitter[i].mAmplitude;
	}
	fac = (fac / a + 1.0 ) * 0.5;
	c = c * (2.0 -  fac);
    return c;
}

vec4 blur(sampler2D tex, vec2 p) {
    vec4 c = texture2D(tex, p);
    float w = c[0] + c[1] + c[2];
    float i = 1;
    vec4 cn = c;
    if(w > 2.2) {
        float r = 1.0;
        for(float x = -r; x <= r; x+=r / 2.0 / 10) {
            for(float y = -r; y <= r; y+= r / 2.0 / 10) {
                float d = r * sqrt(2) - sqrt(x*x + y*y);
                cn += texture2D(tex, p + vec2(x,y)) * d;
                w += d;
            }
        }
        return cn / i;
    }
    return c;
}

void main() {
	WaveEmitter emit0;
	emit0.mPosition = vec2(0.1,0.7);
	emit0.mAmplitude = 0.005;
	emit0.mVelocity = 0.06;
	emit0.mWavelength = 1.0;
	emitter[0] = emit0;

	WaveEmitter emit1;
	emit1.mPosition = vec2(0.8,-0.1);
	emit1.mAmplitude = 0.005;
	emit1.mVelocity = 0.07;
	emit1.mWavelength = 0.6;
	emitter[1] = emit1;

	WaveEmitter emit2;
	emit2.mPosition = vec2(1.1,0.9);
	emit2.mAmplitude = 0.005;
	emit2.mVelocity = 0.05;
	emit2.mWavelength = 0.8;
	emitter[2] = emit2;

	vec2 coord = transformCoord(gl_TexCoord[0].st);
	//gl_FragColor = texture2D(texture1, coord), coord;
    vec4 color = texture2D(texture1, coord);
    vec4 blur = blur(texture1, coord);
    if(gl_TexCoord[0].x < 0.5) {
        color = blur;
    }

    float a = gl_Color.r;

    vec4 color2 = texture2D(texture2, coord);
    gl_FragColor = (1.0 - a) * color2 + a * color, coord;

	//gl_FragColor = transformColor(color, coord), coord;
}
