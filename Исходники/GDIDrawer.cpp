void tTVPDrawer_GDIDoubleBuffering::NotifyBitmapCompleted(tjs_int x, tjs_int y, const void * bits, const BITMAPINFO * bitmapinfo,
	const tTVPRect &cliprect)
{
	// DrawDibDraw にて OffScreenDC に描画を行う
	if(DrawDibHandle && OffScreenDC)
	{
		ShouldShow = true;
		DrawDibDraw(DrawDibHandle,
			OffScreenDC,
			x,
			y,
			cliprect.get_width(),
			cliprect.get_height(),
			const_cast<BITMAPINFOHEADER*>(reinterpret_cast<const BITMAPINFOHEADER*>(bitmapinfo)),
			const_cast<void*>(bits),
			cliprect.left,
			cliprect.top,
			cliprect.get_width(),
			cliprect.get_height(),
			0);
	}
}