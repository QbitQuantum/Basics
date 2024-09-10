/* First Applet */
static LONG APIENTRY
Applet1(HWND hwnd, UINT uMsg, LPARAM wParam, LPARAM lParam)
{
  HPROPSHEETPAGE hpsp[MAX_POWER_PAGES];
  PROPSHEETHEADER psh;
  HPSXA hpsxa = NULL;
  TCHAR Caption[1024];
  SYSTEM_POWER_CAPABILITIES spc;
  LONG ret;

  UNREFERENCED_PARAMETER(uMsg);
  UNREFERENCED_PARAMETER(wParam);
  UNREFERENCED_PARAMETER(lParam);

  memset(Caption, 0x0, sizeof(Caption));
  LoadString(hApplet, IDS_CPLNAME_1, Caption, sizeof(Caption) / sizeof(TCHAR));

  ZeroMemory(&psh, sizeof(PROPSHEETHEADER));
  psh.dwSize = sizeof(PROPSHEETHEADER);
  psh.dwFlags = PSH_PROPTITLE;
  psh.hwndParent = hwnd;
  psh.hInstance = hApplet;
  psh.hIcon = LoadIcon(hApplet, MAKEINTRESOURCE(IDC_CPLICON_1));
  psh.pszCaption = Caption;
  psh.nPages = 0;
  psh.nStartPage = 0;
  psh.phpage = hpsp;

  InitPropSheetPage(&psh, IDD_PROPPAGEPOWERSHEMES, (DLGPROC)PowerSchemesDlgProc);
  if (GetPwrCapabilities(&spc))
  {
    if (spc.SystemBatteriesPresent)
	{
	  InitPropSheetPage(&psh, IDD_PROPPAGEALARMS, (DLGPROC)AlarmsDlgProc);
	}
  }
  InitPropSheetPage(&psh, IDD_PROPPAGEADVANCED, (DLGPROC)AdvancedDlgProc);
  InitPropSheetPage(&psh, IDD_PROPPAGEHIBERNATE, (DLGPROC)HibernateDlgProc);

  /* Load additional pages provided by shell extensions */
  hpsxa = SHCreatePropSheetExtArray(HKEY_LOCAL_MACHINE, REGSTR_PATH_CONTROLSFOLDER TEXT("\\Power"), MAX_POWER_PAGES - psh.nPages);
  if (hpsxa != NULL)
      SHAddFromPropSheetExtArray(hpsxa, PropSheetAddPage, (LPARAM)&psh);

  ret = (LONG)(PropertySheet(&psh) != -1);

  if (hpsxa != NULL)
    SHDestroyPropSheetExtArray(hpsxa);

  return ret;
}