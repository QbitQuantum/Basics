int CRollupCtrl::_InsertPage(LPCTSTR caption, CDialog* pwndTemplate, int idx, BOOL bAutoDestroyTpl,BOOL bAutoExpand)
{
	ASSERT(pwndTemplate!=NULL);
	ASSERT(pwndTemplate->m_hWnd!=NULL);

	CRect r; GetClientRect(r);

	CColorCtrl<CButton>* groupbox = new CColorCtrl<CButton>;
	groupbox->Create("", WS_CHILD|BS_GROUPBOX, r, this, 0 );
	if (m_bkColor != 0)
	{
		groupbox->SetBkColor(m_bkColor);
	}

	CCustomButton* but = new CCustomButton;
	but->Create(caption, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_FLAT, r, this, 0 ); 
	if (m_bkColor != 0)
	{
		but->SetBkColor(m_bkColor);
	}

	HFONT hfont= (HFONT)EditorSettings::Get().Gui.hSystemFont;
	CFont* font = CFont::FromHandle(hfont);
	but->SetFont(font);

	RC_PAGEINFO*	pi	= new RC_PAGEINFO;
	pi->id				= m_lastId++;
	pi->bExpanded		= FALSE;
	pi->bEnable			= TRUE;
	pi->pwndTemplate	= pwndTemplate;
	pi->pwndButton		= but;
	pi->pwndGroupBox	= groupbox;
	pi->pOldDlgProc		= (WNDPROC)::GetWindowLongPtr(pwndTemplate->m_hWnd, DWLP_DLGPROC);
	pi->pOldButProc		= (WNDPROC)::GetWindowLongPtr(but->m_hWnd, GWLP_WNDPROC);
	pi->bAutoDestroyTpl	= bAutoDestroyTpl;

	int newidx;
	if (idx<0)	{
		m_PageList.push_back(pi);
		newidx = m_PageList.size()-1;
	}
	else	{ m_PageList.insert(m_PageList.begin()+idx,pi); newidx=idx; }

	::SetWindowLongPtr(pwndTemplate->m_hWnd, GWLP_USERDATA,	(LONG_PTR)m_PageList[newidx]);
	::SetWindowLongPtr(pwndTemplate->m_hWnd, DWLP_USER,		(LONG_PTR)this);

	::SetWindowLongPtr(but->m_hWnd, GWLP_USERDATA,	(LONG_PTR)m_PageList[newidx]);

	::SetWindowLongPtr(pwndTemplate->m_hWnd, DWLP_DLGPROC, (LONG_PTR)CRollupCtrl::DlgWindowProc);

	::SetWindowLongPtr(but->m_hWnd, GWLP_WNDPROC, (LONG_PTR)CRollupCtrl::ButWindowProc);

	m_nPageHeight+=RC_PGBUTTONHEIGHT+(RC_GRPBOXINDENT*2);
	RecalLayout();

	bool bExpanded = stl::FindInMap( m_expandedMap,caption,bAutoExpand==TRUE );
	if (bExpanded)
	{
		ExpandPage( pi->id,bExpanded,FALSE );
	}
	return pi->id;
}