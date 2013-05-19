#define TWO_PI 6.28318531
uniform sampler2DRect src_tex_unit0; // the texture with the scene you want to blur

uniform vec2 dest_tex_size;
uniform int dirs;
uniform int res;
uniform float radio;
uniform float amp;
uniform float div;

void main(void)
{
	vec2 blurSize;
	 blurSize = vec2(1.0/dest_tex_size.x,1.0/dest_tex_size.y);
	vec4 d=vec4(2,4,8,16)*6.;
   float dir ;
   int rz= res;
   vec2 tmpoint;
   vec2 print= dest_tex_size/6.1;
	vec2 pntorig=vec2(60., 60.);
   vec2 dist=vec2(330., 3300.);
   vec4 trace;
 	vec2 tex_coords = gl_TexCoord[0].st;
 	vec4 orig ;
	vec4 sum = vec4(0.0);
	float mm= div;
	float rs= 6.15;
	float dx;
	float dy;
	vec2 point;
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   for(int j=0; j<dirs; j++){
   	float dir = float(j)*TWO_PI/float(dirs) + radio;
   	 for(int g=0; g<4;g++){
   	 		
   	 		
			  dx = d[g] * sin(dir) * (blurSize.x*amp) ;
	          dy = d[g] * cos(dir)  * (blurSize.y*amp) ;
	          point= vec2(dx, dy) + tex_coords;
			sum[g] += texture2DRect(src_tex_unit0, point)[g]/mm;
   	 	
   	 	}
    
   
   }
   orig.a = sum.a;
   orig=texture2DRect(src_tex_unit0, tex_coords).rgba;
  
	
  //vec4 desCol;
	//if( orig.a > 0.9) orig.a = texture2DRect(src_tex_unit0, tex_coords-4.).a+texture2DRect(src_tex_unit0, tex_coords+4.).a/2.; 
    if( orig.a < 0.1) orig.a = texture2DRect(src_tex_unit0, tex_coords-4.).a+texture2DRect(src_tex_unit0, tex_coords+4.).a/2.; 

   gl_FragColor = vec4(orig.r,orig.g, orig.a,orig.a);
   //gl_FragColor = vec4(orig.r,orig.g, orig.b,orig.a);
  if(gl_FragCoord.x>=pntorig.x  && gl_FragCoord.y>=pntorig.y && gl_FragCoord.x<=pntorig.x+dist.x  && gl_FragCoord.y<=pntorig.y+dist.y   ){

	  	
   	}
}
