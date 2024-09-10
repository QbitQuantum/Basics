void CImgButton::InvalidateParent()
{
	CRect rect;
	GetWindowRect(rect);
	CWnd* pParent = GetParent();
	if(::IsWindow(pParent->GetSafeHwnd()))
	{
		pParent->ScreenToClient(rect);
		pParent->InvalidateRect(rect, FALSE);
	}
}