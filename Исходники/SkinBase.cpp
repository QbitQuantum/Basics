BOOL CSkinBase::DoSysMenu(HWND hWnd, CPoint ptCursor, LPRECT prExclude, BOOL bCopy)
{
	HMENU hMenu = GetSystemMenu(hWnd, FALSE);
	ASSERT ( hMenu );
	
	if ( hMenu )
	{
		TPMPARAMS tpmp;
		tpmp.cbSize = sizeof(tpmp);

		if (prExclude)
			tpmp.rcExclude = *prExclude;
		else
			SetRectEmpty(&tpmp.rcExclude);

		UINT uAlignFlags = TPM_LEFTALIGN | TPM_TOPALIGN | TPM_VERTICAL | TPM_RIGHTBUTTON | TPM_RETURNCMD;
		UINT uID = 0;
		
		if (bCopy) // skinning
		{
			HMENU hSysMenu = CSkinBase::MakeMenuCopy(hMenu);
			ASSERT (hSysMenu);
			
			if (hSysMenu)
			{
				InitSysMenu( hSysMenu, pWnd );
				uID = ::TrackPopupMenuEx(hSysMenu, uAlignFlags, 
										ptCursor.x, ptCursor.y, hWnd, &tpmp);
				
				::DestroyMenu(hSysMenu); // cleanup
			}
		}
		else
		{
			InitSysMenu(hMenu, hWnd);
			uID = ::TrackPopupMenuEx(hMenu, uAlignFlags, 
									ptCursor.x, ptCursor.y, hWnd, &tpmp);
		}
		
		if (uID & 0xf000) // syscommand
		{
			//MSG& curMsg = AfxGetThreadState()->m_lastSentMsg;
			
			// always post this command to allow this function to unwind
			// correctly before the command is handled
			//pWnd->PostMessage(WM_SYSCOMMAND, (uID & 0xfff0), MAKELPARAM(curMsg.pt.x, curMsg.pt.y));
			PostMessage(hWnd, WM_SYSCOMMAND, (uID & 0xfff0), MAKELPARAM(ptCursor.x, ptCursor.y));
		}
	}
	
	return TRUE;
}