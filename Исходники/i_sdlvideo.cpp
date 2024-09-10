//
// I_BuildPixelFormatFromSDLSurface
//
// Helper function that extracts information about the pixel format
// from an SDL_Surface and uses it to initialize a PixelFormat object.
// Note: the SDL_Surface should be locked prior to calling this.
//
static void I_BuildPixelFormatFromSDLSurface(const SDL_Surface* sdlsurface, PixelFormat* format)
{
	const SDL_PixelFormat* sdlformat = sdlsurface->format;
	uint8_t bpp = sdlformat->BitsPerPixel;

	// handle SDL not reporting correct Ashift/Aloss
	uint8_t aloss = bpp == 32 ? 0 : 8;
	uint8_t ashift = bpp == 32 ?  48 - sdlformat->Rshift - sdlformat->Gshift - sdlformat->Bshift : 0;
	
	// Create the PixelFormat specification
	*format = PixelFormat(
			bpp,
			8 - aloss, 8 - sdlformat->Rloss, 8 - sdlformat->Gloss, 8 - sdlformat->Bloss,
			ashift, sdlformat->Rshift, sdlformat->Gshift, sdlformat->Bshift);
}