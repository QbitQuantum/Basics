void DirectDraw::setDisplayMode(int width, int height, int bpp, int refreshRate) {
	debugC(ERROR_BASIC, kDebugGraphics, "DirectDraw::SetDisplayMode (%d x %d), %d bpp",
		width, height, bpp);
	assert(bpp == 16);

	Graphics::PixelFormat pixelFormat(2, 5, 6, 5, 0, 11, 5, 0, 0);
	initGraphics(width, height, true, &pixelFormat);
}