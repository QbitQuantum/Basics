void CBtDld_General::OnChoosefolder()
{
	CString str = "";
	GetDlgItemText (IDC_SAVEIN, str);

	if ((GetFileAttributes (str) & FILE_ATTRIBUTE_DIRECTORY) == 0)
	{
		char sz [MY_MAX_PATH];
		fsGetPath (str, sz);
		str = sz;
	}

	if (str.GetLength () > 3 &&
			(str [str.GetLength () - 1] == '\\' || str [str.GetLength () - 1] == '/'))
	{
		str.GetBuffer (0) [str.GetLength () - 1] = 0;
		str.ReleaseBuffer ();
	}
	
	CFolderBrowser *fb = CFolderBrowser::Create (LS (L_CHOOSEOUTFOLDER), str, NULL, this);
	if (fb == NULL)
		return;

	for (size_t i = 0; i < m_pvDlds->size (); i++)
		m_pvDlds->at (i)->pMgr->MoveToFolder (fb->GetPath ());

	ReadSavedIn ();
}