bool cdxCDynamicControlsManager::StoreWindowPosition(CWnd & rWnd, LPCTSTR lpszProfile)
{
	ASSERT(::IsWindow(rWnd.m_hWnd) && lpszProfile && *lpszProfile);
	// can't use an empty profile section string; see CWinApp::GetProfileInt() for further information

	WINDOWPLACEMENT	wpl;
	VERIFY( rWnd.GetWindowPlacement(&wpl) );
	BOOL	bVisible	=	rWnd.IsWindowVisible();
	int	iState	=	REGVAL_NOSTATE;

	if(rWnd.IsIconic())
		iState	=	REGVAL_ICONIC;
	else
		if(rWnd.IsZoomed())
			iState	=	REGVAL_MAXIMIZED;

	return	AfxGetApp()->WriteProfileInt(lpszProfile,	lpszRegVal_Valid,	REGVAL_INVALID) &&	// invalidate first
				AfxGetApp()->WriteProfileInt(lpszProfile,	lpszRegVal_Left,		wpl.rcNormalPosition.left) &&
				AfxGetApp()->WriteProfileInt(lpszProfile,	lpszRegVal_Right,		wpl.rcNormalPosition.right) &&
				AfxGetApp()->WriteProfileInt(lpszProfile,	lpszRegVal_Top,		wpl.rcNormalPosition.top) &&
				AfxGetApp()->WriteProfileInt(lpszProfile,	lpszRegVal_Bottom,	wpl.rcNormalPosition.bottom) &&
				AfxGetApp()->WriteProfileInt(lpszProfile,	lpszRegVal_Visible,	bVisible ? REGVAL_VISIBLE : REGVAL_HIDDEN) &&
				AfxGetApp()->WriteProfileInt(lpszProfile,	lpszRegVal_State,		iState) &&
				AfxGetApp()->WriteProfileInt(lpszProfile,	lpszRegVal_Valid,	REGVAL_VALID);		// validate position
}