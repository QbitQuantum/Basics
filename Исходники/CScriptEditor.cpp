LRESULT CScriptEditor::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);

//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(675,513);
	SetWindowText(_TEXT("FrameWindowImpl0"));

	m_edit.Create(m_hWnd,CRect(0,0,675,490),_TEXT(""),WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|WS_TABSTOP|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL|ES_WANTRETURN,0,IDC_EDIT);
	m_edit.SetFont((HFONT)m_formFont);

	m_statusbarctrl1.Create(m_hWnd,CRect(0,490,675,513),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,0,IDC_CSCRIPTEDITOR_STATUSBARCTRL1);
	m_statusbarctrl1.SetFont((HFONT)m_formFont);

	Menu2.LoadMenu(IDR_SCRIPT_EDITOR);
//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
	SetMenu(Menu2);
	m_hWndClient=(HWND)m_edit;
	m_hWndStatusBar=(HWND)m_statusbarctrl1;
	m_edit.SetFocus();
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
//}}WTLBUILDER_TABSTOP
	//m_hAccel = AtlLoadAccelerators(IDR_SCRIPT_EDITOR);
	InitLayout();

	return 0;
}