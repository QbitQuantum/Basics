void TaskbarWnd::cacheIconicRepresentation()
{
	if ( hbm_cached_ && !::IsZoomed(doc) ) {
		return;
	}

	RECT r;
	::GetWindowRect( mol::win::mdiClient(), &r );

	RECT cr;
	::GetClientRect(  doc, &cr );
	POINT p = {cr.right,cr.bottom};
	::ClientToScreen( doc, &p );

	if ( p.y > r.bottom ) 
	{
		p.y = r.bottom;
	}
	if ( p.x > r.right ) 
	{
		p.x = r.right;
	}

	::ScreenToClient( doc, &p );

	// snap
	Gdiplus::Bitmap src(p.x, p.y, PixelFormat32bppPARGB );
	{
		Gdiplus::Graphics gsnap( &src );
		gsnap.Clear( 0x00ffffff );

		HDC mem = gsnap.GetHDC();
		BOOL bret = PrintWindow2( doc, mem, 1 );
		gsnap.Flush();
		gsnap.ReleaseHDC(mem);
	}

	if ( hbm_cached_ ) 
	{
		::DeleteObject( (HGDIOBJ)hbm_cached_);
	}
	src.GetHBITMAP(Gdiplus::Color::Black, &hbm_cached_);

	enableTabs(true);
	DwmInvalidateIconicBitmaps(*this);

}