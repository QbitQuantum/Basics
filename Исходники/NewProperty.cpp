BOOL CNewPropertySheet::OnInitDialog()
{
  BOOL bRetval = CPropertySheet::OnInitDialog();

  HMENU hMenu = m_SystemNewMenu.Detach();
  HMENU hSysMenu = ::GetSystemMenu(m_hWnd,FALSE);
  if(hMenu!=hSysMenu)
  {
    if(IsMenu(hMenu))
    {
      ::DestroyMenu(hMenu);
    }
  }
  m_SystemNewMenu.Attach(hSysMenu);
  m_DefaultNewMenu.LoadMenu(::GetMenu(m_hWnd));

  if(IsMenu(m_DefaultNewMenu.m_hMenu))
  {
    UpdateMenuBarColor(m_DefaultNewMenu);
  }

  return bRetval;
}