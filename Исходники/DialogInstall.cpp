void DialogInstall::TabInstall::Initialize()
{
	HWND item = GetDlgItem(m_Window, IDC_INSTALLTAB_COMPONENTS_LIST);

	DWORD extendedFlags = LVS_EX_CHECKBOXES | LVS_EX_LABELTIP | LVS_EX_FULLROWSELECT;

	if (GetOSPlatform() >= OSPLATFORM_VISTA)
	{
		extendedFlags |= LVS_EX_DOUBLEBUFFER;
		SetWindowTheme(item, L"explorer", nullptr);
	}

	ListView_EnableGroupView(item, TRUE);
	ListView_SetExtendedListViewStyleEx(item, 0, extendedFlags);

	// Add columns
	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iSubItem = 0;
	lvc.cx = 180;
	lvc.pszText = L"Name";
	ListView_InsertColumn(item, 0, &lvc);
	lvc.iSubItem = 1;
	lvc.cx = 150;
	lvc.pszText = L"Action";
	ListView_InsertColumn(item, 1, &lvc);

	// Add groups and items
	LVGROUP lvg;
	lvg.cbSize = sizeof(LVGROUP);
	lvg.mask = LVGF_HEADER | LVGF_GROUPID | LVGF_STATE;
	lvg.state = (GetOSPlatform() >= OSPLATFORM_VISTA) ? LVGS_COLLAPSIBLE : LVGS_NORMAL;

	LVITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_GROUPID | LVIF_PARAM;
	lvi.iSubItem = 0;

	auto addComponent = [&](const WCHAR* name, const std::set<std::wstring>& items, const std::wstring& path, int groupId)
	{
		lvg.iGroupId = groupId;
		lvg.pszHeader = (WCHAR*)name;
		ListView_InsertGroup(item, groupId, &lvg);

		lvi.iGroupId = groupId;
		lvi.iItem = 0;
		for (auto iter = items.cbegin(); iter != items.cend(); ++iter)
		{
			lvi.pszText = (WCHAR*)(*iter).c_str();
			lvi.lParam = (LPARAM)&(*iter);
			ListView_InsertItem(item, &lvi);
			ListView_SetCheckState(item, lvi.iItem, TRUE);

			std::wstring itemPath = path + *iter;
			WCHAR* text = L"Add";
			if (_waccess(itemPath.c_str(), 0) != -1)
			{
				bool backup = groupId == 0 && c_Dialog->m_BackupSkins && !c_Dialog->m_BackupPackage;
				text = backup ? L"Backup and replace" : L"Replace";
			}
			ListView_SetItemText(item, lvi.iItem, 1, text);

			++lvi.iItem;
		}
	};

	addComponent(L"Skins", c_Dialog->m_PackageSkins, g_Data.skinsPath, 0);
	addComponent(L"Layouts", c_Dialog->m_PackageLayouts, g_Data.settingsPath + L"Layouts\\", 1);
	addComponent(L"Addons", c_Dialog->m_PackageAddons, g_Data.settingsPath + L"Addons\\", 2);
	addComponent(L"Plugins", c_Dialog->m_PackagePlugins, g_Data.settingsPath + L"Plugins\\", 3);

	item = GetDlgItem(m_Window, IDC_INSTALLTAB_THEME_CHECKBOX);
	if (!c_Dialog->m_LoadLayout.empty())
	{
		Button_SetCheck(item, BST_CHECKED);
	}
	else if (!c_Dialog->m_LoadSkins.empty())
	{
		SetWindowText(item, L"Load included skins");
		Button_SetCheck(item, BST_CHECKED);
	}
	else
	{
		ShowWindow(item, SW_HIDE);
	}

	m_Initialized = true;
}