void clipper_t::fill()
{
	HWND h = WindowFromDC(hdc);
	window_rect_t r(h);
	
	temp_object_t reg(
		CreateRectRgn(r.l, r.t, r.r, r.b));
	
	SelectClipRgn(hdc, (HRGN)reg.handle);
}