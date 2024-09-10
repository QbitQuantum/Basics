BOOL CFlashInterface::OnInitDialog()
{
	CurLangID = STANDARD_LANGID;
	HKEY hKey;
  	DWORD language;
    LONG returnStatus;
	DWORD Type=REG_DWORD;
    DWORD Size=sizeof(DWORD);
    returnStatus = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\CamStudioOpenSource for Nick\\vscap\\Language", 0L, KEY_ALL_ACCESS, &hKey);

	if (returnStatus == ERROR_SUCCESS)
    {

        returnStatus = RegQueryValueEx(hKey, "LanguageID", NULL, &Type,(LPBYTE)&language, &Size);

		if (returnStatus == ERROR_SUCCESS)
        {

        	if ( !LoadLangIDDLL((int) language) )
	         if ( !LoadLangIDDLL(GetUserDefaultLangID()) )
     			LoadLangIDDLL(GetSystemDefaultLangID());
        }
     }

    RegCloseKey(hKey);

	CPropertyPage::OnInitDialog();

	int valset = int(percentLoadedThreshold * 100.0);
	if (valset > 100) valset = 100;
	if (valset < 10) valset = 10;

	UDACCEL acc[2];
    acc[0].nSec = 1;
    acc[0].nInc = 5;

	acc[1].nSec = 3;
    acc[1].nInc = 10;

	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN1))->SetBuddy(GetDlgItem(IDC_PRELOADPERCENT));
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN1))->SetRange(10,100);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN1))->SetPos(valset);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN1))->SetAccel(2,acc);

	// TODO: Add extra initialization here
	((CEdit *)GetDlgItem(IDC_PRELOADBITMAP))->SetWindowText(loadingPath);

	local_swfbk_red = swfbk_red;
	local_swfbk_green = swfbk_green;
	local_swfbk_blue = swfbk_blue;

	CString foxStr,foyStr;
	foxStr.Format("%d",FrameOffsetX);
	foyStr.Format("%d",FrameOffsetY);
	((CEdit *) GetDlgItem(IDC_FRAMEOFFSETX))->SetWindowText(foxStr);
	((CEdit *) GetDlgItem(IDC_FRAMEOFFSETY))->SetWindowText(foyStr);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}