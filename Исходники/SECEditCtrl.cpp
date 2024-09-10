//@doc SECEditCtrl
//@mfunc This function should be called in the OnInitDialog handler
//for the dialog in which you want to place the SECEditCtrl.
//Note that this function destroys the window and replaces it, rather than
//just subclassing it. If you are replacing an Edit Control, you may use
//class wizard to map EN_SETFOCUS and EN_KILLFOCUS, and these notifications
//will be sent.
//@rdesc BOOL 
//@parm The ID of the control to replace
//@parm The parent window of SECEditCtrl
//@parm Extended style of the window (defaults to WS_EX_CLIENTEDGE)
//@comm dwExStyle defaults to WS_EX_CLIENTEDGE.
BOOL SECEditCtrl::Initialize(UINT nID, CWnd * pParentWnd, DWORD dwExStyle)
{
	CRect rect;
	CWnd* pWnd = pParentWnd->GetDlgItem(nID);
	pWnd->GetWindowRect(&rect);
	pParentWnd->ScreenToClient(&rect);

	// If creating dynamically, model your create call after this one
	BOOL bCreated = Create(NULL, _T("SECEdit"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 
						   rect, pParentWnd, nID);

	ASSERT(bCreated);
	if(!bCreated)
		return FALSE;

	// Set the Z-Order so this new control keeps the same tab order as the
	// control it is replacing
	SetWindowPos(pWnd, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);

	// Destroy the control being replaced
	pWnd->DestroyWindow();

	// Add 3D border to control
	ModifyStyleEx(NULL, dwExStyle, SWP_FRAMECHANGED);

	return bCreated;
}