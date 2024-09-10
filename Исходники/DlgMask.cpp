void __stdcall CDlgMask::draw_fun(PLAY_HANDLE handle, HDC hDc, LONG nUser)
{
	CDC* dc = CDC::FromHandle(hDc);
	CDlgMask* test= (CDlgMask*)nUser;	
	
	// draw user rect
	CPen pen_blue(0,1,RGB(0,0,255));
	dc->SelectObject(&pen_blue);
	
	dc->SelectStockObject(NULL_BRUSH);
	dc->Rectangle(&test->m_mask_rt);
}