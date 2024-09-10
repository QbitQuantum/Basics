DLLEXP bool load(WCHAR *fn)
{
	CImage ci;
	HRESULT hr=ci.Load(fn);
	if (!SUCCEEDED(hr))
	{
		return false;
	}
	g_snap_height=ci.GetHeight();
	g_snap_width=ci.GetWidth();
	BitBlt(g_memdc.m_hDC,0,0,g_snap_width,g_snap_height,ci.GetDC(),0,0,SRCCOPY);
	g_bitmap.GetBitmapBits(g_scn_height*g_scn_width*4,g_buf_clr);
	return true;
}