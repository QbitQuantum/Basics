static void rtgui_dc_buffer_fill_rect(struct rtgui_dc *self, struct rtgui_rect *dst_rect)
{
    struct rtgui_dc_buffer *dst;
	unsigned r, g, b, a;
	rtgui_rect_t _r, *rect;
	
    dst = (struct rtgui_dc_buffer *)self;

	_r = *dst_rect;
	/* parameter checking */
    if (_r.x1 > dst->width)  _r.x1 = dst->width;
    if (_r.x2 > dst->width)  _r.x2 = dst->width;
    if (_r.y1 > dst->height) _r.y1 = dst->height;
    if (_r.y2 > dst->height) _r.y2 = dst->height;
	rect = &_r;

	r = RTGUI_RGB_R(dst->gc.foreground);
	g = RTGUI_RGB_G(dst->gc.foreground);
	b = RTGUI_RGB_B(dst->gc.foreground);
	a = RTGUI_RGB_A(dst->gc.foreground);

	switch (dst->pixel_format)
	{
		case RTGRAPHIC_PIXEL_FORMAT_RGB565:
			FILLRECT(rt_uint16_t, DRAW_SETPIXEL_RGB565);
			break;
		case RTGRAPHIC_PIXEL_FORMAT_BGR565:
			FILLRECT(rt_uint16_t, DRAW_SETPIXEL_BGR565);
			break;
		case RTGRAPHIC_PIXEL_FORMAT_RGB888:
			FILLRECT(rt_uint16_t, DRAW_SETPIXEL_RGB888);
			break;
		case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
			FILLRECT(rt_uint16_t, DRAW_SETPIXEL_ARGB8888);
			break;
	}
}