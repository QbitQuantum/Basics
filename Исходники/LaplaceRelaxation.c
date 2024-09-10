void Draw (SDL_Surface *screen, char *bmpfile)
{
	char messageText[128];
	Uint32 rmask, gmask, bmask, amask;
	SDL_Surface *picture;
	SDL_Surface *mapped_picture;
	SDL_Surface *rotozoom_picture;
	SDL_PixelFormat *pixelFormat;
	Uint8 *grayscale, *map, *curmap;
	double *unrelaxed, *relaxed, *currelax;
	int mapsize, relaxsize;
	int rowskip;
	char *pixel;
	Uint32 p;
	int x, y;
	Uint8 r, g, b, a;
	double dy;
	double t, s;
	int i;
	double c1, c2, c3, c4, ca;
	Uint8 lookupTable[256];
	double zw, zh, zf;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
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

	/* Load the image into a surface */
	printf("Loading picture: %s\n", bmpfile);
	picture = SDL_LoadBMP(bmpfile);
	if ( picture == NULL ) {
		fprintf(stderr, "Couldn't load %s: %s\n", bmpfile, SDL_GetError());
		return;
	}

	/* Convert image to a brightness map */
	printf("Allocating workbuffers\n");
	mapsize = picture->w * picture->h;
	relaxsize = mapsize * sizeof(double);
	grayscale = (Uint8 *)malloc(mapsize);
	map = (Uint8 *)malloc(mapsize);
	unrelaxed = (double *)malloc(relaxsize);
	relaxed = (double *)malloc(relaxsize);
	if ((grayscale == NULL) || (map == NULL) || (unrelaxed == NULL) || (relaxed == NULL))
	{
		fprintf(stderr, "Out of memory\n");
		return;
	}
	memset(grayscale, 0, mapsize);
	memset(map, 0, mapsize);
	memset(unrelaxed, 0, relaxsize);
	memset(relaxed, 0, relaxsize);

	printf("Converting image to brightness map\n");
	pixel = picture->pixels;
	pixelFormat = picture->format;
	rowskip = (picture->pitch - picture->w * picture->format->BytesPerPixel);
	curmap = grayscale;
	for (y=0; y < picture->h; y++) {
		for (x=0; x < picture->w; x++) {
			// Get RGB
			p = getPixel(picture, x, y);
			SDL_GetRGBA(p, pixelFormat, &r, &g, &b, &a);

			// Calculate luminance (Y = 0.3R + 0.59G + 0.11B;)
			dy  = (0.30 * r) + (0.59 * g) + (0.11 * b);
			if (dy<0.0) {
				dy=0.0;
			} else if (dy>255.0) {
				dy=255.0;
			}
			*curmap = (Uint8)dy;

			// Next pixel
			pixel += picture->format->BytesPerPixel;
			curmap++;
		}

		// Next row
		pixel += rowskip;
	}

	/* --- Prepare relaxation loop --- */

	/* Binarize luminance map */
	SDL_imageFilterBinarizeUsingThreshold(grayscale, map, mapsize, threshold);

	/* Create cos^5 based lookup table */
	t = 0.0;
	for (i = 0; i < 256; i++)
	{
		s = 1.0 - 0.5 * (1.0 + cos(t));
		s = 255.0 * s * s * s * s * s;
		lookupTable[i] = (Uint8)s;
		t += ((double)contours*2.0*3.141592653589/128.0);
	}

	/* Create new surface for relaxed image */
	mapped_picture = SDL_CreateRGBSurface(SDL_SWSURFACE, picture->w, picture->h, 32,
		rmask, gmask, bmask, amask);
	if (mapped_picture == NULL) {
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		return;
	}

	/* Apply relaxation algorithm */
	printf("Applying Laplacian relaxation: %i iterations\n", iterations);
	// Iterate to relax
	for (i = 0; i <= iterations; i++)
	{
		// Backup original
		memcpy(unrelaxed, relaxed, relaxsize);
		// Average into relaxed
		for (x=0; x < picture->w; x++) {		
			for (y=0; y < picture->h; y++) {
				// up
				c1 = GetPotential(map, grayscale, unrelaxed, x, y-1, picture->w, picture->h);
				// down
				c2 = GetPotential(map, grayscale, unrelaxed, x, y+1, picture->w, picture->h);
				// left
				c3 = GetPotential(map, grayscale, unrelaxed, x-1, y, picture->w, picture->h);
				// right
				c4 = GetPotential(map, grayscale, unrelaxed, x+1, y, picture->w, picture->h);
				// average and store
				ca = ((c1 + c2 + c3 + c4)/4.0);
				relaxed[x+y*picture->w] = ca;
			}
		}

		// Draw only sometimes
		if (((i % 10)==0) || (i==iterations)) {

			/* --- Create image with contour map --- */

			/* Fill output surface via colormap */
			currelax = relaxed;
			for (y=0; y<mapped_picture->h; y++) {
				for (x=0; x<mapped_picture->w; x++) {
					if (map[x+y*picture->w]!=0) {
						r = g = b = grayscale[x+y*picture->w];
					} else {
						r = g = b = lookupTable[(Uint8)*currelax];
					}
					pixelRGBA(mapped_picture, x, y, r, g, b, 255);
					currelax++;
				}
			}

			/* --- Scale and draw to screen --- */

			/* Scale to screen size */
			zw = (double)screen->w/(double)mapped_picture->w; 
			zh = (double)screen->h/(double)mapped_picture->h; 
			zf = (zw < zh) ? zw : zh;
			if ((rotozoom_picture=zoomSurface(mapped_picture, zf, zf, 1))==NULL) {
				fprintf(stderr, "Rotozoom failed: %s\n", SDL_GetError());
				return;
			}	

			/* Draw surface to screen */
			if ( SDL_BlitSurface(rotozoom_picture, NULL, screen, NULL) < 0 ) {
				fprintf(stderr, "Blit failed: %s\n", SDL_GetError());
				return;
			}
			SDL_FreeSurface(rotozoom_picture);

			/* Info */
			if (i != iterations) {
				sprintf(messageText,"%i", i);
				stringRGBA(screen, 8, 8, messageText, 255, 255, 255, 255);
			}

			/* Display by flipping screens */
			SDL_Flip(screen);
		}

		/* Maybe quit */
		HandleEvent();
	}

	/* Save final picture */
	if (SDL_SaveBMP(mapped_picture, "result.bmp") <0) {
		fprintf(stderr, "Save BMP failed: %s\n", SDL_GetError());
		return;
	}
	free(map);
	free(grayscale);
	free(unrelaxed);
	free(relaxed);
	SDL_FreeSurface(picture);
	SDL_FreeSurface(mapped_picture);

	return;
}