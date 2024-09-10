// Create a surface which has the RGB values of the base surface and the Alpha values made from an average between the RGB values of the alpha mask surface
// Both input surfaces must have the same dimensions
extern SDL_Surface *TransferAlpha( SDL_Surface *base, SDL_Surface *alpha )
{
	SDL_Surface *_outsurf = SDL_CreateRGBSurface(SDL_SWSURFACE,base->w,base->h,base->format->BitsPerPixel,base->format->Rmask,base->format->Gmask,base->format->Bmask,base->format->Amask);
	SDL_Surface *outsurf = SDL_DisplayFormatAlpha(_outsurf);
	SDL_FreeSurface(_outsurf);
	long int pix, piy;
	Uint32 pxx, pxx2, pxx3;
	Uint8 R,G,B,A;
	Uint8 A1,A2,A3,A4,A5;
	SDL_LockSurface(outsurf);
	SDL_LockSurface(base);
	SDL_LockSurface(alpha);
	pix = 0;
	piy = 0;
	while ( (pix < outsurf->w) && (piy < outsurf->h) )
	{
		pxx = getpixel(base,pix,piy);
		pxx2 = getpixel(alpha,pix,piy);
		SDL_GetRGBA(pxx,base->format,&R,&G,&B,&A5);
		SDL_GetRGBA(pxx2,alpha->format,&A1,&A2,&A3,&A4);
		A = (A1/3)+(A2/3)+(A3/3);
		A = (int)((((float)A/255.0*(float)A4)/255.0)*(float)A5);
		pxx3 = SDL_MapRGBA(outsurf->format,R,G,B,A);
		putpixel(outsurf,pix,piy,pxx3);
		pix++;
		if ( pix < outsurf->w )
			continue;
		pix = 0;
		piy++;
	}
	SDL_UnlockSurface(outsurf);
	SDL_UnlockSurface(base);
	SDL_UnlockSurface(alpha);
	return outsurf;
}