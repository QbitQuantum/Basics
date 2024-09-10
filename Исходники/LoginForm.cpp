void LoginForm::setFrameRegion()
{
#ifdef WIN32
	wxRect wbr = getWindowsBorderRect();
	wxPoint br = wbr.GetBottomRight();

	br.x += 2;
	br.y += 2;

	wxRegion region = CreateRoundRectRgn(wbr.x, wbr.y, br.x, br.y, 5, 5);

	// Windows takes ownership of the region, so
	// we'll have to make a copy of the region to give to it.
	DWORD noBytes = ::GetRegionData(GetHrgnOf(region), 0, nullptr);
	RGNDATA *rgnData = (RGNDATA*) new char[noBytes];
	::GetRegionData(GetHrgnOf(region), noBytes, rgnData);
	HRGN hrgn = ::ExtCreateRegion(nullptr, noBytes, rgnData);
	delete[] (char*) rgnData;

	// Now call the shape API with the new region.
	::SetWindowRgn((HWND)GetHWND(), hrgn, FALSE);
#endif // LINUX TODO
}