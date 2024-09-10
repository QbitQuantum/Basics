void Design::drawBitmap(Graphics::ManagedSurface *surface, Common::SeekableReadStream &in) {
	int numBytes = in.readSint16BE();
	int y1 = in.readSint16BE();
	int x1 = in.readSint16BE();
	int y2 = in.readSint16BE();
	int x2 = in.readSint16BE();
	int w = x2 - x1;
	int h = y2 - y1;
	Graphics::Surface tmp;

	tmp.create(w, h, Graphics::PixelFormat::createFormatCLUT8());

	numBytes -= 10;

	int x = 0, y = 0;
	while (numBytes > 0 && y < h) {
		int n = in.readSByte();
		int count;
		int b = 0;
		int state = 0;

		numBytes--;

		if ((n >= 0) && (n <= 127)) { // If n is between 0 and 127 inclusive, copy the next n+1 bytes literally.
			count = n + 1;
			state = 1;
		} else if ((n >= -127) && (n <= -1)) { // Else if n is between -127 and -1 inclusive, copy the next byte -n+1 times.
			b = in.readByte();
			numBytes--;
			count = -n + 1;
			state = 2;
		} else { // Else if n is -128, noop.
			count = 0;
		}

		for (int i = 0; i < count && y < h; i++) {
			byte color = 0;
			if (state == 1) {
				color = in.readByte();
				numBytes--;
			} else if (state == 2)
				color = b;

			for (int c = 0; c < 8; c++) {
				if (_boundsCalculationMode) {
					adjustBounds(x1 + x, y1 + y);
				} else if (x1 + x >= 0 && x1 + x < surface->w && y1 + y >= 0 && y1 + y < surface->h)
					*((byte *)tmp.getBasePtr(x, y)) = (color & (1 << (7 - c % 8))) ? kColorBlack : kColorWhite;
				x++;
				if (x == w) {
					y++;
					x = 0;
					break;
				}
			}
		}
	}

	in.skip(numBytes);

	if (!_boundsCalculationMode) {
		Graphics::FloodFill ff(&tmp, kColorWhite, kColorGreen);
		for (int yy = 0; yy < h; yy++) {
			ff.addSeed(0, yy);
			ff.addSeed(w - 1, yy);
		}
		for (int xx = 0; xx < w; xx++) {
			ff.addSeed(xx, 0);
			ff.addSeed(xx, h - 1);
		}
		ff.fill();

		for (y = 0; y < h && y1 + y < surface->h; y++) {
			byte *src = (byte *)tmp.getBasePtr(0, y);
			byte *dst = (byte *)surface->getBasePtr(x1, y1 + y);
			for (x = 0; x < w; x++) {
				if (*src != kColorGreen)
					*dst = *src;
				src++;
				dst++;
			}
		}
	}

	tmp.free();
}