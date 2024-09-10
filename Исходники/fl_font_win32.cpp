void Fl_Device::rtl_draw(const char *str, int n, float x, float y)
{
	// USE BUFFER HERE ALSO
	SetTextColor(fl_gc, fl_colorref);
	SelectObject(fl_gc, current_font);

	int i = 0;
	int lx = 0;
	const WCHAR *skod;
	resize_buffer(n);
	int wn = fl_utf2unicode((const unsigned char *)str, n, wstr);

	while (i < wn) {
	    lx = int(fl_width(wstr[i]));
		x -= lx;
		skod = (const WCHAR*)wstr + i;
#ifndef _WIN32_WCE
		TextOutW(fl_gc, int(floor(x+.5f)), int(floor(y+.5f)), skod, 1);
#else
		RECT rect = {int(floor(x+.5f)),int(floor(y+.5f)), 0,0};
		DrawText(fl_gc, skod, 1, &rect, DT_SINGLELINE | DT_TOP | DT_LEFT | DT_NOCLIP);	
#endif
		if (fl_nonspacing(wstr[i])) {
			x += lx;
		}
		i++;
	}	
}