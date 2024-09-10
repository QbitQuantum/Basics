void RenderManager::blitSurfaceToSurface(const Graphics::Surface &src, const Common::Rect &_srcRect , Graphics::Surface &dst, int _x, int _y, uint32 colorkey) {
	Common::Rect srcRect = _srcRect;
	if (srcRect.isEmpty())
		srcRect = Common::Rect(src.w, src.h);
	srcRect.clip(src.w, src.h);
	Common::Rect dstRect = Common::Rect(-_x + srcRect.left , -_y + srcRect.top, -_x + srcRect.left + dst.w, -_y + srcRect.top + dst.h);
	srcRect.clip(dstRect);

	if (srcRect.isEmpty() || !srcRect.isValidRect())
		return;

	Graphics::Surface *srcAdapted = src.convertTo(dst.format);
	uint32 keycolor = colorkey & ((1 << (src.format.bytesPerPixel << 3)) - 1);

	// Copy srcRect from src surface to dst surface
	const byte *srcBuffer = (const byte *)srcAdapted->getBasePtr(srcRect.left, srcRect.top);

	int xx = _x;
	int yy = _y;

	if (xx < 0)
		xx = 0;
	if (yy < 0)
		yy = 0;

	if (_x >= dst.w || _y >= dst.h) {
		srcAdapted->free();
		delete srcAdapted;
		return;
	}

	byte *dstBuffer = (byte *)dst.getBasePtr(xx, yy);

	int32 w = srcRect.width();
	int32 h = srcRect.height();

	for (int32 y = 0; y < h; y++) {
		switch (srcAdapted->format.bytesPerPixel) {
		case 1: {
			const uint *srcTemp = (const uint *)srcBuffer;
			uint *dstTemp = (uint *)dstBuffer;
			for (int32 x = 0; x < w; x++) {
				if (*srcTemp != keycolor)
					*dstTemp = *srcTemp;
				srcTemp++;
				dstTemp++;
			}
		}
		break;

		case 2: {
			const uint16 *srcTemp = (const uint16 *)srcBuffer;
			uint16 *dstTemp = (uint16 *)dstBuffer;
			for (int32 x = 0; x < w; x++) {
				if (*srcTemp != keycolor)
					*dstTemp = *srcTemp;
				srcTemp++;
				dstTemp++;
			}
		}
		break;

		case 4: {
			const uint32 *srcTemp = (const uint32 *)srcBuffer;
			uint32 *dstTemp = (uint32 *)dstBuffer;
			for (int32 x = 0; x < w; x++) {
				if (*srcTemp != keycolor)
					*dstTemp = *srcTemp;
				srcTemp++;
				dstTemp++;
			}
		}
		break;

		default:
			break;
		}
		srcBuffer += srcAdapted->pitch;
		dstBuffer += dst.pitch;
	}

	srcAdapted->free();
	delete srcAdapted;
}