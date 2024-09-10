//////////////////
// Create window DC, including non-client area.
// 
WPNCWinDC::WPNCWinDC(WPWin *w)
{
	assert(w);
	win = w;
	hdc = GetWindowDC((*win)());
	assert(hdc);
}