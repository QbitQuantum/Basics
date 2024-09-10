bool createScreenShot(Graphics::Surface &surf) {
	Graphics::PixelFormat screenFormat = g_system->getScreenFormat();
	//convert surface to 2 bytes pixel format to avoid problems with palette saving and loading
	if ((screenFormat.bytesPerPixel == 1) || (screenFormat.bytesPerPixel == 2)) {
		return grabScreen565(&surf);
	} else {
		Graphics::Surface *screen = g_system->lockScreen();
		if (!screen) {
			return false;
		}
		surf.create(screen->w, screen->h, Graphics::PixelFormat(4, 8, 8, 8, 8, 24, 16, 8, 0));
		for (uint y = 0; y < screen->h; ++y) {
			for (uint x = 0; x < screen->w; ++x) {
				byte r = 0, g = 0, b = 0, a = 0;
				uint32 col = READ_UINT32(screen->getBasePtr(x, y));
				screenFormat.colorToARGB(col, a, r, g, b);
				*((uint32 *)surf.getBasePtr(x, y)) = Graphics::ARGBToColor<Graphics::ColorMasks<8888> >(a, r, g, b);
			}
		}
		g_system->unlockScreen();
		return true;
	}
}