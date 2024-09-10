void CToxOptionsNodeList::OnInitDialog()
{
	m_nodes.SetExtendedListViewStyle(LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);

	HIMAGELIST hImageList = m_nodes.CreateImageList(LVSIL_SMALL);
	HICON icon = Skin_LoadIcon(SKINICON_OTHER_TYPING);
	ImageList_AddIcon(hImageList, icon); IcoLib_ReleaseIcon(icon);
	icon = Skin_LoadIcon(SKINICON_OTHER_DELETE);
	ImageList_AddIcon(hImageList, icon); IcoLib_ReleaseIcon(icon);

	m_nodes.AddColumn(0, _T("IPv4"), 100);
	m_nodes.AddColumn(1, _T("IPv6"), 100);
	m_nodes.AddColumn(2, TranslateT("Port"), 50);
	m_nodes.AddColumn(3, TranslateT("Public key"), 130);
	m_nodes.AddColumn(4, _T(""), 32 - GetSystemMetrics(SM_CXVSCROLL));
	m_nodes.AddColumn(5, _T(""), 32 - GetSystemMetrics(SM_CXVSCROLL));

	m_nodes.EnableGroupView(TRUE);
	m_nodes.AddGroup(0, TranslateT("Common nodes"));
	m_nodes.AddGroup(1, TranslateT("User nodes"));

	////////////////////////////////////////

	int iItem = -1;

	if (CToxProto::IsFileExists((TCHAR*)VARST(_T(TOX_INI_PATH))))
	{
		char fileName[MAX_PATH];
		mir_strcpy(fileName, VARS(TOX_INI_PATH));

		char *section, sections[MAX_PATH], value[MAX_PATH];
		GetPrivateProfileSectionNamesA(sections, _countof(sections), fileName);
		section = sections;
		while (*section != NULL)
		{
			if (strstr(section, TOX_SETTINGS_NODE_PREFIX) == section)
			{
				GetPrivateProfileStringA(section, "IPv4", NULL, value, _countof(value), fileName);
				iItem = m_nodes.AddItem(mir_a2t(value), -1, NULL, 0);

				GetPrivateProfileStringA(section, "IPv6", NULL, value, _countof(value), fileName);
				m_nodes.SetItem(iItem, 1, mir_a2t(value));

				GetPrivateProfileStringA(section, "Port", NULL, value, _countof(value), fileName);
				m_nodes.SetItem(iItem, 2, mir_a2t(value));

				GetPrivateProfileStringA(section, "PubKey", NULL, value, _countof(value), fileName);
				m_nodes.SetItem(iItem, 3, mir_a2t(value));
			}
			section += mir_strlen(section) + 1;
		}
	}

	char module[MAX_PATH], setting[MAX_PATH];
	mir_snprintf(module, "%s_Nodes", m_proto->m_szModuleName);
	int nodeCount = db_get_w(NULL, module, TOX_SETTINGS_NODE_COUNT, 0);
	for (int i = 0; i < nodeCount; i++)
	{
		mir_snprintf(setting, TOX_SETTINGS_NODE_IPV4, i);
		ptrT value(db_get_tsa(NULL, module, setting));
		iItem = m_nodes.AddItem(value, -1, NULL, 1);

		mir_snprintf(setting, TOX_SETTINGS_NODE_IPV6, i);
		value = db_get_tsa(NULL, module, setting);
		m_nodes.SetItem(iItem, 1, value);

		mir_snprintf(setting, TOX_SETTINGS_NODE_PORT, i);
		int port = db_get_w(NULL, module, setting, 0);
		if (port > 0)
		{
			char portNum[10];
			itoa(port, portNum, 10);
			m_nodes.SetItem(iItem, 2, mir_a2t(portNum));
		}

		mir_snprintf(setting, TOX_SETTINGS_NODE_PKEY, i);
		value = db_get_tsa(NULL, module, setting);
		m_nodes.SetItem(iItem, 3, value);

		m_nodes.SetItem(iItem, 4, _T(""), 0);
		m_nodes.SetItem(iItem, 5, _T(""), 1);
	}
}