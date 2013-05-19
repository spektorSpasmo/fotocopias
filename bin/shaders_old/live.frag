uniform vec2 resolution;
uniform vec2 	spec;
uniform float time;

void main(void){
vec2 res= vec2(1440.0, 768.0);
vec2 uv=  2.0 * (gl_FragCoord.xy / res) - 1.0;
vec2 uv1=  2.0 * (gl_FragCoord.xy / res) - 1.0;
float col = 0.0;
float col1 = 0.0;
float i =1.0;
//for (float
uv.x += sin(i*20.0 + spec.x * 5.0 + time * 6.0 + uv.y  * 1.5) * spec.y;
uv.x += sin(i*20.0 + spec.x * 5.0) * spec.y;

uv.y += cos(i*20.0 + spec.y * 2.0 + time * 2.0 + uv.x  * 2.5) * spec.x;
uv.y += cos(i*10.0 + spec.y * 5.0) * spec.x;
col+=abs(0.2/uv.x) *spec.y;
col1+=abs(0.22/uv.y) *spec.x ;


gl_FragColor = vec4(col, col1, col, 1.0);
}
