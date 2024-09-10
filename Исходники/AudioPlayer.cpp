CDROM* GetCDROM()
{
	CDROM* first = NULL;
	CDROM* last = NULL;
	wchar_t* name = L"²¥·Å¹âÅÌ(&G)";
	HMENU menu = GetMenu(main_wnd.hWnd);
	HMENU sub = GetSubMenu(menu, 0);
	MENUITEMINFO item = {0};
	item.fMask = MIIM_STRING | MIIM_ID | MIIM_SUBMENU;
	item.fType = MFT_STRING;
	item.fState = MFS_ENABLED;
	item.cbSize = sizeof(MENUITEMINFO);
	item.cch = wcslen(name);
	item.dwTypeData = name;	
	item.hSubMenu = CreateMenu();
	InsertMenuItem(sub, 1, TRUE, &item);
	
	DWORD n = GetLogicalDriveStrings(0, NULL);
	if (n > 0)
	{		
		wchar_t* buffer = new wchar_t[n];
		DWORD len = GetLogicalDriveStrings(n, buffer);
		wchar_t* ptr = buffer;
		DWORD i = 0;

		while (len > 0)
		{			
			UINT type = GetDriveType(ptr);
			if (type == DRIVE_CDROM)
			{				
				wchar_t driver[16] = {0};				
				StrCat(driver, L"\\\\.\\");				
				StrNCat(driver, ptr, 3);				
				name = CDROMName(driver);				
				if (name != NULL)
				{
					StrTrim(name, L" ");
					CDROM* cdrom = new CDROM();
					ZeroMemory(cdrom, sizeof(CDROM));
					StrNCat(cdrom->letter, ptr, 3);
					StrCat(cdrom->driver, driver);

					DWORD length = wcslen(name) + 16;
					cdrom->name = new wchar_t[length];
					wmemset(cdrom->name, 0, length);
					StrCat(cdrom->name, L"[");
					StrCat(cdrom->name, cdrom->letter);
					StrCat(cdrom->name, L"] ");
					StrCat(cdrom->name, name);
					SAFE_DELETE_ARRAY(name);
					
					cdrom->msgId = WM_USER + WM_CDROM + i;
					cdrom->next = NULL;
					i++;

					if (first == NULL)
					{
						first = cdrom;
						last = cdrom;
					}
					else
					{
						last->next = cdrom;
						last = cdrom;
					}

					MENUITEMINFO child = {0};
					child.fMask = MIIM_STRING | MIIM_ID;
					child.fType = MFT_STRING;
					child.fState = MFS_ENABLED;
					child.cbSize = sizeof(MENUITEMINFO);
					child.cch = wcslen(cdrom->name);
					child.dwTypeData = cdrom->name;
					child.wID = cdrom->msgId;
					
					InsertMenuItem(item.hSubMenu, 0, FALSE, &child);
				}			
			}

			ptr += 4;
			len -= 4;
		}

		SAFE_DELETE_ARRAY(buffer);
	}

	return first;
}