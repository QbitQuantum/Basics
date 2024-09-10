void GifAvatar::draw(MyBitmap *bmp, int x, int y, int w, int h, POPUPOPTIONS *options)
{
	if (!av || (w <= 0) || (h <= 0)) return;

	if (!frameCount || !frameDelays || !hBitmap || (cachedWidth != w) || (cachedHeight != h))
	{
		cachedWidth = w;
		cachedHeight = h;
		if (frameDelays) {
			mir_free(frameDelays);
			frameDelays = NULL;
		}
		if (hBitmap) DeleteObject(hBitmap);
		GDIPlus_ExtractAnimatedGIF(av->szFilename, w, h, &hBitmap, &frameDelays, &frameCount, &frameSize);
	}

	if (!frameCount) return;

	HRGN rgn;
	if (options->avatarRadius)
	{
		rgn = CreateRoundRectRgn(x, y, x+w, y+h, 2 * options->avatarRadius, 2 * options->avatarRadius);
		SelectClipRgn(bmp->getDC(), rgn);
	} else
	{
		rgn = CreateRectRgn(x, y, x+w, y+h);
	}

	HDC hdcTmp = CreateCompatibleDC(bmp->getDC());
	SelectObject(hdcTmp, hBitmap);
	SetStretchBltMode(bmp->getDC(), HALFTONE);


	if (av->dwFlags & AVS_PREMULTIPLIED)
	{
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;
		AlphaBlend(bmp->getDC(), x, y, w, h, hdcTmp, frameSize.cx*activeFrame, 0, frameSize.cx, frameSize.cy, bf);

		if (options->avatarBorders && options->avatarPNGBorders)
		{
			HBRUSH hbr = CreateSolidBrush(fonts.clAvatarBorder);
			bmp->saveAlpha(x, y, w, h);
			FrameRgn(bmp->getDC(), rgn, hbr, 1, 1); 
			DeleteObject(hbr);
			bmp->restoreAlpha(x, y, w, h);
		}
	}
	else {
		bmp->saveAlpha(x, y, w, h);
		StretchBlt(bmp->getDC(), x, y, w, h, hdcTmp, frameSize.cx*activeFrame, 0, frameSize.cx, frameSize.cy, SRCCOPY);
		if (options->avatarBorders) {
			HBRUSH hbr = CreateSolidBrush(fonts.clAvatarBorder);
			FrameRgn(bmp->getDC(), rgn, hbr, 1, 1); 
			DeleteObject(hbr);
		}
		bmp->restoreAlpha(x, y, w, h);
	}
	DeleteObject(rgn);
	SelectClipRgn(bmp->getDC(), NULL);
	DeleteDC(hdcTmp);

	activeFrame = (activeFrame + 1) % frameCount;
}