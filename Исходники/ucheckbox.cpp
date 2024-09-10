BOOL uCheckBox::Create(LPCTSTR Caption, DWORD dwStyle, int x, int y, int w, int h, CWnd* pParentWnd, UINT nID)
{
	ASSERT(pParentWnd);
	pParentWindow = pParentWnd;
	mID = nID;

	Style = dwStyle & UCS_CONTROL_MASK;
	State = UC_STATE_DEFAULT;
	// CaptionColor = uCore->GetColor((Style & ULS_BOX) ? _UC_BLACK : _UC_WHITE);
	// ShadowColor = uCore->GetColor(_UC_DARK);
	LampColor = uCore->GetColor(_UC_HOVER);

	// Render
	SETRECT(Size, 0, 0, w, h);

	// Render Lamp
	SetLampColor(LampColor);
	
	BOOL ret = CWnd::Create(KXU_CHECKBOX_CLASSNAME, Caption, dwStyle & UCS_WINDOW_MASK,
							CRect(x, y, x + w, y + h),
							pParentWnd, nID);
	return ret;
}