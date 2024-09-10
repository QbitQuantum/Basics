Image calculate_ii(const Image *source) {

	Image res;
	SDL_Surface *ii_surf;
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	//ii_surf = &(*(source->surface));
	ii_surf = SDL_CreateRGBSurface(0, source->surface->w, source->surface->h,
		32, rmask, gmask, bmask, amask);

	printf("Creating ii, size {w=%d, h=%d}\n", ii_surf->w, ii_surf->h);

	for(int y = 0; y < ii_surf->h; y++) {
		for(int x = ii_surf->w - 1; x >= 0; x--) {
			//printf("pix(%d, %d) = %8x\n", x, y, getpixel(source->surface, x, y));
			Uint32 ii_value = 0;
			
			Uint32 leftSum = 0;
			for(int sx = 0; sx <= x; sx++) {
				leftSum += getpixel(source->surface, sx, y) & 0xff;
			}

			if(y == 0)
				ii_value = leftSum;
			else
				ii_value = leftSum + getpixel(ii_surf, x, y - 1);
			
			/*if(x == y && y > 0)
				printf("ii (%d, %d) = %d\t top=%d\n", x, y, ii_value, getpixel(ii_surf, x, y - 1));*/
			putpixel(ii_surf, x, y, ii_value);
		}
	}

	res.surface = ii_surf;

	SDL_Rect *dim = malloc(sizeof(SDL_Rect));
	dim->x = 0;
	dim->y = 0;
	dim->w = ii_surf->w;
	dim->h = ii_surf->h;
	res.dim = dim;

	return res;
}