/* Win32 icon mask semantics are different from those of SDL:
     SDL applies the mask to the icon and copies result to desktop.
     Win32 applies the mask to the desktop and XORs the icon on.
   This means that the SDL mask needs to be applied to the icon and
   then inverted and passed to Win32.
*/
void WIN_SetWMIcon(_THIS, SDL_Surface *icon, Uint8 *mask)
{
#ifdef DISABLE_ICON_SUPPORT
	return;
#else
	SDL_Palette *pal_256;
	SDL_Surface *icon_256;
	Uint8 *pdata, *pwin32;
	Uint8 *mdata, *mwin32, m = 0;
	int icon_len;
	int icon_plen;
	int icon_mlen;
	int icon_pitch;
	int mask_pitch;
	SDL_Rect bounds;
	int i, skip;
	int row, col;
	struct /* quasi-BMP format */ Win32Icon {
		Uint32 biSize;
		Sint32 biWidth;
		Sint32 biHeight;
		Uint16 biPlanes;
		Uint16 biBitCount;
		Uint32 biCompression;
		Uint32 biSizeImage;
		Sint32 biXPelsPerMeter;
		Sint32 biYPelsPerMeter;
		Uint32 biClrUsed;
		Uint32 biClrImportant;
		struct /* RGBQUAD -- note it's BGR ordered */ {
			Uint8 rgbBlue;
			Uint8 rgbGreen;
			Uint8 rgbRed;
			Uint8 rgbReserved;
		} biColors[256];
		/* Pixels:
		Uint8 pixels[]
		*/
		/* Mask:
		Uint8 mask[]
		*/
	} *icon_win32;
	
	/* Allocate the win32 bmp icon and set everything to zero */
	icon_pitch = ((icon->w+3)&~3);
	mask_pitch = ((icon->w+7)/8);
	icon_plen = icon->h*icon_pitch;
	icon_mlen = icon->h*mask_pitch;
	icon_len = sizeof(*icon_win32)+icon_plen+icon_mlen;
	icon_win32 = (struct Win32Icon *)alloca(icon_len);
	if ( icon_win32 == NULL ) {
		return;
	}
	memset(icon_win32, 0, icon_len);

	/* Set the basic BMP parameters */
	icon_win32->biSize = sizeof(*icon_win32)-sizeof(icon_win32->biColors);
	icon_win32->biWidth = icon->w;
	icon_win32->biHeight = icon->h*2;
	icon_win32->biPlanes = 1;
	icon_win32->biBitCount = 8;
	icon_win32->biSizeImage = icon_plen+icon_mlen;

	/* Allocate a standard 256 color icon surface */
	icon_256 = SDL_CreateRGBSurface(SDL_SWSURFACE, icon->w, icon->h,
					 icon_win32->biBitCount, 0, 0, 0, 0);
	if ( icon_256 == NULL ) {
		return;
	}
	pal_256 = icon_256->format->palette;
	if (icon->format->palette && 
		(icon->format->BitsPerPixel == icon_256->format->BitsPerPixel)){
		Uint8 black;
		memcpy(pal_256->colors, icon->format->palette->colors,
					pal_256->ncolors*sizeof(SDL_Color));
		/* Make sure that 0 is black! */
		black = SDL_FindColor(pal_256, 0x00, 0x00, 0x00);
		pal_256->colors[black] = pal_256->colors[0];
		pal_256->colors[0].r = 0x00;
		pal_256->colors[0].g = 0x00;
		pal_256->colors[0].b = 0x00;
	} else {
		SDL_DitherColors(pal_256->colors,
					icon_256->format->BitsPerPixel);
	}

	/* Now copy color data to the icon BMP */
	for ( i=0; i<(1<<icon_win32->biBitCount); ++i ) {
		icon_win32->biColors[i].rgbRed = pal_256->colors[i].r;
		icon_win32->biColors[i].rgbGreen = pal_256->colors[i].g;
		icon_win32->biColors[i].rgbBlue = pal_256->colors[i].b;
	}

	/* Convert icon to a standard surface format.  This may not always
	   be necessary, as Windows supports a variety of BMP formats, but
	   it greatly simplifies our code.
	*/ 
        bounds.x = 0;
        bounds.y = 0;
        bounds.w = icon->w;
        bounds.h = icon->h;
        if ( SDL_LowerBlit(icon, &bounds, icon_256, &bounds) < 0 ) {
		SDL_FreeSurface(icon_256);
                return;
	}

	/* Copy pixels upside-down to icon BMP, masked with the icon mask */
	if ( SDL_MUSTLOCK(icon_256) || (icon_256->pitch != icon_pitch) ) {
		SDL_FreeSurface(icon_256);
		SDL_SetError("Warning: Unexpected icon_256 characteristics");
		return;
	}
	pdata = (Uint8 *)icon_256->pixels;
	mdata = mask;
	pwin32 = (Uint8 *)icon_win32+sizeof(*icon_win32)+icon_plen-icon_pitch;
	skip = icon_pitch - icon->w;
	for ( row=0; row<icon->h; ++row ) {
		for ( col=0; col<icon->w; ++col ) {
			if ( (col%8) == 0 ) {
				m = *mdata++;
			}
			if ( (m&0x80) != 0x00 ) {
				*pwin32 = *pdata;
			}
			m <<= 1;
			++pdata;
			++pwin32;
		}
		pdata  += skip;
		pwin32 += skip;
		pwin32 -= 2*icon_pitch;
	}
	SDL_FreeSurface(icon_256);

	/* Copy mask inverted and upside-down to icon BMP */
	mdata = mask;
	mwin32 = (Uint8 *)icon_win32
			+sizeof(*icon_win32)+icon_plen+icon_mlen-mask_pitch;
	for ( row=0; row<icon->h; ++row ) {
		for ( col=0; col<mask_pitch; ++col ) {
			*mwin32++ = ~*mdata++;
		}
		mwin32 -= 2*mask_pitch;
	}

	/* Finally, create the icon handle and set the window icon */
	screen_icn = CreateIconFromResourceEx((Uint8 *)icon_win32, icon_len,
			TRUE, 0x00030000, icon->w, icon->h, LR_DEFAULTCOLOR);
	if ( screen_icn == NULL ) {
		SDL_SetError("Couldn't create Win32 icon handle");
	} else {
		SetClassLong(SDL_Window, GCL_HICON, (LONG)screen_icn);
	}
#endif /* DISABLE_ICON_SUPPORT */
}