BOOL CDlgAutTexturize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrPretenderTextureSize.ResetContent();
  // add all available frictions
  for(INDEX iW=0; iW<10; iW++)
  {
    CTString strSize;
    strSize.PrintF("%dx%d pixels", 1<<iW, 1<<iW);
    m_ctrPretenderTextureSize.AddString( CString(strSize));
  }
  INDEX iSelected=6;
  iSelected=AfxGetApp()->GetProfileInt( L"World editor", L"Pretender resolution", iSelected);
  m_ctrPretenderTextureSize.SetCurSel(iSelected);

	m_ctrlPretenderTextureStyle.ResetContent();
  m_ctrlPretenderTextureStyle.AddString( L"Front view only");
  m_ctrlPretenderTextureStyle.AddString( L"Cylindrical view (FRBL)");
  m_ctrlPretenderTextureStyle.AddString( L"Boxed view (FRBLUD)");
  iSelected=1;
  iSelected=AfxGetApp()->GetProfileInt( L"World editor", L"Pretender style", iSelected);
  m_ctrlPretenderTextureStyle.SetCurSel(iSelected);
	return TRUE;
}