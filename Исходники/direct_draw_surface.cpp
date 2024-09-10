void DirectDrawSurface::create(int w, int h) {
	Graphics::PixelFormat pixelFormat(2, 5, 6, 5, 0, 11, 5, 0, 0);
	_surface = new Graphics::ManagedSurface(w, h, pixelFormat);
	_disposeAfterUse = DisposeAfterUse::YES;
}