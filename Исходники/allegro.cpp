void rgb_to_hsv(int r, int g, int b, float *h, float *s, float *v) {	
    float maxc = (float)MAX(MAX(r, g), b);
    float minc = (float)MIN(MIN(r, g), b);
    *v = maxc;
    if(minc == maxc) {
		*h = 0;
		*s = 0;
		return;
	}

	*s = (maxc-minc) / maxc;
	float rc = (maxc-r) / (maxc-minc);
	float gc = (maxc-g) / (maxc-minc);
	float bc = (maxc-b) / (maxc-minc);
	if(r == maxc) *h = bc-gc;
	else if(g == maxc) *h = 2.0f+rc-bc;
	else *h = 4.0f+gc-rc;

	*h = *h/6.0f;
	FMOD(*h, 1.0f);
}