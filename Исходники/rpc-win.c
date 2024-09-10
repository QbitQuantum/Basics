/**
 * Called from VIDC code when the RISC OS mode has changed.
 * Update windows size to hold it.
 *
 * @param x X size in pixels
 * @param y Y size in pixels
 */
void updatewindowsize(uint32_t x, uint32_t y)
{
	RECT r;

	GetWindowRect(ghwnd, &r);
	MoveWindow(ghwnd, r.left, r.top,
	           x + (GetSystemMetrics(SM_CXFIXEDFRAME) * 2),
	           y + (GetSystemMetrics(SM_CYFIXEDFRAME) * 2) + GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYCAPTION),
	           TRUE);
        if (mousecapture)
        {
                RECT arcclip;

                ClipCursor(&oldclip);
                GetWindowRect(ghwnd,&arcclip);
                arcclip.left+=GetSystemMetrics(SM_CXFIXEDFRAME)+10;
                arcclip.right-=GetSystemMetrics(SM_CXFIXEDFRAME)+10;
                arcclip.top+=GetSystemMetrics(SM_CXFIXEDFRAME)+GetSystemMetrics(SM_CYMENUSIZE)+GetSystemMetrics(SM_CYCAPTION)+10;
                arcclip.bottom-=GetSystemMetrics(SM_CXFIXEDFRAME)+10;
                ClipCursor(&arcclip);
        }
}