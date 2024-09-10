ATMO_BOOL CAtmoGradients::InitDialog(WPARAM wParam) 
{
	HWND groupBox = getDlgItem( IDC_ZONE_GROUP );
	CLanguage *Lng = new CLanguage;

	Lng->szCurrentDir[Lng->SetLngPath()];

	sprintf(Lng->szFileINI, "%s\\Language.ini\0", Lng->szCurrentDir);

	GetPrivateProfileString("Common", "Language", "English", Lng->szLang, 256, Lng->szFileINI);

	// Read Buffer from IniFile
	sprintf(Lng->szTemp, "%s\\%s.xml\0", Lng->szCurrentDir, Lng->szLang);

	Lng->XMLParse(Lng->szTemp, Lng->sGradientsText, "Gradients");  	

	SetWindowLongPtr(groupBox, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	OrgGroupBoxProc = (WNDPROC)SetWindowLongPtr(groupBox, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(GroupBoxProc));

	int zonenIdx = 0;
	char zonename[100];
	int xpos, ypos;

	int zoneCount = m_pConfig->getZoneCount() + 1;
	m_ZoneRadios = new HWND[ zoneCount ];

	for(int i=0; i<zoneCount; i++)
		m_ZoneRadios[i] = 0;

#define radio_width 60
#define radio_height 20


	xpos = 10;
	ypos = 12;
	RECT rect, rrect;
	GetClientRect( groupBox, &rect );
	GetWindowRect( groupBox, &rrect );

	if(m_pConfig->getZonesTopCount() > 0) 
	{
		int radioWidth = (rect.right - rect.left - 20) /  (m_pConfig->getZonesTopCount() + 1);

		xpos = 10 + radioWidth -  radio_width/2;

		for( int zone=0; zone < m_pConfig->getZonesTopCount(); zone++)
		{
			sprintf( zonename, Lng->sGradientsText[0] + "%d", zonenIdx );
			HWND handle = CreateWindow("BUTTON", zonename,
				BS_AUTORADIOBUTTON  | BS_LEFTTEXT  | WS_VISIBLE | WS_TABSTOP | WS_CHILD, 
				xpos, ypos, radio_width, radio_height, groupBox, NULL, m_hInst, NULL);
			SetWindowFont(handle, GetWindowFont(m_hDialog), false);

			m_ZoneRadios[ zonenIdx ] = handle;
			zonenIdx++;
			xpos += radioWidth;
		}
	}

	if( m_pConfig->getZonesLRCount() > 0 )
	{
		int radioHeight = (rect.bottom - rect.top - 40) / (m_pConfig->getZonesLRCount() + 1);

		xpos = rect.right - 10 - radio_width;
		ypos = rect.top + 20 + radioHeight - radio_height / 2;

		for( int zone=0; zone < m_pConfig->getZonesLRCount(); zone++)
		{
			sprintf( zonename, Lng->sGradientsText[0] + "%d", zonenIdx );
			HWND handle = CreateWindow("BUTTON", zonename,
				BS_AUTORADIOBUTTON  | BS_LEFTTEXT  | WS_VISIBLE | WS_TABSTOP | WS_CHILD, 
				xpos, ypos, radio_width, radio_height, groupBox, NULL, m_hInst, NULL);
			SetWindowFont(handle, GetWindowFont(m_hDialog), false);


			m_ZoneRadios[ zonenIdx ] = handle;
			zonenIdx++;
			ypos += radioHeight;
		}
	}

	if(m_pConfig->getZonesBottomCount() > 0) 
	{
		int radioWidth = (rect.right - rect.left - 20) /  (m_pConfig->getZonesBottomCount() + 1);
		xpos = rect.right -  10 - radioWidth - radio_width/2 ;
		ypos = rect.bottom - 30;

		for( int zone=0; zone < m_pConfig->getZonesBottomCount(); zone++)
		{
			sprintf( zonename, Lng->sGradientsText[0] + "%d", zonenIdx );

			HWND handle = CreateWindow("BUTTON", zonename,
				BS_AUTORADIOBUTTON  | BS_LEFTTEXT  | WS_VISIBLE | WS_TABSTOP | WS_CHILD, 
				xpos, ypos, radio_width, radio_height, groupBox, NULL, m_hInst, NULL);
			SetWindowFont(handle, GetWindowFont(m_hDialog), false);


			m_ZoneRadios[ zonenIdx ] = handle;

			zonenIdx++;
			xpos -= radioWidth;
		}
	}

	if( m_pConfig->getZonesLRCount() > 0 )
	{
		int radioHeight = (rect.bottom - rect.top - 40) / (m_pConfig->getZonesLRCount() + 1);

		xpos = rect.left + 10;
		ypos = rect.bottom - 20 - radioHeight - radio_height / 2;

		for( int zone=0; zone < m_pConfig->getZonesLRCount(); zone++)
		{
			sprintf( zonename, Lng->sGradientsText[0] + "%d", zonenIdx );
			HWND handle = CreateWindow("BUTTON", zonename,
				BS_AUTORADIOBUTTON  | BS_RIGHT | WS_VISIBLE | WS_TABSTOP | WS_CHILD, 
				xpos, ypos, radio_width, radio_height, groupBox, NULL, m_hInst, NULL);
			SetWindowFont(handle, GetWindowFont(m_hDialog), false);


			m_ZoneRadios[ zonenIdx ] = handle;
			zonenIdx++;
			ypos -= radioHeight;
		}
	}

	if( m_pConfig->getZoneSummary() )
	{
		xpos = rect.left + 20 + radio_width;
		ypos = (rect.bottom - 50);

		sprintf( zonename, Lng->sGradientsText[1] + "%d", zonenIdx );
		HWND handle = CreateWindow("BUTTON", zonename,
			BS_AUTORADIOBUTTON  | BS_RIGHT | WS_VISIBLE | WS_TABSTOP | WS_CHILD, 
			xpos, ypos, 100, radio_height, groupBox, NULL, m_hInst, NULL);

		SetWindowFont(handle, GetWindowFont(m_hDialog), false);

		m_ZoneRadios[ zonenIdx ] = handle;
		zonenIdx++;
	}

	m_ZoneRadios[ zonenIdx ] = 0;

	this->SetupSliderControl(IDC_EDGE_WEIGHT,1,30,this->m_edge_weight,5);
	SendMessage(getDlgItem(IDC_EDGE_WEIGHT),TBM_SETPAGESIZE,0,2);

	char buffer[32];
	sprintf(buffer,Lng->sGradientsText[2] + "[%d]",m_edge_weight);
	SetWindowText( getDlgItem(IDC_STATIC_EDGEW), buffer);

	if(zonenIdx > 0) {
		SetActiveZone( 0 );
		SendMessage( m_ZoneRadios[ 0 ], (UINT)BM_SETCHECK, BST_CHECKED, 0);
	}

	SendMessage(this->m_hDialog, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)(Lng->sGradientsText[15]));
	SendMessage(getDlgItem(IDCANCEL), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)(Lng->sGradientsText[16]));
	SendMessage(getDlgItem(IDC_ZONE_GROUP), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)(Lng->sGradientsText[17]));

	return ATMO_FALSE;
}