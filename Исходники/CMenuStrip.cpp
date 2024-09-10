	//=============================================================================================================
	bool CMenuStrip::Initialize(HWND parent)
	{
		if( hmenu )
			return true;

		CWindow::Initialize(parent);
		hmenu = CreateMenu();

		for( size_t i = 0; i < submenus.size(); ++i )
		{
			popupmenu& pm = submenus[i];
			AppendMenuA(hmenu, MF_STRING|MF_POPUP, (UINT)pm.handle, pm.text.c_str());
		}

		SetMenu(parent, hmenu);
		return (hmenu != NULL);
	}