rdpShadowSurface* shadow_surface_new(rdpShadowServer* server, int x, int y, int width, int height)
{
	rdpShadowSurface* surface;

	surface = (rdpShadowSurface*) calloc(1, sizeof(rdpShadowSurface));

	if (!surface)
		return NULL;

	surface->server = server;

	surface->x = x;
	surface->y = y;
	surface->width = width;
	surface->height = height;
	surface->scanline = (surface->width + (surface->width % 4)) * 4;

	surface->data = (BYTE*) calloc(1, surface->scanline * surface->height);
	if (!surface->data)
	{
		free (surface);
		return NULL;
	}

	if (!InitializeCriticalSectionAndSpinCount(&(surface->lock), 4000))
	{
		free (surface->data);
		free (surface);
		return NULL;
	}

	region16_init(&(surface->invalidRegion));

	return surface;
}