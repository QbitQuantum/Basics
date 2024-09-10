void AtlZeroOrigin(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;

	// Quit if already zero origin
	if (rc.left==0 && rc.top==0)
		return;

	OffsetWindowOrgEx(di.hdcDraw, -rc.left, -rc.top, NULL);
	OffsetRect(&rc, -rc.left, -rc.top);
}