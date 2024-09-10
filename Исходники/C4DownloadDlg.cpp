bool C4DownloadDlg::DownloadFile(const char *szDLType, C4GUI::Screen *pScreen, const char *szURL, const char *szSaveAsFilename, const char *szNotFoundMessage)
{
	// log it
	LogF(LoadResStr("IDS_PRC_DOWNLOADINGFILE"), szURL);
	// show download dialog
	C4DownloadDlg *pDlg = new C4DownloadDlg(szDLType);
	if (!pDlg->ShowModal(pScreen, szURL, szSaveAsFilename))
	{
		// show an appropriate error
		const char *szError = pDlg->GetError();
		if (!szError || !*szError) szError = LoadResStr("IDS_PRC_UNKOWNERROR");
		StdStrBuf sError;
		sError.Format(LoadResStr("IDS_PRC_DOWNLOADERROR"), GetFilename(szURL), szError);
		// it's a 404: display extended message
		if (SSearch(szError, "404") && szNotFoundMessage)
			{ sError.Append("|"); sError.Append(szNotFoundMessage); }
		// display message
		pScreen->ShowMessageModal(sError.getData(), FormatString(LoadResStr("IDS_CTL_DL_TITLE"), szDLType).getData(), C4GUI::MessageDialog::btnOK, C4GUI::Ico_Error, NULL);
		delete pDlg;
		return false;
	}
	LogF(LoadResStr("IDS_PRC_DOWNLOADCOMPLETE"), szURL);
	delete pDlg;
	return true;
}