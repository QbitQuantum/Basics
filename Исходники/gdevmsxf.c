/* Render a character. */
int
win_render_char(gx_xfont * xf, gx_xglyph xg, gx_device * dev,
		int xo, int yo, gx_color_index color, int required)
{
    char chr = (char)xg;
    int code;

#ifdef NOTUSED			/* we don't own any windows so we can no longer do this */
    if (dev->dname == gs_mswin_device.dname &&
	wdev->hdctext != NULL && !wxf->invert_y
	) {			/* Display the character directly */
	HDC hdc = wdev->hdctext;
	PALETTEENTRY *pal = &wdev->limgpalette->palPalEntry[color];

	if ((code = win_select_font(hdc, wxf)) < 0)
	    return code;
	SetTextColor(hdc, RGB(pal->peRed, pal->peGreen, pal->peBlue));
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, xo, yo - wxf->y_offset, &chr, 1);
    } else
#endif
    if (!required)
	code = -1;		/* too hard */
    else {			/* Display on an intermediate bitmap, then copy the bits. */
	gs_point wxy;
	gs_int_rect bbox;
	int w, h, wbm, raster;
	gx_device_win *fdev = wxf->dev;
	HBITMAP hbm;
	byte *bits;

	code = (*xf->common.procs->char_metrics) (xf, xg, 0,
						  &wxy, &bbox);
	if (code < 0)
	    return code;
	w = bbox.q.x - bbox.p.x;
	h = bbox.q.y - bbox.p.y;
	wbm = ROUND_UP(w, align_bitmap_mod * 8);
	raster = wbm >> 3;
	bits = gs_malloc(dev->memory, h, raster, "win_render_char");
	if (bits == 0)
	    return gs_error_limitcheck;
	hbm = CreateBitmap(wbm, h, 1, 1, NULL);
	if (hbm == NULL) {
	    code = gs_error_limitcheck;
	} else {
	    HDC hdcwin = win_get_dc(fdev);
	    HDC hdcbit = CreateCompatibleDC(hdcwin);

	    dev_proc_copy_mono((*copy_mono)) =
		dev_proc(dev, copy_mono);
	    int y = yo - wxf->y_offset;

	    SetMapMode(hdcbit, GetMapMode(hdcwin));
	    win_select_font(hdcbit, wxf);
	    SelectObject(hdcbit, hbm);
	    PatBlt(hdcbit, 0, 0, wbm, h, rop_write_0s);
	    SetTextColor(hdcbit, 0xffffffL);	/* 1 */
	    SetBkMode(hdcbit, TRANSPARENT);
	    TextOut(hdcbit, 0, 0, &chr, 1);
	    GetBitmapBits(hbm, (DWORD) raster * h, bits);
	    DeleteDC(hdcbit);
	    win_release_dc(fdev, hdcwin);
	    DeleteObject(hbm);
	    if (!wxf->invert_y)
		code = (*copy_mono) (dev, bits, 0,
				     raster, gx_no_bitmap_id,
				     xo, y, w, h,
				     gx_no_color_index, color);
	    else {		/* Copy scan lines in reverse order. */
		int i;

		y += h - 1;
		for (i = 0; i < h; i++)
		    (*copy_mono) (dev, bits + i * raster,
				  0, raster, gx_no_bitmap_id,
				  xo, y - i, w, 1,
				  gx_no_color_index, color);
	    }
	}
	gs_free(dev->memory, bits, h, raster, "win_render_char");
    }
    return (code < 0 ? code : 0);
}