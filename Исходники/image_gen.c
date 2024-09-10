void BKE_image_buf_fill_checker(unsigned char *rect, float *rect_float, int width, int height)
{
	/* these two passes could be combined into one, but it's more readable and 
	* easy to tweak like this, speed isn't really that much of an issue in this situation... */
 
	int checkerwidth= 32, dark= 1;
	int x, y;

	unsigned char *rect_orig= rect;
	float *rect_float_orig= rect_float;

	
	float h=0.0, hoffs=0.0, hue=0.0, s=0.9, v=0.9, r, g, b;

	/* checkers */
	for(y= 0; y<height; y++) {
		dark= powf(-1.0f, floorf(y / checkerwidth));
		
		for(x= 0; x<width; x++) {
			if (x % checkerwidth == 0) dark= -dark;
			
			if (rect_float) {
				if (dark > 0) {
					rect_float[0]= rect_float[1]= rect_float[2]= 0.25f;
					rect_float[3]= 1.0f;
				} else {
					rect_float[0]= rect_float[1]= rect_float[2]= 0.58f;
					rect_float[3]= 1.0f;
				}
				rect_float+= 4;
			}
			else {
				if (dark > 0) {
					rect[0]= rect[1]= rect[2]= 64;
					rect[3]= 255;
				} else {
					rect[0]= rect[1]= rect[2]= 150;
					rect[3]= 255;
				}
				rect+= 4;
			}
		}
	}

	rect= rect_orig;
	rect_float= rect_float_orig;

	/* 2nd pass, colored + */
	for(y= 0; y<height; y++) {
		hoffs= 0.125f * floorf(y / checkerwidth);
		
		for(x= 0; x<width; x++) {
			h= 0.125f * floorf(x / checkerwidth);
			
			if ((fabs((x % checkerwidth) - (checkerwidth / 2)) < 4) &&
				(fabs((y % checkerwidth) - (checkerwidth / 2)) < 4)) {
				
				if ((fabs((x % checkerwidth) - (checkerwidth / 2)) < 1) ||
					(fabs((y % checkerwidth) - (checkerwidth / 2)) < 1)) {
					
					hue= fmodf(fabs(h-hoffs), 1.0f);
					hsv_to_rgb(hue, s, v, &r, &g, &b);
					
					if (rect) {
						rect[0]= (char)(r * 255.0f);
						rect[1]= (char)(g * 255.0f);
						rect[2]= (char)(b * 255.0f);
						rect[3]= 255;
					}
					
					if (rect_float) {
						rect_float[0]= r;
						rect_float[1]= g;
						rect_float[2]= b;
						rect_float[3]= 1.0f;
					}
				}
			}

			if (rect_float) rect_float+= 4;
			if (rect) rect+= 4;
		}
	}
}