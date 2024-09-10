void CDownloaderProperties_NewDownloadPage::OnSetgrpsfldr() 
{
	CFolderBrowser *fb = CFolderBrowser::Create (LS (L_CHOOSEOUTFOLDER), 
		_DldsGrps.FindGroup (GRP_OTHER_ID)->strOutFolder, NULL, this);
	if (fb == NULL)
		return;

	CString str = fb->GetPath ();
	if (str.Right (1) != '\\')
		str += '\\';

	if (MessageBox (LS (L_ALLGRPSFLDRSWBCHANGEDTOTHISFLDR), NULL, MB_YESNO) == IDNO)
		return;

	for (size_t i = 0; i < _DldsGrps.GetTotalCount (); i++) {
		_DldsGrps.GetGroup (i)->strOutFolder = str;
		_DldsGrps.GetGroup (i)->setDirty();
		
	}

	
	
	
	
}