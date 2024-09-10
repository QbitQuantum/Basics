void LoadClcOptions(HWND hwnd, struct ClcData *dat, BOOL bFirst)
{
	HDC hdc = GetDC(hwnd);
	for (int i = 0; i <= FONTID_MAX; i++) {
		if (!dat->fontInfo[i].changed)
			DeleteObject(dat->fontInfo[i].hFont);

		LOGFONT lf;
		pcli->pfnGetFontSetting(i, &lf, &dat->fontInfo[i].colour);
		lf.lfHeight = -MulDiv(lf.lfHeight, GetDeviceCaps(hdc, LOGPIXELSY), 72);

		dat->fontInfo[i].hFont = CreateFontIndirect(&lf);
		dat->fontInfo[i].changed = 0;

		HFONT holdfont = (HFONT)SelectObject(hdc, dat->fontInfo[i].hFont);
		SIZE fontSize;
		GetTextExtentPoint32(hdc, _T("x"), 1, &fontSize);
		SelectObject(hdc, holdfont);

		dat->fontInfo[i].fontHeight = fontSize.cy;
	}
	ReleaseDC(hwnd, hdc);

	dat->min_row_heigh = (int)cfg::getByte("CLC", "RowHeight", CLCDEFAULT_ROWHEIGHT);
	dat->group_row_height = (int)cfg::getByte("CLC", "GRowHeight", CLCDEFAULT_ROWHEIGHT);
	dat->row_border = 0;
	dat->rightMargin = cfg::getByte("CLC", "RightMargin", CLCDEFAULT_LEFTMARGIN);
	dat->bkColour = cfg::getByte("CLC", "UseWinColours", CLCDEFAULT_USEWINDOWSCOLOURS) ?
		GetSysColor(COLOR_3DFACE) : cfg::getDword("CLC", "BkColour", CLCDEFAULT_BKCOLOUR);

	coreCli.pfnLoadClcOptions(hwnd, dat, bFirst);

	if (!dat->bkChanged) {
		if (cfg::dat.hBrushCLCBk)
			DeleteObject(cfg::dat.hBrushCLCBk);
		cfg::dat.hBrushCLCBk = CreateSolidBrush(dat->bkColour);
		if (dat->hBmpBackground) {
			if (cfg::dat.hdcPic) {
				SelectObject(cfg::dat.hdcPic, cfg::dat.hbmPicOld);
				DeleteDC(cfg::dat.hdcPic);
				cfg::dat.hdcPic = 0;
				cfg::dat.hbmPicOld = 0;
			}
		}

		cfg::dat.bmpBackground = dat->hBmpBackground;
		if (cfg::dat.bmpBackground) {
			HDC hdcThis = GetDC(pcli->hwndContactList);
			GetObject(cfg::dat.bmpBackground, sizeof(cfg::dat.bminfoBg), &(cfg::dat.bminfoBg));
			cfg::dat.hdcPic = CreateCompatibleDC(hdcThis);
			cfg::dat.hbmPicOld = reinterpret_cast<HBITMAP>(SelectObject(cfg::dat.hdcPic, cfg::dat.bmpBackground));
			ReleaseDC(pcli->hwndContactList, hdcThis);
		}
	}

	if (cfg::getByte("CLCExt", "EXBK_FillWallpaper", 0)) {
		char wpbuf[MAX_PATH];
		if (dat->hBmpBackground) {
			DeleteObject(dat->hBmpBackground);
			dat->hBmpBackground = NULL;
		}

		SystemParametersInfoA(SPI_GETDESKWALLPAPER, MAX_PATH, wpbuf, 0);

		// we have a wallpaper string
		if (wpbuf[0] != 0)
			dat->hBmpBackground = reinterpret_cast<HBITMAP>(LoadImageA(NULL, wpbuf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

		cfg::dat.bmpBackground = dat->hBmpBackground;
		if (cfg::dat.bmpBackground) {
			HDC hdcThis = GetDC(pcli->hwndContactList);
			GetObject(cfg::dat.bmpBackground, sizeof(cfg::dat.bminfoBg), &(cfg::dat.bminfoBg));
			cfg::dat.hdcPic = CreateCompatibleDC(hdcThis);
			cfg::dat.hbmPicOld = reinterpret_cast<HBITMAP>(SelectObject(cfg::dat.hdcPic, cfg::dat.bmpBackground));
			ReleaseDC(pcli->hwndContactList, hdcThis);
		}
	}
}