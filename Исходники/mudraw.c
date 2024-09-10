static void drawbmp(fz_context *ctx, fz_document *doc, fz_page *page, fz_display_list *list, int pagenum, fz_cookie *cookie)
{
	float zoom;
	fz_matrix ctm;
	fz_irect ibounds;
	fz_rect bounds, tbounds;

	int w, h;
	fz_device *dev;
	HDC dc, dc_main;
	RECT rc;
	HBRUSH bg_brush;
	HBITMAP hbmp;
	BITMAPINFO bmi = { 0 };
	int bmp_data_len;
	unsigned char *bmp_data;

	fz_bound_page(doc, page, &bounds);
	zoom = resolution / 72;
	fz_pre_scale(fz_rotate(&ctm, rotation), zoom, zoom);
	tbounds = bounds;
	fz_round_rect(&ibounds, fz_transform_rect(&tbounds, &ctm));

	w = width;
	h = height;
	if (res_specified)
	{
		fz_round_rect(&ibounds, &tbounds);
		if (w && ibounds.x1 - ibounds.x0 <= w)
			w = 0;
		if (h && ibounds.y1 - ibounds.y0 <= h)
			h = 0;
	}
	if (w || h)
	{
		float scalex = w / (tbounds.x1 - tbounds.x0);
		float scaley = h / (tbounds.y1 - tbounds.y0);
		fz_matrix scale_mat;
		if (w == 0)
			scalex = fit ? 1.0f : scaley;
		if (h == 0)
			scaley = fit ? 1.0f : scalex;
		if (!fit)
			scalex = scaley = min(scalex, scaley);
		fz_concat(&ctm, &ctm, fz_scale(&scale_mat, scalex, scaley));
		tbounds = bounds;
		fz_transform_rect(&tbounds, &ctm);
	}
	fz_round_rect(&ibounds, &tbounds);
	fz_rect_from_irect(&tbounds, &ibounds);

	w = ibounds.x1 - ibounds.x0;
	h = ibounds.y1 - ibounds.y0;

	dc_main = GetDC(NULL);
	dc = CreateCompatibleDC(dc_main);
	hbmp = CreateCompatibleBitmap(dc_main, w, h);
	DeleteObject(SelectObject(dc, hbmp));

	SetRect(&rc, 0, 0, w, h);
	bg_brush = CreateSolidBrush(RGB(0xFF,0xFF,0xFF));
	FillRect(dc, &rc, bg_brush);
	DeleteObject(bg_brush);

	dev = fz_new_gdiplus_device(ctx, dc, &tbounds);
	if (list)
		fz_run_display_list(list, dev, &ctm, &tbounds, cookie);
	else
		fz_run_page(doc, page, dev, &ctm, cookie);
	fz_free_device(dev);

	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = output_format == OUT_TGA ? -h : h;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = output_format == OUT_TGA ? 32 : 24;
	bmi.bmiHeader.biCompression = BI_RGB;

	bmp_data_len = output_format == OUT_TGA ? w * h * 4 : ((w * 3 + 3) / 4) * 4 * h;
	bmp_data = fz_malloc(ctx, bmp_data_len);
	if (!GetDIBits(dc, hbmp, 0, h, bmp_data, &bmi, DIB_RGB_COLORS))
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot draw page %d in PDF file '%s'", pagenum, filename);

	DeleteDC(dc);
	ReleaseDC(NULL, dc_main);
	DeleteObject(hbmp);

	if (output)
	{
		char buf[512];
		FILE *f;

		sprintf(buf, output, pagenum);
		f = fopen(buf, "wb");
		if (!f)
			fz_throw(ctx, FZ_ERROR_GENERIC, "could not create raster file '%s'", buf);

		if (output_format == OUT_TGA)
		{
			fz_pixmap *pix = fz_new_pixmap_with_data(ctx, fz_device_bgr(ctx), w, h, bmp_data);
			fz_write_tga(ctx, pix, buf, 0);
			fz_drop_pixmap(ctx, pix);
		}
		else
		{
			BITMAPFILEHEADER bmpfh = { 0 };
			static const int one = 1;
			if (!*(char *)&one)
				fz_throw(ctx, FZ_ERROR_GENERIC, "rendering to BMP is not supported on big-endian architectures");

			bmpfh.bfType = MAKEWORD('B', 'M');
			bmpfh.bfOffBits = sizeof(bmpfh) + sizeof(bmi);
			bmpfh.bfSize = bmpfh.bfOffBits + bmp_data_len;

			fwrite(&bmpfh, sizeof(bmpfh), 1, f);
			fwrite(&bmi, sizeof(bmi), 1, f);
			fwrite(bmp_data, 1, bmp_data_len, f);
		}

		fclose(f);
	}

	if (showmd5)
	{
		fz_pixmap *pix = fz_new_pixmap_with_data(ctx, fz_device_bgr(ctx), bmp_data_len / 4 / h, h, bmp_data);
		unsigned char digest[16];
		int i;

		fz_md5_pixmap(pix, digest);
		printf(" ");
		for (i = 0; i < 16; i++)
			printf("%02x", digest[i]);

		fz_drop_pixmap(ctx, pix);
	}

	fz_free(ctx, bmp_data);
}