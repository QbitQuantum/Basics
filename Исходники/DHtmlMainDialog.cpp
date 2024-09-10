void CDHtmlMainDialog::InitMenu()
{
	CMenu menu;
	CMenu subMenu;
	BOOL FlagHitTheme = FALSE;
	BOOL FlagHitLang = FALSE;
	UINT newItemID = 0;
	UINT currentItemID = 0;
	UINT defaultStyleItemID = 0;
	UINT defaultLanguageItemID = 0;
	WIN32_FIND_DATA findData;
	WIN32_FIND_DATA findCssData;
	HANDLE hFind;
	HANDLE hCssFind;
	CString themePath;
	CString themeCssPath;
	CString langPath;
	int i = 0;
	TCHAR *ptrEnd;
	TCHAR str[256];
	
	menu.Attach(GetMenu()->GetSafeHmenu());
	subMenu.Attach(menu.GetSubMenu(m_ThemeIndex)->GetSafeHmenu());
//	subMenu.RemoveMenu(0, MF_BYPOSITION);

	themePath.Format(_T("%s\\*.*"), m_ThemeDir);

	hFind = ::FindFirstFile(themePath, &findData);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		while(::FindNextFile(hFind, &findData) && i <= 0xFF)
		{
			if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
//				themeCssPath.Format(_T("%s\\%s\\%s"), m_ThemeDir,
//									findData.cFileName, MAIN_CSS_FILE_NAME);
				hCssFind = ::FindFirstFile(themeCssPath, &findCssData);
				if(hCssFind != INVALID_HANDLE_VALUE)
				{
					// Add Theme
					newItemID = WM_THEME_ID + i;
					i++;
					subMenu.AppendMenu(MF_STRING, (UINT_PTR)newItemID, findData.cFileName);
					m_MenuArrayTheme.Add(findData.cFileName);
					if(m_CurrentTheme.Compare(findData.cFileName) == 0)
					{
						currentItemID = newItemID;
						FlagHitTheme = TRUE;
					}
					if(_tcsstr(findData.cFileName, _T("default")) != NULL)
					{
						defaultStyleItemID = newItemID;
					}
				}
			}
		}
	}
	FindClose(hFind);

	if(! FlagHitTheme)
	{
		currentItemID = defaultStyleItemID;
		m_CurrentTheme = _T("default");
	}

	subMenu.CheckMenuRadioItem(WM_THEME_ID, WM_THEME_ID + (UINT)m_MenuArrayTheme.GetSize(),
								currentItemID, MF_BYCOMMAND);

	subMenu.Detach();

#ifdef _UNICODE
	subMenu.Attach(menu.GetSubMenu(m_LangIndex)->GetSafeHmenu());

	CMenu subMenuAN;
	CMenu subMenuOZ;

	subMenuAN.Attach(subMenu.GetSubMenu(0)->GetSafeHmenu()); // 1st is "A~N"
	subMenuAN.RemoveMenu(0, MF_BYPOSITION);
	subMenuOZ.Attach(subMenu.GetSubMenu(1)->GetSafeHmenu()); // 2nd is "O~Z"
	subMenuOZ.RemoveMenu(0, MF_BYPOSITION);

	langPath.Format(_T("%s\\*.lang"), m_LangDir);
	i = 0;
	hFind = ::FindFirstFile(langPath, &findData);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do{
			if(findData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				newItemID = WM_LANGUAGE_ID + i;
				i++;

				// Add Language
				CString cstr;
				cstr.Format(_T("%s\\%s"), m_LangDir, findData.cFileName);
				GetPrivateProfileString(_T("Language"), _T("LANGUAGE"), _T(""), str, 256, cstr);
				if((ptrEnd = _tcsrchr(findData.cFileName, '.')) != NULL)
				{
					*ptrEnd = '\0';
				}

				cstr.Format(_T("%s, [%s]"), str, findData.cFileName);
				if('A' <= findData.cFileName[0] && findData.cFileName[0] <= 'N')
				{
					subMenuAN.AppendMenu(MF_STRING, (UINT_PTR)newItemID, cstr);
				}
				else
				{
					subMenuOZ.AppendMenu(MF_STRING, (UINT_PTR)newItemID, cstr);
				}
				m_MenuArrayLang.Add(findData.cFileName);

				if(m_CurrentLang.Compare(findData.cFileName) == 0)
				{
					currentItemID = newItemID;
					FlagHitLang = TRUE;
				}
			}
		}while(::FindNextFile(hFind, &findData) && i <= 0xFF);
	}
	FindClose(hFind);

	subMenuAN.CheckMenuRadioItem(WM_LANGUAGE_ID, WM_LANGUAGE_ID + (UINT)m_MenuArrayLang.GetSize(),
								currentItemID, MF_BYCOMMAND);
	subMenuOZ.CheckMenuRadioItem(WM_LANGUAGE_ID, WM_LANGUAGE_ID + (UINT)m_MenuArrayLang.GetSize(),
								currentItemID, MF_BYCOMMAND);

	subMenuOZ.Detach();
	subMenuAN.Detach();
	subMenu.Detach();
	menu.Detach();
#else
	subMenu.Attach(menu.GetSubMenu(m_LangIndex)->GetSafeHmenu());
	subMenu.RemoveMenu(0, MF_BYPOSITION);//A~N
	subMenu.RemoveMenu(0, MF_BYPOSITION);//O~Z
	langPath.Format(_T("%s\\*.lang"), m_LangDir);
	i = 0;
	hFind = ::FindFirstFile(langPath, &findData);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do{
			if(findData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				newItemID = WM_LANGUAGE_ID + i;
				i++;

				// Add Language
				CString cstr;
				cstr.Format(_T("%s\\%s"), m_LangDir, findData.cFileName);
				GetPrivateProfileString(_T("Language"), _T("LANGUAGE"), _T(""), str, 256, cstr);
				if((ptrEnd = _tcsrchr(findData.cFileName, '.')) != NULL){
					*ptrEnd = '\0';
				}

				cstr.Format(_T("%s, [%s]"), str, findData.cFileName);
				subMenu.AppendMenu(MF_STRING, (UINT_PTR)newItemID, cstr);
				m_MenuArrayLang.Add(findData.cFileName);

				if(m_CurrentLang.Compare(findData.cFileName) == 0)
				{
					currentItemID = newItemID;
					FlagHitLang = TRUE;
				}
			}
		}while(::FindNextFile(hFind, &findData) && i <= 0xFF);

	}
	FindClose(hFind);

	subMenu.CheckMenuRadioItem(WM_LANGUAGE_ID, WM_LANGUAGE_ID + (UINT)m_MenuArrayLang.GetSize(),
								currentItemID, MF_BYCOMMAND);

	subMenu.Detach();
	menu.Detach();
#endif
	if(! FlagHitLang)
	{
		AfxMessageBox(_T("Fatal Error. Missing Language Files!!"));
	}
}