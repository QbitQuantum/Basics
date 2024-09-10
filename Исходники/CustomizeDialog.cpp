LRESULT CCustomizeDialog::OnInitDialog( WPARAM /*wParam*/, LPARAM /*lParam*/ )
{
    CRect rcClient;
    GetClientRect( rcClient );
    CRect rcWindow;
    GetWindowRect( rcWindow );

	// create  the windows	// sizes are hardcoded //ugly way


	CRect  rc;
	CFont *pFont =GetFont();
	ASSERT_VALID(pFont);

	
  
	//static wnd
	rc=CRect(4,2,49,8);
	MapDialogRect(m_hWnd,&rc);
	rc.left+=rcClient.left;
	rc.top+=rcClient.bottom;
	VERIFY(m_wndTextOptionsText.Create(_T("Te&xt options:"),WS_CHILD|WS_VISIBLE,rc,this));
 	m_wndTextOptionsText.SetFont(pFont);
	m_wndTextOptionsText.SetWindowPos(NULL,rc.left,rc.top,rc.right,rc.bottom,SWP_NOZORDER|SWP_NOACTIVATE);

	
	//Text options
	rc=CRect(52,0,123,50);
	MapDialogRect(m_hWnd,&rc);
	rc.left+=rcClient.left;
	rc.top+=rcClient.bottom;
	VERIFY(m_wndTextOptions.Create(WS_CHILD |WS_VISIBLE |CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP,rc,this, IDC_CB_TEXTOPTIONS));
 	m_wndTextOptions.SetFont(pFont);

	m_wndTextOptions.AddString(_T("Show Text Labels"));
	m_wndTextOptions.AddString(_T("Selective Text on Right"));
	m_wndTextOptions.AddString(_T("No Text Labels"));

	SetTextOptions(m_eTextOptions);
	m_wndTextOptions.SetWindowPos(NULL,rc.left,rc.top,rc.right,rc.bottom,SWP_NOZORDER|SWP_NOACTIVATE);

 
	//static wnd
	rc=CRect(4,20,49,8);
	MapDialogRect(m_hWnd,&rc);
	rc.left+=rcClient.left;
	rc.top+=rcClient.bottom;
	VERIFY(m_wndIconOptionsText.Create(_T("Ico&n options:"),WS_CHILD|WS_VISIBLE,rc,this));
	m_wndIconOptionsText.SetFont(pFont);
	m_wndIconOptionsText.SetWindowPos(NULL,rc.left,rc.top,rc.right,rc.bottom,SWP_NOZORDER|SWP_NOACTIVATE);


	//icon combo
	rc=CRect(52,18,123,50);
	MapDialogRect(m_hWnd,&rc);
	rc.left+=rcClient.left;
	rc.top+=rcClient.bottom;
	VERIFY(m_wndIconOptions.Create(WS_CHILD |WS_VISIBLE |CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP,rc,this, IDC_CB_ICONOPTIONS));
 	m_wndIconOptions.SetFont(pFont);

	m_wndIconOptions.AddString(_T("Small Icons"));
	m_wndIconOptions.AddString(_T("Large Icons"));
	
	SetIconOptions(m_eIconOptions);
	m_wndIconOptions.SetWindowPos(NULL,rc.left,rc.top,rc.right,rc.bottom,SWP_NOZORDER|SWP_NOACTIVATE);



	// final rect
	rc=CRect(0,0,179,34);
	MapDialogRect(m_hWnd,&rc);
	rc.left+=rcClient.left;
	rc.top+=rcClient.bottom;
	
 
    // Increase height of Customize Toolbar dialog accordingly
    rcWindow.bottom += (rc.bottom+cyPadding);
    VERIFY( SetWindowPos( 0, 0, 0, rcWindow.Width(), rcWindow.Height(),
        SWP_NOZORDER | SWP_NOMOVE ) );

	//Set Title
	ASSERT(m_pToolBar);
	CString strName,strOrgName;
	m_pToolBar->GetWindowText(strName);

	if (!strName.IsEmpty())
	{
		GetWindowText(strOrgName);
		SetWindowText(strOrgName + _T(" - ")+ strName);
	}

    return Default();

}