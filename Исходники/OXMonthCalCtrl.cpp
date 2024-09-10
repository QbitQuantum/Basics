int COXMonthCalCtrl::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(GetSafeHwnd()));

	// the control should be designated to provide tooltips
	if((GetMonthCalStyle()&OXMCS_INFOTIP)==0)
		return -1;

	pTI->hwnd=GetSafeHwnd();

	GetClientRect(&pTI->rect);

	MCHITTESTINFO mcHitTest;
	::ZeroMemory((void*)&mcHitTest,sizeof(mcHitTest));
	mcHitTest.cbSize=sizeof(mcHitTest);
	mcHitTest.pt=point;
///	HitTest(&mcHitTest);
	::SendMessage(GetSafeHwnd(),MCM_HITTEST,0,(LPARAM)&mcHitTest);

	pTI->uId=mcHitTest.uHit;

	pTI->uFlags&=~(TTF_IDISHWND);

	// set text to LPSTR_TEXTCALLBACK in order to get TTN_NEEDTEXT message when 
	// it's time to display tool tip
	pTI->lpszText=LPSTR_TEXTCALLBACK;

	return PtrToInt(pTI->uId);
}