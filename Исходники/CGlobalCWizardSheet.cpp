BOOL 
CGlobalCWizardSheet::OnInitDialog() 
{
	CMenu		*pSysMenu;
	HDC			hDC;
	PGPBoolean	loadedBitmap;
	PGPUInt32	numBits;

	CPropertySheet::OnInitDialog();

	// Get screen depth.
	hDC = ::GetDC(NULL);		// DC for desktop
	numBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	::ReleaseDC(NULL, hDC);

	// Load the bitmap and create a palette for it.
	if (numBits <= 1)
	{
		loadedBitmap = App->GetBitmapAndPalette(IDB_SIDEBAR1, 
			&mSidebarBitmap, &mSidebarPalette);
	}
	else if (numBits <= 4)
	{
		loadedBitmap = App->GetBitmapAndPalette(IDB_SIDEBAR4, 
			&mSidebarBitmap, &mSidebarPalette);
	}
	else
	{
		loadedBitmap = App->GetBitmapAndPalette(IDB_SIDEBAR8, 
			&mSidebarBitmap, &mSidebarPalette);
	}

	// Need to give the dialog a close box if we want a help box as well.
	ModifyStyle(NULL, WS_SYSMENU, NULL);

	// Show the context help button.
	ModifyStyleEx(NULL, WS_EX_CONTEXTHELP, NULL);

	// Alter the system menu.
	pSysMenu = GetSystemMenu(FALSE);
	pgpAssertAddrValid(pSysMenu, CMenu);

	pSysMenu->DeleteMenu(SC_MINIMIZE, MF_BYCOMMAND);
	pSysMenu->DeleteMenu(SC_MAXIMIZE, MF_BYCOMMAND);
	pSysMenu->DeleteMenu(SC_RESTORE, MF_BYCOMMAND);
	pSysMenu->DeleteMenu(SC_SIZE, MF_BYCOMMAND);

	DrawMenuBar();

	// Center on screen.
	CenterWindow(GetDesktopWindow());

	// Put us in front.
	SetForegroundWindow();

	// Put on top if necessary.
	App->TweakOnTopAttribute(this);

	return TRUE;
}