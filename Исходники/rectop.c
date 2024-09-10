void buf_rectfill_area(unsigned char *rect, float *rectf, int width, int height, const float col[4], int x1, int y1, int x2, int y2)
{
	int i, j;
	float a; /* alpha */
	float ai; /* alpha inverted */
	float aich; /* alpha, inverted, ai/255.0 - Convert char to float at the same time */
	if ((!rect && !rectf) || (!col) || col[3]==0.0f)
		return;
	
	/* sanity checks for coords */
	CLAMP(x1, 0, width);
	CLAMP(x2, 0, width);
	CLAMP(y1, 0, height);
	CLAMP(y2, 0, height);

	if (x1>x2) SWAP(int,x1,x2);
	if (y1>y2) SWAP(int,y1,y2);
	if (x1==x2 || y1==y2) return;
	
	a = col[3];
	ai = 1-a;
	aich = ai/255.0f;

	if (rect) {
		unsigned char *pixel; 
		unsigned char chr=0, chg=0, chb=0;
		float fr=0, fg=0, fb=0;

		const int alphaint= FTOCHAR(a);
		
		if (a == 1.0f) {
			chr = FTOCHAR(col[0]);
			chg = FTOCHAR(col[1]);
			chb = FTOCHAR(col[2]);
		} else {
			fr = col[0]*a;
			fg = col[1]*a;
			fb = col[2]*a;
		}
		for (j = 0; j < y2-y1; j++) {
			for (i = 0; i < x2-x1; i++) {
				pixel = rect + 4 * (((y1 + j) * width) + (x1 + i));
				if (pixel >= rect && pixel < rect+ (4 * (width * height))) {
					if (a == 1.0f) {
						pixel[0] = chr;
						pixel[1] = chg;
						pixel[2] = chb;
						pixel[3] = 255;
					} else {
						int alphatest;
						pixel[0] = (char)((fr + ((float)pixel[0]*aich))*255.0f);
						pixel[1] = (char)((fg + ((float)pixel[1]*aich))*255.0f);
						pixel[2] = (char)((fb + ((float)pixel[2]*aich))*255.0f);
						pixel[3] = (char)((alphatest= ((int)pixel[3] + alphaint)) < 255 ? alphatest : 255);
					}
				}
			}
		}
	}
	
	if (rectf) {
		float *pixel;
		for (j = 0; j < y2-y1; j++) {
			for (i = 0; i < x2-x1; i++) {
				pixel = rectf + 4 * (((y1 + j) * width) + (x1 + i));
				if (a == 1.0f) {
					pixel[0] = col[0];
					pixel[1] = col[1];
					pixel[2] = col[2];
					pixel[3] = 1.0f;
				} else {
					float alphatest;
					pixel[0] = (col[0]*a) + (pixel[0]*ai);
					pixel[1] = (col[1]*a) + (pixel[1]*ai);
					pixel[2] = (col[2]*a) + (pixel[2]*ai);
					pixel[3] = (alphatest= (pixel[3] + a)) < 1.0f ? alphatest : 1.0f;
				}
			}
		}
	}
}