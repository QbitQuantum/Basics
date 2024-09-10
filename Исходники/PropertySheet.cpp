	void PropSheet::Show(HINSTANCE hInstance, HWND hParent, std::string title, int startpage, bool floating, bool wizard)
	{	
		HPROPSHEETPAGE *pages = new HPROPSHEETPAGE[list.size()];
		PROPSHEETPAGE page;
		//common settings
		memset((void*)&page,0,sizeof(PROPSHEETPAGE));
		page.dwSize = sizeof(PROPSHEETPAGE);
		page.hInstance = hInstance;

		int i=0;
		for (DlgList::iterator iter = list.begin(); iter != list.end(); iter++, i++)
		{
			if (wizard)
			{
				if (i == 0 || i == list.size()-1)
					page.dwFlags = PSP_HIDEHEADER;
				else
					page.dwFlags = PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
			}
			else
			{
				page.dwFlags = PSP_USETITLE;
			}
			page.pszTemplate = iter->resource;
			page.pfnDlgProc = Tab::TabDlgProc;
			page.pszTitle = iter->title;
			page.pszHeaderTitle = wizard?iter->title:0;
			page.pszHeaderSubTitle = wizard?iter->hdrSubTitle:0;
			page.lParam = (LPARAM)iter->tab;
			pages[i] = CreatePropertySheetPage(&page);
		}

		PROPSHEETHEADER sheet;
		memset(&sheet,0,sizeof(sheet));
		sheet.dwSize = sizeof(PROPSHEETHEADER);
		sheet.hInstance = hInstance;
		sheet.hwndParent = hParent;
		sheet.pszbmWatermark = watermark;
		sheet.pszbmHeader = header;
		
		if (icon)
			sheet.hIcon = icon;

		if (wizard)
			sheet.dwFlags = PSH_USECALLBACK | PSH_WIZARD97 | (watermark?PSH_WATERMARK:0) | (header?PSH_HEADER:0);
		else
			sheet.dwFlags = PSH_USECALLBACK | PSH_PROPTITLE;

		if (floating)
			sheet.dwFlags |= PSH_MODELESS;
		//else
		//	sheet.dwFlags |= PSH_NOAPPLYNOW;

		if (icon) 
			sheet.dwFlags |= PSH_USEHICON;

		sheet.pszCaption = ConvertUTF8ToWString(title).c_str();
		sheet.nPages = (UINT)list.size();
		sheet.phpage = pages;
		sheet.nStartPage = startpage;
		sheet.pfnCallback = (PFNPROPSHEETCALLBACK)Callback;
		
		if (wizard)
		{
			NONCLIENTMETRICS ncm = {0};
			ncm.cbSize = sizeof(ncm);
			SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);

			//Create the intro/end title font
			LOGFONT TitleLogFont = ncm.lfMessageFont;
			TitleLogFont.lfWeight = FW_BOLD;
			lstrcpy(TitleLogFont.lfFaceName, TEXT("Verdana Bold"));
			//StringCchCopy(TitleLogFont.lfFaceName, 32, TEXT("Verdana Bold"));

			HDC hdc = GetDC(NULL); //gets the screen DC
			INT FontSize = 12;
			TitleLogFont.lfHeight = 0 - GetDeviceCaps(hdc, LOGPIXELSY) * FontSize / 72;
			hTitleFont = CreateFontIndirect(&TitleLogFont);
			ReleaseDC(NULL, hdc);
		}
		else
			hTitleFont = 0;

		centered=false;
		PropertySheet(&sheet);
		if (!floating)
		{
			for (DlgList::iterator iter = list.begin(); iter != list.end(); iter++)
			{
				delete iter->tab;
			}
			DeleteObject(hTitleFont);
		}
		delete [] pages;
	}