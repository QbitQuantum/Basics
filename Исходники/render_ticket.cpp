void RenderTicket::drawToSurface(Graphics::Surface *_targetSurface, Common::Rect *dstRect, Common::Rect *clipRect) const {
	TransparentSurface src(*getSurface(), false);
	bool doDelete = false;
	if (!clipRect) {
		doDelete = true;
		clipRect = new Common::Rect();
		clipRect->setWidth(getSurface()->w * _transform._numTimesX);
		clipRect->setHeight(getSurface()->h * _transform._numTimesY);
	}

	if (_owner) {
		if (_transform._alphaDisable) {
			src.setAlphaMode(TransparentSurface::ALPHA_OPAQUE);
		} else {
			src.setAlphaMode(_owner->getAlphaType());
		}
	}

	if (_transform._numTimesX * _transform._numTimesY == 1) {

		src.blit(*_targetSurface, dstRect->left, dstRect->top, _transform._flip, clipRect, _transform._rgbaMod, clipRect->width(), clipRect->height(), _transform._blendMode);

	} else {

		// clipRect is a subrect of the full numTimesX*numTimesY rect
		Common::Rect subRect;

		int y = 0;
		int w = getSurface()->w;
		int h = getSurface()->h;
		assert(w == _dstRect.width() / _transform._numTimesX);
		assert(h == _dstRect.height() / _transform._numTimesY);

		int basex = dstRect->left - clipRect->left;
		int basey = dstRect->top - clipRect->top;

		for (int ry = 0; ry < _transform._numTimesY; ++ry) {
			int x = 0;
			for (int rx = 0; rx < _transform._numTimesX; ++rx) {

				subRect.left = x;
				subRect.top = y;
				subRect.setWidth(w);
				subRect.setHeight(h);

				if (subRect.intersects(*clipRect)) {
					subRect.clip(*clipRect);
					subRect.translate(-x, -y);
					src.blit(*_targetSurface, basex + x + subRect.left, basey + y + subRect.top, _transform._flip, &subRect, _transform._rgbaMod, subRect.width(), subRect.height(), _transform._blendMode);

				}

				x += w;
			}
			y += h;
		}
	}

	if (doDelete) {
		delete clipRect;
	}
}