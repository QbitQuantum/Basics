void CDlg_UnpackSettings::OnBrowse() 
{
	CString str = "";
	GetDlgItemText (IDC_DSTFOLDER, str);

	if (str.GetLength () > 3 && (str [str.GetLength () - 1] == '\\' || str [str.GetLength () - 1] == '/'))
		str.GetBuffer (0) [str.GetLength () - 1] = 0;

	CFolderBrowser *fb = CFolderBrowser::Create (LS (L_CHOOSEOUTFOLDER), str, NULL, this);
	if (fb == NULL)
		return;

	SetDlgItemText (IDC_DSTFOLDER, fb->GetPath ());
	GetDlgItem (IDC_DSTFOLDER)->SetFocus ();	
}