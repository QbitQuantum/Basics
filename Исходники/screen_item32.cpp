Common::Rect ScreenItem::getNowSeenRect(const Plane &plane) const {
	CelObj &celObj = getCelObj();

	Common::Rect celObjRect(celObj._width, celObj._height);
	Common::Rect nsRect;

	if (_useInsetRect) {
		if (_insetRect.intersects(celObjRect)) {
			nsRect = _insetRect;
			nsRect.clip(celObjRect);
		} else {
			nsRect = Common::Rect();
		}
	} else {
		nsRect = celObjRect;
	}

	const uint16 scriptWidth = g_sci->_gfxFrameout->getCurrentBuffer().scriptWidth;
	const uint16 scriptHeight = g_sci->_gfxFrameout->getCurrentBuffer().scriptHeight;

	Ratio scaleX, scaleY;
	if (_scale.signal & kScaleSignalDoScaling32) {
		if (_scale.signal & kScaleSignalUseVanishingPoint) {
			int num = _scale.max * (_position.y - plane._vanishingPoint.y) / (scriptWidth - plane._vanishingPoint.y);
			scaleX = Ratio(num, 128);
			scaleY = Ratio(num, 128);
		} else {
			scaleX = Ratio(_scale.x, 128);
			scaleY = Ratio(_scale.y, 128);
		}
	}

	if (scaleX.getNumerator() == 0 || scaleY.getNumerator() == 0) {
		return Common::Rect();
	}

	int16 displaceX = celObj._displace.x;
	int16 displaceY = celObj._displace.y;

	if (_mirrorX != celObj._mirrorX && _celInfo.type != kCelTypePic) {
		displaceX = celObj._width - displaceX - 1;
	}

	if (celObj._scaledWidth != kLowResX || celObj._scaledHeight != kLowResY) {
		// high resolution coordinates

		if (_useInsetRect) {
			Ratio scriptToCelX(celObj._scaledWidth, scriptWidth);
			Ratio scriptToCelY(celObj._scaledHeight, scriptHeight);
			mulru(nsRect, scriptToCelX, scriptToCelY, 0);

			if (nsRect.intersects(celObjRect)) {
				nsRect.clip(celObjRect);
			} else {
				nsRect = Common::Rect();
			}
		}

		if (!scaleX.isOne() || !scaleY.isOne()) {
			// Different games use a different cel scaling mode, but the
			// difference isn't consistent across SCI versions; instead,
			// it seems to be related to an update that happened during
			// SCI2.1mid where games started using hi-resolution game
			// scripts
			if (scriptWidth == kLowResX) {
				mulinc(nsRect, scaleX, scaleY);
				// TODO: This was in the original code, baked into the
				// multiplication though it is not immediately clear
				// why this is the only one that reduces the BR corner
				nsRect.right -= 1;
				nsRect.bottom -= 1;
			} else {
				nsRect.left = (nsRect.left * scaleX).toInt();
				nsRect.top = (nsRect.top * scaleY).toInt();

				if (scaleX.getNumerator() > scaleX.getDenominator()) {
					nsRect.right = (nsRect.right * scaleX).toInt();
				} else {
					nsRect.right = ((nsRect.right - 1) * scaleX).toInt() + 1;
				}

				if (scaleY.getNumerator() > scaleY.getDenominator()) {
					nsRect.bottom = (nsRect.bottom * scaleY).toInt();
				} else {
					nsRect.bottom = ((nsRect.bottom - 1) * scaleY).toInt() + 1;
				}
			}
		}

		Ratio celToScriptX(scriptWidth, celObj._scaledWidth);
		Ratio celToScriptY(scriptHeight, celObj._scaledHeight);

		displaceX = (displaceX * scaleX * celToScriptX).toInt();
		displaceY = (displaceY * scaleY * celToScriptY).toInt();

		mulinc(nsRect, celToScriptX, celToScriptY);
		nsRect.translate(_position.x - displaceX, _position.y - displaceY);
	} else {
		// low resolution coordinates

		if (!scaleX.isOne() || !scaleY.isOne()) {
			mulinc(nsRect, scaleX, scaleY);
			// TODO: This was in the original code, baked into the
			// multiplication though it is not immediately clear
			// why this is the only one that reduces the BR corner
			nsRect.right -= 1;
			nsRect.bottom -= 1;
		}

		displaceX = (displaceX * scaleX).toInt();
		displaceY = (displaceY * scaleY).toInt();
		nsRect.translate(_position.x - displaceX, _position.y - displaceY);

		if (_mirrorX != celObj._mirrorX && _celInfo.type != kCelTypePic) {
			nsRect.translate(plane._gameRect.width() - nsRect.width(), 0);
		}
	}

	return nsRect;
}