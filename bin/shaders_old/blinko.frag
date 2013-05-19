#define TWO_PI 6.28318531
uniform sampler2DRect src_tex_unit0; // the texture with the scene you want to blur
uniform float timer;
uniform vec2 dest_tex_size;


void main(void){

	vec2 tex_coords = gl_TexCoord[0].st;	
	vec4 newColor  = texture2DRect(src_tex_unit0,  tex_coords).rgba;

	 if (mod(timer, 3.0)==0.0){

if(newColor.r<0.83){newColor.a=newColor.r;}else{1.0;};

}else{

newColor.a=0.0;
};
	
	vec4 final=vec4(newColor.g,newColor.b,newColor.r,1.0-newColor.a);
	
	
//   gl_FragColor = vec4(orig.r,orig.g, orig.a,orig.a);
   gl_FragColor = final;
	  	
   	
}
