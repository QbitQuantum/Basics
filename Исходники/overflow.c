static void overlay_one_inplace(
		float *ox, float *oy, float *of, // background images and flow
		int w, int h, int pd,            // dimensions of background
		float *ppx, int pw, int ph,      // overlaid image and its size
		float posx, float posy,          // overlay position
		float zoom, float angle,         // overlay transformation
		float dx, float dy               // overlay displacement
		)
{
	float (*px)[pw][pd] = (void*)ppx;
	float dxy[2] = {dx, dy};
	float sina = sin(angle*M_PI/180.0);
	float cosa = cos(angle*M_PI/180.0);
	for (int j = 0; j < ph; j++)
	for (int i = 0; i < pw; i++)
	{
		float cij[2] = {i - pw/2.0, j - ph/2.0};
		float ai = pw/2.0 + zoom * ( cosa * cij[0] + sina * cij[1]);
		float aj = ph/2.0 + zoom * (-sina * cij[0] + cosa * cij[1]);
		ai = round(ai);
		aj = round(aj);
		float adxy[2] = {dx + ai - i, dy + aj - j};
		// TODO: correct re-sampling (!)

		setpixel(ox,w,h,pd, posx + i      , posy + j      , px[j][i]);
		setpixel(oy,w,h,pd, posx + dx + ai, posy + dy + aj, px[j][i]);
		setpixel(of,w,h,2 , posx + i      , posy + j      , adxy);
	}
}