#define TWO_PI 6.28318531
uniform sampler2DRect src_tex_unit0; // the texture with the scene you want to blur
uniform sampler2DRect original; 
uniform vec2 dest_tex_size;
uniform float timer;
uniform vec4 par1;
uniform vec4 par2;

 float rand(vec2 n)
{
  return 0.5 + 0.5 *
     fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}
void main(void)
{
	vec4 final;
	vec2 tex_coords = gl_TexCoord[0].st;	
	vec4 newColor  = texture2DRect(src_tex_unit0,  tex_coords).rgba;
	vec4 newColorO  = texture2DRect(original,  tex_coords-par2.rg*100.+rand(par1.rb)).rgba;
	//if(newColorO.r>0.83){newColor.a=1.0-newColorO.r;}else{ newColor.a=1.0;};
	if(par2.y*10.0<100.0){
	final=vec4(newColor.r,newColor.r,newColor.r,1.0-newColorO.r);
	}else{
	 final=vec4(newColorO.g,newColor.r,newColor.b,1.0-newColorO.a);
	}
	
	
	
	
	
	
//   gl_FragColor = vec4(orig.r,orig.g, orig.a,orig.a);
   gl_FragColor = final;
	  	

}
