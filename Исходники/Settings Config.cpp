LRESULT	CSettingConfig::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	stdstr ConfigRomTitle, GameIni(g_Settings->LoadStringVal(Game_IniKey));

	if (!GameIni.empty())
	{
		ConfigRomTitle.Format("Config: %s",g_Settings->LoadStringVal(Game_GoodName).c_str());
	}

	RECT rcSettingInfo;
	::GetWindowRect(GetDlgItem(IDC_SETTING_INFO),&rcSettingInfo);
	::MapWindowPoints(NULL,m_hWnd,(LPPOINT)&rcSettingInfo,2);

	CConfigSettingSection * SettingsSection;

	//Set the text for all gui Items
	SetDlgItemTextW(m_hWnd, IDC_RESET_PAGE, GS(BOTTOM_RESET_PAGE));
	SetDlgItemTextW(m_hWnd, IDC_RESET_ALL, GS(BOTTOM_RESET_ALL));
	SetDlgItemTextW(m_hWnd, IDOK, GS(CHEAT_OK));
	SetDlgItemTextW(m_hWnd, IDCANCEL, GS(CHEAT_CANCEL));
	SetDlgItemTextW(m_hWnd, IDAPPLY, GS(BOTTOM_APPLY));

	if (m_GameConfig)
	{
		if (g_Settings->LoadBool(Setting_RdbEditor))
		{
			SetWindowText(stdstr_f("%s ** RDB Edit Mode **",ConfigRomTitle.c_str()).c_str());
		} 
		else 
		{
			SetWindowText(ConfigRomTitle.c_str());
		}		
	}
	else 
	{
		if (g_Settings->LoadBool(Setting_RdbEditor))
		{
			SetWindowText(stdstr_f("%ws ** RDB Edit Mode **",GS(OPTIONS_TITLE)).c_str());
		} else {
			::SetWindowTextW(m_hWnd, GS(OPTIONS_TITLE));
		}

		if (g_Settings->LoadBool(Setting_PluginPageFirst))
		{
			SettingsSection = new CConfigSettingSection(GS(TAB_PLUGIN));
			SettingsSection->AddPage(new COptionPluginPage(this->m_hWnd,rcSettingInfo ));
			m_Sections.push_back(SettingsSection);
		}

		m_GeneralOptionsPage = new CGeneralOptionsPage(this,this->m_hWnd,rcSettingInfo );
		m_AdvancedPage = new CAdvancedOptionsPage(this->m_hWnd,rcSettingInfo );

		SettingsSection = new CConfigSettingSection(GS(TAB_OPTIONS));
		SettingsSection->AddPage(m_GeneralOptionsPage);
		SettingsSection->AddPage(m_AdvancedPage);
		SettingsSection->AddPage(new COptionsDirectoriesPage(this->m_hWnd,rcSettingInfo ));
		m_Sections.push_back(SettingsSection);

		SettingsSection = new CConfigSettingSection(GS(TAB_ROMSELECTION));
		SettingsSection->AddPage(new COptionsGameBrowserPage(this->m_hWnd,rcSettingInfo ));
		m_Sections.push_back(SettingsSection);

		SettingsSection = new CConfigSettingSection(GS(TAB_SHORTCUTS));
		SettingsSection->AddPage(new COptionsShortCutsPage(this->m_hWnd,rcSettingInfo ));
		m_Sections.push_back(SettingsSection);

		if (!g_Settings->LoadBool(Setting_PluginPageFirst))
		{
			SettingsSection = new CConfigSettingSection(GS(TAB_PLUGIN));
			SettingsSection->AddPage(new COptionPluginPage(this->m_hWnd,rcSettingInfo ));
			m_Sections.push_back(SettingsSection);
		}
	}

	//Game Settings
	if (!GameIni.empty())
	{
        CConfigSettingSection * GameSettings = new CConfigSettingSection(ConfigRomTitle.ToUTF16().c_str());
		GameSettings->AddPage(new CGameGeneralPage(this->m_hWnd,rcSettingInfo ));
		GameSettings->AddPage(new CGameRecompilePage(this->m_hWnd,rcSettingInfo ));
		GameSettings->AddPage(new CGamePluginPage(this->m_hWnd,rcSettingInfo ));
		if (g_Settings->LoadBool(Setting_RdbEditor))
		{
			GameSettings->AddPage(new CGameStatusPage(this->m_hWnd,rcSettingInfo ));
		}
		m_Sections.push_back(GameSettings);
	}

	
	m_PagesTreeList.Attach(GetDlgItem(IDC_PAGELIST));

	bool bFirstItem = true;
	bool HideAdvanced = g_Settings->LoadBool(UserInterface_BasicMode);
	for (SETTING_SECTIONS::const_iterator iter = m_Sections.begin(); iter != m_Sections.end(); iter++)
	{
		CConfigSettingSection * Section = *iter;
		
		HTREEITEM hSectionItem = NULL;	

		for (size_t i = 0; i < Section->GetPageCount(); i++)
		{
			CSettingsPage * Page = Section->GetPage(i);
			if (HideAdvanced && Page == m_AdvancedPage)
			{
				continue;
			}
			if (i == 0)
			{
				hSectionItem = m_PagesTreeList.InsertItemW(TVIF_TEXT | TVIF_PARAM,Section->GetPageTitle(),0,0,0,0,(ULONG)Page,TVI_ROOT,TVI_LAST);
				continue;
			}
			if (hSectionItem == NULL)
			{
				continue;
			}
			m_PagesTreeList.InsertItemW(TVIF_TEXT | TVIF_PARAM,GS(Page->PageTitle()),0,0,0,0,(ULONG)Page,hSectionItem,TVI_LAST);
		}
		if (bFirstItem && hSectionItem != NULL)
		{
			bFirstItem = false;
			m_PagesTreeList.Expand(hSectionItem);
			m_PagesTreeList.SelectItem(hSectionItem);
		}
	}

	BoldChangedPages(m_PagesTreeList.GetRootItem());
	return TRUE;
}