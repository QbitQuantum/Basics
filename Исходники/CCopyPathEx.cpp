//当用户点击我们添加的菜单项时该方法将被调用
HRESULT CCCopyPathEx::InvokeCommand ( LPCMINVOKECOMMANDINFO pCmdInfo )
{	
	HWND m_pWnd = NULL;
	LogTrace("菜单ID：%d", LOWORD(pCmdInfo->lpVerb));

	m_pWnd = FindWindow(NULL,_T("Spring                                {8192000D-A7B6-433a-8B40-53A3FC3EC52A}")); // 查找DataRecv进程.
	if(m_pWnd == NULL)
	{
		MessageBox(NULL, TEXT("Unable to find DataRecv."), NULL, MB_OK);
		//return;
	}
	COPYDATASTRUCT cpd = {0}; // 给COPYDATASTRUCT结构赋值.
	cpd.dwData = 0;

	try {
		// copy the string to the clipboard
		if (!::OpenClipboard(pCmdInfo->hwnd))
		{
			// Fail silently
			return S_OK;
		}

		int cTextBytes = 0;
		if ( 1 == m_cFiles ) 
		{
			cTextBytes = (_tcslen( m_szFile ) + 1) * sizeof(TCHAR);
		} 
		else 
		{
			for ( int iFile = 0; iFile < m_cFiles; iFile++ ) 
			{
				cTextBytes += ((m_lstFiles[ iFile ].length() + 2 /*\r\n*/) * sizeof(TCHAR));
			}
			cTextBytes += sizeof(TCHAR); // null terminator
		}

		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cTextBytes );
		if (hGlobal != NULL)
		{
			LPVOID lpText = GlobalLock(hGlobal);
			memset( lpText, 0, cTextBytes );
			if ( 1 == m_cFiles ) 
			{
				memcpy(lpText, m_szFile, cTextBytes);
				LogTrace("选择一个文件，文件名:%s;", m_szFile);
				//MessageBox(NULL, m_szFile, "Tips", MB_OK);
				cpd.cbData = strlen(m_szFile);
				cpd.lpData = (void*)lpText;
				::SendMessage(m_pWnd, WM_COPYDATA, NULL, (LPARAM)&cpd);
				//m_pWnd->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd);// 发送.
			} 
			else 
			{
				LPTSTR szText = (LPTSTR)lpText;
				for ( int iFile = 0; iFile < m_cFiles; iFile++ ) 
				{
					_tcscat( szText, m_lstFiles[ iFile ].c_str() );
					_tcscat( szText, _T("\r\n") );

				}
				LogTrace("选择%d个文件，文件名:\r\n%s;", iFile, szText);
				//MessageBox(NULL, szText, "Tips", MB_OK);
				cpd.cbData = strlen(szText);
				cpd.lpData = (void*)szText;
				//m_pWnd->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd);// 发送.
				::SendMessage(m_pWnd, WM_COPYDATA, NULL, (LPARAM)&cpd);
			}

			EmptyClipboard();
			GlobalUnlock(hGlobal);

#ifdef _UNICODE
			SetClipboardData(CF_UNICODETEXT, hGlobal);
#else
			SetClipboardData(CF_TEXT, hGlobal);
#endif
		}

		CloseClipboard();

	} 
	catch ( ... ) 
	{
		return E_FAIL;
	}

	return S_OK;
	/////////////////////////////////////////////////////////////////////////
	//// 如果lpVerb 实际指向一个字符串, 忽略此次调用并退出.
	//if ( 0 != HIWORD( pCmdInfo->lpVerb ))
	//	return E_INVALIDARG;
	//// 点击的命令索引 – 在这里，唯一合法的索引为0.
	//switch ( LOWORD( pCmdInfo->lpVerb ))
	//{
	//case 0:
	//	{
	//		TCHAR szMsg [MAX_PATH + 32];
	//		wsprintf ( szMsg, _T("The selected file was:\n\n%s"), m_szFile );
	//		MessageBox ( pCmdInfo->hwnd, szMsg, _T("CCCopyPathEx"),
	//			MB_ICONINFORMATION );
	//		return S_OK;
	//	}
	//	break;
	//default:
	//	return E_INVALIDARG;
	//	break;
	//}
}