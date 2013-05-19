#define TWO_PI 6.28318531
uniform sampler2DRect src_tex_unit0; // the texture with the scene you want to blur
uniform sampler2DRect original; 

uniform vec2 dest_tex_size;
uniform float timer;


void main(void)
{
	vec2 tex_coords = vec2 (mod(gl_TexCoord[0	].s+(dest_tex_size.x)*(mod(timer, dest_tex_size.x)/2000.), dest_tex_size.x), gl_TexCoord[0].t);	
	
	
vec4 newColor  = texture2DRect(src_tex_unit0,  tex_coords).rgba;
	vec4 newColorO  = texture2DRect(original,  tex_coords).rgba;
	//if(newColorO.r>0.83){newColor.a=1.0-newColorO.r;}else{ newColor.a=1.0;};
	vec4 final=vec4(newColorO.r,newColor.r,newColor.r,1.0-newColorO.r);
	
	
//   gl_FragColor = vec4(orig.r,orig.g, orig.a,orig.a);
   gl_FragColor = final;
   	
}
