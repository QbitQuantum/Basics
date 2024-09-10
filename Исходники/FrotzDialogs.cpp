BOOL OptionsDialog::OnInitDialog() 
{
  CPropertySheet::OnInitDialog();

  // Enable context sensitive help
  ModifyStyleEx(0,WS_EX_CONTEXTHELP);

  // Create the font to use
  m_font.CreateFontIndirect(&m_logFont);

  // Set the font for the property pages
  ChangeDialogFont(this,&m_font);
  CPropertyPage* page = GetActivePage();
  for (int i = 0; i < GetPageCount(); i++)
  {
    SetActivePage(i);
    CPropertyPage* page = GetActivePage();
    ChangeDialogFont(page,&m_font);
  }
  SetActivePage(page);

  // Resize the property page
  CTabCtrl* tab = GetTabControl();
  tab->GetWindowRect(&m_page);
  ScreenToClient(&m_page);
  tab->AdjustRect(FALSE,&m_page);
  page->MoveWindow(&m_page);

  return TRUE;
}