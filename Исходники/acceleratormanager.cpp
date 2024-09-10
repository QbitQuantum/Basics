void CAcceleratorManager::UpdateMenu(HMENU menu)
{
	int count = GetMenuItemCount(menu);

	OSVERSIONINFO info = {0};
	info.dwOSVersionInfoSize = sizeof(info);
	GetVersionEx(&info);

	if (info.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		MENUITEMINFO info = {0};
		info.cbSize = sizeof(info) - sizeof(HBITMAP);
		info.fMask  = MIIM_ID | MIIM_SUBMENU;
		for (int i = 0; i < count; i++)
		{
			GetMenuItemInfo(menu, i, TRUE, &info);

			if (info.hSubMenu != NULL)
			{
				UpdateMenu(info.hSubMenu);
			}
			else
			{
				if (info.wID != (UINT)-1)
				{
					char         ss[128];
					MENUITEMINFO info2 = {0};
					info2.cbSize     = sizeof(info2) - sizeof(HBITMAP);	// FIXME: why?
					info2.fMask      = MIIM_STRING;
					info2.dwTypeData = ss;
					info2.cch        = 128;
					GetMenuItemInfo(menu, i, MF_BYPOSITION, &info2);

					CString str(ss);
					int     index = str.Find('\t');
					if (index != -1)
						str = str.Left(index);

					WORD command = info.wID;

					CCmdAccelOb *o;
					if (m_mapAccelTable.Lookup(command, o))
					{
						if (o->m_Accels.GetCount())
						{
							POSITION   pos   = o->m_Accels.GetHeadPosition();
							CAccelsOb *accel = o->m_Accels.GetNext(pos);

							CString s;
							accel->GetString(s);
							str += "\t";
							str += s;
						}
					}
					if (str != ss)
						ModifyMenu(menu, i, MF_BYPOSITION | MF_STRING, info.wID, str);
				}
			}
		}
	}
	else
	{
		MENUITEMINFO info = {0};
		info.cbSize = sizeof(info);
		info.fMask  = MIIM_ID | MIIM_SUBMENU;
		for (int i = 0; i < count; i++)
		{
			GetMenuItemInfo(menu, i, TRUE, &info);

			if (info.hSubMenu != NULL)
			{
				UpdateMenu(info.hSubMenu);
			}
			else
			{
				if (info.wID != (WORD)-1)
				{
					wchar_t ss[128];
					wchar_t str[512];
					MENUITEMINFOW info2 = {0};
					info2.cbSize     = sizeof(info2);
					info2.fMask      = MIIM_STRING;
					info2.dwTypeData = ss;
					info2.cch        = 128;
					GetMenuItemInfoW(menu, i, MF_BYPOSITION, &info2);

					wcscpy(str, ss);

					wchar_t *p = wcschr(str, '\t');
					if (p)
						*p = 0;

					CCmdAccelOb *o;
					WORD         command = info.wID;
					if (m_mapAccelTable.Lookup(command, o))
					{
						if (o->m_Accels.GetCount())
						{
							POSITION pos = o->m_Accels.GetHeadPosition();

							CAccelsOb *accel = o->m_Accels.GetNext(pos);

							CString s;
							accel->GetString(s);

							wchar_t temp[128];
							temp[0] = '\t';
							temp[1] = 0;
							wcscat(str, temp);
							p = temp;
							for (const char *sp = s; *sp; sp++)
								*p++ = *sp;
							*p = 0;
							wcscat(str, temp);
						}
					}
					if (wcscmp(str, ss))
						ModifyMenuW(menu, i, MF_BYPOSITION | MF_STRING, info.wID, str);
				}
			}
		}
	}
}