BOOL 
HandleClickEventOnLink(HWND hwndLayout, HELEMENT helem, const wchar_t *url)
{
	wyInt32 tabicon;	
	MDIWindow *wnd = GetActiveWin();
	if(url)
	{
		tabicon = wnd->m_pctabmodule->GetActiveTabImage();

		if(tabicon == IDI_DATASEARCH)
		{
#ifndef COMMUNITY			
			TabDbSearch *tabsearch;
			tabsearch = dynamic_cast<TabDbSearch*>(wnd->m_pctabmodule->GetActiveTabType());
			
            if(!tabsearch)
            {
				return FALSE;
            }

			tabsearch->OnHyperLink(helem, url);
#endif
			return true;		
		}

		if(!wcsicmp(url, L"optimizer_help "))
        {
			ShowHelp("Schema%20Optimizer%20SQLyog%20MySQL%20GUI.htm");
        }
        else if(!wcsicmp(url, L"redundantindexes_help "))
        {
            ShowHelp("Redundant%20Indexes%20for%20SQLyog%20MySQL%20Client.htm");
        }
		else if(!wcsicmp(url, L"pref_others ")) 
		{
			PreferenceBase	*pref = CreatePreferences();
			
            if(pref)
			{
				if(pGlobals->m_entlicense.CompareI("Professional"))
				{
					pref->Create(4);
				}
				else
				{
					pref->Create(3);
				}

				delete pref;
			}
		}
		else if(!wcsicmp(url, L"http://www.webyog.com/shop/?ref=community.queryprofiler"))
        {
			::ShellExecuteW(hwndLayout,L"open", url, NULL,NULL,SW_SHOWNORMAL);
        }
        else
        {
            HandleClickTableURL(url);
            PostMessage(hwndLayout, UM_FOCUS, 0, 0);
        }
	}

	return true;		
}