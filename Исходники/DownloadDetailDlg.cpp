void CDownloadDetailDlg::SetPartFileInfo(CKnownFile	*file)
{
	if(! file) return ;
	CPartFile	*pPartFile = NULL;
	if ( file->IsKindOf(RUNTIME_CLASS(CPartFile)) )
		pPartFile = (CPartFile*) file;



	SetDlgItemText(IDC_STATIC_FILENAME, file->GetFilePath());
	

	CString strTmp;
	time_t restTime;
	if ( NULL != pPartFile )
	{
		if (!thePrefs.UseSimpleTimeRemainingComputation())
			restTime = pPartFile->getTimeRemaining();
		else
			restTime = pPartFile->getTimeRemainingSimple();

		strTmp.Format(_T("%s (%s)"), CastSecondsToHM(restTime), CastItoXBytes((pPartFile->GetFileSize() - pPartFile->GetCompletedSize()), false, false));
		SetDlgItemText(IDC_STATIC_LAST_SEEN_TIME, strTmp);
	}

}