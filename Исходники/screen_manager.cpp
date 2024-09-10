void OSScreenManager::fillRect(SurfaceNum surfaceNum, Rect *rect, byte r, byte g, byte b) {
	DirectDrawSurface *surface = getDDSurface(surfaceNum);
	if (!surface)
		return;

	// If bounds are provided, clip and use them. Otherwise, use entire surface area
	Rect surfaceRect(0, 0, surface->getWidth(), surface->getHeight());
	Rect tempRect;

	if (rect) {
		tempRect = *rect;
		tempRect.clip(surfaceRect);
	} else {
		tempRect = surfaceRect;
	}

	if (tempRect.isValidRect())
		surface->fillRect(&tempRect, r, g, b);
}