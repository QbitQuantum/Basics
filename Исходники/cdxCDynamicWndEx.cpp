bool cdxCDynamicWndEx::StoreWindowPosition(LPCTSTR lpszProfile)
{
	if(!IsWindow() || !lpszProfile || !*lpszProfile)
	{
		ASSERT(false);
		return false;
	}

	CWnd	*pWnd	=	Window();

	WINDOWPLACEMENT	wpl;
	VERIFY( pWnd->GetWindowPlacement(&wpl) );
	CRect windowRect;
	pWnd->GetWindowRect(&windowRect);

	BOOL	bVisible	=	pWnd->IsWindowVisible();
	int	iState	=	REGVAL_NOSTATE;

	if(pWnd->IsIconic())
		iState	=	REGVAL_ICONIC;
	else
		if(pWnd->IsZoomed())
			iState	=	REGVAL_MAXIMIZED;

	CWinApp	*app	=	AfxGetApp();

	if(!app->m_pszRegistryKey || !*app->m_pszRegistryKey)
	{
		TRACE(_T("*** NOTE[cdxCDynamicWndEx::StoreWindowPosition()]: To properly store and restore a window's position, please call CWinApp::SetRegistryKey() in you app's InitInstance() !\n"));
		return false;
	}

	return	app->WriteProfileInt(lpszProfile,	lpszRegVal_Valid,	REGVAL_INVALID) &&	// invalidate first
				app->WriteProfileInt(lpszProfile,	lpszRegVal_Left,		windowRect.left) &&
				app->WriteProfileInt(lpszProfile,	lpszRegVal_Right,		windowRect.right) &&
				app->WriteProfileInt(lpszProfile,	lpszRegVal_Top,		windowRect.top) &&
				app->WriteProfileInt(lpszProfile,	lpszRegVal_Bottom,	windowRect.bottom) &&
//				app->WriteProfileInt(lpszProfile,	lpszRegVal_Left,		wpl.rcNormalPosition.left) &&
//				app->WriteProfileInt(lpszProfile,	lpszRegVal_Right,		wpl.rcNormalPosition.right) &&
//				app->WriteProfileInt(lpszProfile,	lpszRegVal_Top,		wpl.rcNormalPosition.top) &&
//				app->WriteProfileInt(lpszProfile,	lpszRegVal_Bottom,	wpl.rcNormalPosition.bottom) &&
				app->WriteProfileInt(lpszProfile,	lpszRegVal_Visible,	bVisible ? REGVAL_VISIBLE : REGVAL_HIDDEN) &&
				app->WriteProfileInt(lpszProfile,	lpszRegVal_State,		iState) &&
				app->WriteProfileInt(lpszProfile,	lpszRegVal_Valid,	REGVAL_VALID);		// validate position
}