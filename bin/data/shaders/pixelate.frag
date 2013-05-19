#define TWO_PI 6.28318531
uniform sampler2DRect src_tex_unit0; // the texture with the scene you want to blur

uniform vec2 dest_tex_size;
uniform int dirs;

uniform float radio;
uniform float amp;
uniform float div;
//uniform float blurSize; // I've chosen this size because this will result in that every step will be one pixel wide if the RTScene texture is of size 512x512
 
void main(void)
{
	vec2 blurSize = vec2(1.0/dest_tex_size.x,1.0/dest_tex_size.y);
	vec4 d=vec4(2,4,8,16)*0.01;
	
   	float dir ;
    vec2 tmpoint;
   //vec2 point;
   
//   vec2 pntorig=vec2(60., 60.);
//   vec2 dist=vec2(330., 3300.);
//   vec4 trace;
 
 	vec2 tex_coords = gl_TexCoord[0].st;
 	vec4 orig ;
	vec4 sum = vec4(0.0)*0.01;
	float mm= div;
	float rs= 6.15;
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   for(int j=0; j<dirs; j++){
   	float dir = 1./float(j)*TWO_PI/float(dirs) + radio;
   	 for(int g=0; g<4;g++){
   	 		
   	 		
			 float dx = d[g] * sin(dir) + amp ;
	         float dy = d[g] * cos(dir) + amp ;
	         vec2 point= vec2(dx, dy) + gl_FragCoord.xy/dest_tex_size;

			sum[g] += 0.02;
   	 	
   	 	}
    
   
   }
   orig = vec4(sum.rgb, 0.5);
   

	
  //vec4 desCol;
	//if( orig.a > 0.9) orig.a = texture2DRect(src_tex_unit0, tex_coords-4.).a+texture2DRect(src_tex_unit0, tex_coords+4.).a/2.; 
   // if( orig.a < 0.1) orig.a = texture2DRectRect(src_tex_unit0, tex_coords-4.).a+texture2DRectRect(src_tex_unit0, tex_coords+4.).a/2.; 
 if( orig.a > 0.9) orig.a = texture2DRect(src_tex_unit0, tex_coords-4.).a+texture2DRect(src_tex_unit0, tex_coords+4.).a/4.; 
    if( orig.a < 0.1) orig.a = texture2DRect(src_tex_unit0, tex_coords-4.).a+texture2DRect(src_tex_unit0, tex_coords+4.).a/8.; 

  
   gl_FragColor = vec4(orig.a,orig.a, orig.a,orig.a);
   gl_FragColor = orig;
  // gl_FragColor = texture2DRect(src_tex_unit0, tex_coords);
//  if(gl_FragCoord.x>=pntorig.x  && gl_FragCoord.y>=pntorig.y && gl_FragCoord.x<=pntorig.x+dist.x  && gl_FragCoord.y<=pntorig.y+dist.y   ){
////   	orig.a+=sum.r;
//	//gl_FragColor ==vec4(1,0,1,1);
//	//if(amp<5.) gl_FragColor = vec4(1.); 
//	  	
//   	}
}
