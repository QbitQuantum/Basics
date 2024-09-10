CPlugin::CPlugin(const PluginStartupInfo *Info)
{
  m_hModule=(HINSTANCE)GetModuleHandle(Info->ModuleName);
  m_pMalloc=NULL;
  NULL_HWND=NULL;
  REG_WaitToContinue=L"WaitToContinue";
  REG_UseGUI=L"UseGUI";
  REG_DelUsingFar=L"DelUsingFar";
  REG_ClearSel=L"ClearSelection";
  REG_Silent=L"Silent";
  REG_Helptext=L"Helptext";
  REG_DifferentOnly=L"DifferentOnly";
  REG_GuiPos=L"GuiPos";
  SelectedItems=NULL;
  SelectedItemsCount=0;

  *(PluginStartupInfo*)this=*Info;
  m_fsf=*Info->FSF;

  ReadRegValues();

  m_bWin2K = !IsWindowsXPOrGreater();
}