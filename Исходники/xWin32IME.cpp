void xWnd32IMEInput::setCompositionWndPos(int hImc, int x, int y)
{
	COMPOSITIONFORM cf;
	cf.dwStyle = CFS_POINT;
	cf.ptCurrentPos.x = x;
	cf.ptCurrentPos.y = y;
	ImmSetCompositionWindow((HIMC)hImc, &cf);
}