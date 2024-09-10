void MacWindow::drawBorder() {
	_borderIsDirty = false;

	bool active = _active, scrollable = _scrollable, closeable = _active, drawTitle = !_title.empty();
	const int size = kBorderWidth;
	int x = 0;
	int y = 0;
	int width = _borderSurface.w;
	int height = _borderSurface.h;
	Graphics::ManagedSurface *g = &_borderSurface;

	// We draw rect with outer kColorGreen2 and inner kColorGreen, so on 2 passes we cut out
	// scene by external shape of the border
	int sz = kBorderWidth / 2;
	g->clear(kColorGreen2);
	g->fillRect(Common::Rect(sz, sz, width - sz, height - sz), kColorGreen);

	drawBox(g, x,                    y,                     size,                 size);
	drawBox(g, x + width - size - 1, y,                     size,                 size);
	drawBox(g, x + width - size - 1, y + height - size - 1, size,                 size);
	drawBox(g, x,                    y + height - size - 1, size,                 size);
	drawBox(g, x + size,             y + 2,                 width - 2 * size - 1, size - 4);
	drawBox(g, x + size,             y + height - size + 1, width - 2 * size - 1, size - 4);
	drawBox(g, x + 2,                y + size,              size - 4,             height - 2 * size - 1);
	drawBox(g, x + width - size + 1, y + size,              size - 4,             height - 2 * size - 1);

	if (active) {
		fillRect(g, x + size, y + 5,           width - 2 * size - 1, 8, kColorBlack);
		fillRect(g, x + size, y + height - 13, width - 2 * size - 1, 8, kColorBlack);
		fillRect(g, x + 5,    y + size,        8,                    height - 2 * size - 1, kColorBlack);
		if (!scrollable) {
			fillRect(g, x + width - 13, y + size, 8, height - 2 * size - 1, kColorBlack);
		} else {
			int x1 = x + width - 15;
			int y1 = y + size + 1;

			for (int yy = 0; yy < ARROW_H; yy++) {
				for (int xx = 0; xx < ARROW_W; xx++)
					g->hLine(x1 + xx, y1 + yy, x1 + xx, (arrowPixels[yy][xx] != 0 ? kColorBlack : kColorWhite));
			}

			fillRect(g, x + width - 13, y + size + ARROW_H, 8, height - 2 * size - 1 - ARROW_H * 2, kColorBlack);

			y1 += height - 2 * size - ARROW_H - 2;
			for (int yy = 0; yy < ARROW_H; yy++) {
				for (int xx = 0; xx < ARROW_W; xx++)
					g->hLine(x1 + xx, y1 + yy, x1 + xx, (arrowPixels[ARROW_H - yy - 1][xx] != 0 ? kColorBlack : kColorWhite));
			}

			if (_highlightedPart == kBorderScrollUp || _highlightedPart == kBorderScrollDown) {
				int rx1 = x + width - kBorderWidth + 2;
				int ry1 = y + size + _dims.height() * _scrollPos;
				int rx2 = rx1 + size - 4;
				int ry2 = ry1 + _dims.height() * _scrollSize;
				Common::Rect rr(rx1, ry1, rx2, ry2);

				Graphics::drawFilledRect(rr, kColorBlack, drawPixelInverted, g);
			}
		}
		if (closeable) {
			if (_highlightedPart == kBorderCloseButton) {
				fillRect(g, x + 6, y + 6, 6, 6, kColorBlack);
			} else {
				drawBox(g, x + 5, y + 5, 7, 7);
			}
		}
	}

	if (drawTitle) {
		const Graphics::Font *font = getTitleFont();
		int yOff = _wm->hasBuiltInFonts() ? 3 : 1;

		int w = font->getStringWidth(_title) + 10;
		int maxWidth = width - size * 2 - 7;
		if (w > maxWidth)
			w = maxWidth;
		drawBox(g, x + (width - w) / 2, y, w, size);
		font->drawString(g, _title, x + (width - w) / 2 + 5, y + yOff, w, kColorBlack);
	}
}