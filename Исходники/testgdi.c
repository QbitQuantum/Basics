static void
win_draw(win_t *win)
{
	GpGraphics *gp;
	GpStatus st;
	GpImage *img;
	gunichar2 *unis;

	XClearWindow(win->dpy, win->win);

	GdipCreateFromXDrawable_linux (win->win, win->dpy, &gp);
        {	
		GpPen *pen;
		GpSolidFill *brush;
		int a = 255;
		int r = 255;
		int g = 0;
		int b = 0;
		
		GdipCreatePen1 (a << 24 | r << 16 | g << 8 | b,
				10, UnitPixel, &pen);
		
		GdipDrawRectangle (gp, pen, 10, 10, 60, 60);
		GdipDrawLine (gp, pen, 0, 0, 100, 100);
		
		GdipCreateSolidFill (a << 24 | r << 16 | g << 8 | b, &brush);
		
		printf ("%d\n",GdipFillEllipse (gp, (GpBrush*)brush, 40, 40, 50, 75));
//		return;
	}

	
	
	
	unis = g_utf8_to_utf16 ("test.jpg", -1, NULL, NULL, NULL);
	st = GdipLoadImageFromFile (unis, &img);
	CHECK_GDIP_ST(st);
	st = GdipDrawImage (gp, img, 0, 0);
	CHECK_GDIP_ST(st);
	g_free (unis);
	GdipDisposeImage (img);
	img = NULL;

	printf("jpg drawn \n");

	unis = g_utf8_to_utf16 ("test.tif", -1, NULL, NULL, NULL);
	st = GdipLoadImageFromFile (unis, &img);
	CHECK_GDIP_ST(st);
	st = GdipDrawImage (gp, img, 100, 0);
	CHECK_GDIP_ST(st);
	g_free (unis);
	GdipDisposeImage (img);
	img = NULL;

	printf("tif drawn \n");

	unis = g_utf8_to_utf16 ("test.gif", -1, NULL, NULL, NULL);
	st = GdipLoadImageFromFile (unis, &img);
	CHECK_GDIP_ST(st);
	st = GdipDrawImage (gp, img, 200, 0);
	CHECK_GDIP_ST(st);
	g_free (unis);
	GdipDisposeImage (img);
	img = NULL;

	printf("gif drawn \n");

	unis = g_utf8_to_utf16 ("test.png", -1, NULL, NULL, NULL);
	st = GdipLoadImageFromFile (unis, &img);
	CHECK_GDIP_ST(st);
	st = GdipDrawImage (gp, img, 0, 100);
	CHECK_GDIP_ST(st);
	g_free (unis);
	GdipDisposeImage (img);
	img = NULL;

	printf("png drawn \n");

	unis = g_utf8_to_utf16 ("test.bmp", -1, NULL, NULL, NULL);
	st = GdipLoadImageFromFile (unis, &img);
	CHECK_GDIP_ST(st);
	st = GdipDrawImage (gp, img, 200, 100);
	CHECK_GDIP_ST(st);
	g_free (unis);
	GdipDisposeImage (img);
	img = NULL;

	printf("bmp drawn \n");

}