static void paint_cb(HWND window, PAINTSTRUCT* ps, HDC dc)
{
	int textwidth, textheight;
	glyphcache_getfontsize(&textwidth, &textheight);

	int x1 = ps->rcPaint.left / textwidth;
	x1 -= 1; /* because of overlapping characters */
	if (x1 < 0)
		x1 = 0;

	int y1 = ps->rcPaint.top/textheight;
	int x2 = ps->rcPaint.right/textwidth;
	x2 += 1; /* because of overlapping characters */
	if (x2 >= screenwidth)
	{
		RECT r = {screenwidth*textwidth, 0, ps->rcPaint.right, ps->rcPaint.bottom};
		FillRect(dc, &r, GetStockObject(BLACK_BRUSH));
		x2 = screenwidth;
	}

	int y2 = ps->rcPaint.bottom / textheight;
	if (y2 >= screenheight)
	{
		RECT r = {0, screenheight*textheight, ps->rcPaint.right, ps->rcPaint.bottom};
		FillRect(dc, &r, GetStockObject(BLACK_BRUSH));
		y2 = screenheight-1;
	}

	int state = SaveDC(dc);

	HPEN brightpen = CreatePen(PS_SOLID, 0, 0xffffff);
	HPEN normalpen = CreatePen(PS_SOLID, 0, 0x888888);
	HPEN dimpen = CreatePen(PS_SOLID, 0, 0x555555);

	for (int y = y1; y <= y2; y++)
	{
		int sy = y * textheight;

		/* Clear this line (or at least the part of it we're drawing). */

		RECT r = {ps->rcPaint.left, sy, ps->rcPaint.right, sy+textheight};
		FillRect(dc, &r, GetStockObject(BLACK_BRUSH));

		/* Draw the actual text. */

		for (int x = x1; x < x2; x++)
		{
			int seq = y*screenwidth + x;
			int sx = x * textwidth;

			unsigned int id = frontbuffer[seq];
			struct glyph* glyph = glyphcache_getglyph(id, dc);
			if (glyph)
			{
				BitBlt(dc, sx+glyph->xoffset, sy+glyph->yoffset,
					glyph->realwidth, glyph->realheight,
					glyph->dc, 0, 0, SRCPAINT);

				if (id & DPY_UNDERLINE)
				{
					if (id & DPY_BRIGHT)
						SelectObject(dc, brightpen);
					else if (id & DPY_DIM)
						SelectObject(dc, dimpen);
					else
						SelectObject(dc, normalpen);

					MoveToEx(dc, sx, sy+textheight-1, NULL);
					LineTo(dc, sx+glyph->width, sy+textheight-1);
				}
			}
		}

		/* Now go through and invert any characters which are in reverse. */

		for (int x = x1; x < x2; x++)
		{
			int seq = y*screenwidth + x;
			int sx = x * textwidth;

			unsigned int id = frontbuffer[seq];
			if (id & DPY_REVERSE)
			{
				int w;
				struct glyph* glyph = glyphcache_getglyph(id, dc);
				if (glyph)
					w = glyph->width;
				else
					w = textwidth;

				BitBlt(dc, sx, sy, w, textheight, NULL, 0, 0, DSTINVERT);
			}
		}
	}

	/* Draw the cursor caret. */

	{
		int x = cursorx*textwidth;
		int y = cursory*textheight;

		SelectObject(dc, brightpen);
		MoveToEx(dc, x, y, NULL);
		LineTo(dc, x, y+textheight);
		SetPixelV(dc, x-1, y-1, 0xffffff);
		SetPixelV(dc, x+1, y-1, 0xffffff);
		SetPixelV(dc, x-1, y+textheight, 0xffffff);
		SetPixelV(dc, x+1, y+textheight, 0xffffff);
	}


	DeleteObject(brightpen);
	DeleteObject(normalpen);
	DeleteObject(dimpen);
	RestoreDC(dc, state);
}