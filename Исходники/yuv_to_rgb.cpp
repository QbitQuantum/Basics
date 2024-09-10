YUVToRGBLookup::YUVToRGBLookup(Graphics::PixelFormat format) {
	_colorTab = new int16[4 * 256]; // 2048 bytes

	int16 *Cr_r_tab = &_colorTab[0 * 256];
	int16 *Cr_g_tab = &_colorTab[1 * 256];
	int16 *Cb_g_tab = &_colorTab[2 * 256];
	int16 *Cb_b_tab = &_colorTab[3 * 256];

	_rgbToPix = new uint32[3 * 768]; // 9216 bytes

	uint32 *r_2_pix_alloc = &_rgbToPix[0 * 768];
	uint32 *g_2_pix_alloc = &_rgbToPix[1 * 768];
	uint32 *b_2_pix_alloc = &_rgbToPix[2 * 768];

	int16 CR, CB;
	int i;

	// Generate the tables for the display surface

	for (i = 0; i < 256; i++) {
		// Gamma correction (luminescence table) and chroma correction
		// would be done here. See the Berkeley mpeg_play sources.

		CR = CB = (i - 128);
		Cr_r_tab[i] = (int16) ( (0.419 / 0.299) * CR) + 0 * 768 + 256;
		Cr_g_tab[i] = (int16) (-(0.299 / 0.419) * CR) + 1 * 768 + 256;
		Cb_g_tab[i] = (int16) (-(0.114 / 0.331) * CB);
		Cb_b_tab[i] = (int16) ( (0.587 / 0.331) * CB) + 2 * 768 + 256;
	}

	// Set up entries 0-255 in rgb-to-pixel value tables.
	for (i = 0; i < 256; i++) {
		r_2_pix_alloc[i + 256] = format.RGBToColor(i, 0, 0);
		g_2_pix_alloc[i + 256] = format.RGBToColor(0, i, 0);
		b_2_pix_alloc[i + 256] = format.RGBToColor(0, 0, i);
	}

	// Spread out the values we have to the rest of the array so that we do
	// not need to check for overflow.
	for (i = 0; i < 256; i++) {
		r_2_pix_alloc[i] = r_2_pix_alloc[256];
		r_2_pix_alloc[i + 512] = r_2_pix_alloc[511];
		g_2_pix_alloc[i] = g_2_pix_alloc[256];
		g_2_pix_alloc[i + 512] = g_2_pix_alloc[511];
		b_2_pix_alloc[i] = b_2_pix_alloc[256];
		b_2_pix_alloc[i + 512] = b_2_pix_alloc[511];
	}
}