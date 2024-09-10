//////////////////
// Create folder tab control from static control.
// Destroys the static control. This is convenient for dialogs
//
BOOL CFolderTabCtrl::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CStatic wndStatic;
	if (!wndStatic.SubclassDlgItem(nID, pParent))
		return FALSE;
	CRect rc;
	wndStatic.GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	wndStatic.DestroyWindow();
	rc.bottom = rc.top + GetDesiredHeight();
	return Create(WS_CHILD|WS_VISIBLE, rc, pParent, nID);
}