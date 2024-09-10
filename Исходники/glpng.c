int APIENTRY pngLoadRawF(FILE *fp, pngRawInfo *pinfo) {
	unsigned char header[8];
	png_structp png;
	png_infop   info;
	png_infop   endinfo;
	png_bytep   data;
   png_bytep  *row_p;
   double	fileGamma;

	png_uint_32 width, height;
	int depth, color;

	png_uint_32 i;

	if (pinfo == NULL) return 0;

	fread(header, 1, 8, fp);
	if (!png_check_sig(header, 8)) return 0;

	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info = png_create_info_struct(png);
	endinfo = png_create_info_struct(png);

	// DH: added following lines
	if (setjmp(png->jmpbuf))
	{
		png_destroy_read_struct(&png, &info, &endinfo);
		return 0;
	}
	// ~DH

	png_init_io(png, fp);
	png_set_sig_bytes(png, 8);
	png_read_info(png, info);
	png_get_IHDR(png, info, &width, &height, &depth, &color, NULL, NULL, NULL);

	pinfo->Width  = width;
	pinfo->Height = height;
	pinfo->Depth  = depth;

	/*--GAMMA--*/
	checkForGammaEnv();
	if (png_get_gAMA(png, info, &fileGamma))
		png_set_gamma(png, screenGamma, fileGamma);
	else
		png_set_gamma(png, screenGamma, 1.0/2.2);

	png_read_update_info(png, info);

	data = (png_bytep) malloc(png_get_rowbytes(png, info)*height);
	row_p = (png_bytep *) malloc(sizeof(png_bytep)*height);

	for (i = 0; i < height; i++) {
		if (StandardOrientation)
			row_p[height - 1 - i] = &data[png_get_rowbytes(png, info)*i];
		else
			row_p[i] = &data[png_get_rowbytes(png, info)*i];
	}

	png_read_image(png, row_p);
	free(row_p);

	if (color == PNG_COLOR_TYPE_PALETTE) {
		int cols;
		png_get_PLTE(png, info, (png_colorp *) &pinfo->Palette, &cols);
	}
	else {
		pinfo->Palette = NULL;
	}

	if (color&PNG_COLOR_MASK_ALPHA) {
		if (color&PNG_COLOR_MASK_PALETTE || color == PNG_COLOR_TYPE_GRAY_ALPHA)
			pinfo->Components = 2;
		else
			pinfo->Components = 4;
		pinfo->Alpha = 8;
	}
	else {
		if (color&PNG_COLOR_MASK_PALETTE || color == PNG_COLOR_TYPE_GRAY)
			pinfo->Components = 1;
		else
			pinfo->Components = 3;
		pinfo->Alpha = 0;
	}

	pinfo->Data = data;

	png_read_end(png, endinfo);
	png_destroy_read_struct(&png, &info, &endinfo);

	return 1;
}