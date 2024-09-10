int xf_CreateSurface(RdpgfxClientContext* context, RDPGFX_CREATE_SURFACE_PDU* createSurface)
{
	size_t size;
	UINT32 bytesPerPixel;
	xfGfxSurface* surface;
	xfContext* xfc = (xfContext*) context->custom;

	surface = (xfGfxSurface*) calloc(1, sizeof(xfGfxSurface));

	if (!surface)
		return -1;

	surface->surfaceId = createSurface->surfaceId;
	surface->width = (UINT32) createSurface->width;
	surface->height = (UINT32) createSurface->height;
	surface->alpha = (createSurface->pixelFormat == PIXEL_FORMAT_ARGB_8888) ? TRUE : FALSE;
	surface->format = PIXEL_FORMAT_XRGB32;

	surface->scanline = surface->width * 4;
	surface->scanline += (surface->scanline % (xfc->scanline_pad / 8));

	size = surface->scanline * surface->height;
	surface->data = (BYTE*) _aligned_malloc(size, 16);

	if (!surface->data)
	{
		free (surface);
		return -1;
	}

	ZeroMemory(surface->data, size);

	if ((xfc->depth == 24) || (xfc->depth == 32))
	{
		surface->image = XCreateImage(xfc->display, xfc->visual, xfc->depth, ZPixmap, 0,
				(char*) surface->data, surface->width, surface->height, xfc->scanline_pad, surface->scanline);
	}
	else
	{
		bytesPerPixel = (FREERDP_PIXEL_FORMAT_BPP(xfc->format) / 8);
		surface->stageStep = surface->width * bytesPerPixel;
		surface->stageStep += (surface->stageStep % (xfc->scanline_pad / 8));
		size = surface->stageStep * surface->height;

		surface->stage = (BYTE*) _aligned_malloc(size, 16);

		if (!surface->stage)
		{
			free (surface->data);
			free (surface);
			return -1;
		}

		ZeroMemory(surface->stage, size);

		surface->image = XCreateImage(xfc->display, xfc->visual, xfc->depth, ZPixmap, 0,
				(char*) surface->stage, surface->width, surface->height, xfc->scanline_pad, surface->stageStep);
	}

	context->SetSurfaceData(context, surface->surfaceId, (void*) surface);

	return 1;
}