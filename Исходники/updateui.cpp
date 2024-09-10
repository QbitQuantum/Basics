NDUPDATE_API
BOOL
WINAPI
NdasUpdateDoUpdate(
	IN HWND hWndParent,
	IN LPCTSTR szBaseURL,
	IN PNDUPDATE_SYSTEM_INFO pSystemInformation)
{
	HINSTANCE hResInst = _NdasUpdateDllInstance;
	NDUPDATE_UPDATE_INFO updateInformation = {0};

	CDownloadUI downloadUI;
	TCHAR szUpdaterTitle[MAX_STR_CAPTION];
	::LoadString(
		hResInst, 
		IDS_UPDATER_TITLE, 
		szUpdaterTitle, 
		MAX_STR_CAPTION);

	BOOL fSuccess = downloadUI.Initialize(
		hResInst,
		hWndParent,
		szUpdaterTitle);

	CString strBanner;
	strBanner.LoadString(IDS_STATUS_CHECK_UPDATE);
	downloadUI.SetBannerText(strBanner);

	fSuccess = ::NdasUpdateGetUpdateInfo(
		&CDownloadBindStatusCallback(&downloadUI), 
		szBaseURL,
		pSystemInformation,
		&updateInformation);


	if (!fSuccess) {

		CString strDescr;
		strDescr.LoadString(IDS_UPDATER_ERROR_UPDATE_CHECK);

		CString strFormatted;
		strFormatted.FormatMessage(
			IDS_UPDATER_ERROR_FMT, 
			(LPCTSTR)strDescr, 
			::GetLastError());

		::MessageBox(
			hWndParent, 
			strFormatted, 
			szUpdaterTitle, 
			MB_OK | MB_ICONERROR);

		downloadUI.Terminate();
		return FALSE;
	}

	strBanner.LoadString(IDS_STATUS_CHECK_UPDATE_DONE);
	downloadUI.SetBannerText(strBanner);

	if (!updateInformation.fNeedUpdate) {
		CString strMsg;
		strMsg.LoadString(IDS_NO_UPDATE);
		::MessageBox(
			hWndParent,
			strMsg,
			szUpdaterTitle,
			MB_OK | MB_ICONINFORMATION);
		downloadUI.Terminate();
		return TRUE;
	}

	CString strMsg;
	strMsg.LoadString(IDS_NEW_UPDATE);

	UINT_PTR uiResponse = ::MessageBox(
		hWndParent,
		strMsg,
		szUpdaterTitle,
		MB_YESNO | MB_ICONQUESTION);

	if (IDYES != uiResponse) {
		downloadUI.Terminate();
		return TRUE;
	}

	strBanner.LoadString(IDS_STATUS_DOWNLOAD_UPDATE);
	downloadUI.SetBannerText(strBanner);

	TCHAR szDownloaded[MAX_PATH];
	HRESULT hr = ::URLDownloadToCacheFile(
		NULL,
		updateInformation.szUpdateFileURL,
		szDownloaded,
		sizeof(szDownloaded),
		0,
		&CDownloadBindStatusCallback(&downloadUI));

	if (!downloadUI.HasUserCanceled() && FAILED(hr)) {

		CString strDescr;
		strDescr.LoadString(IDS_UPDATER_ERROR_DOWNLOAD);

		CString strFormatted;
		strFormatted.FormatMessage(
			IDS_UPDATER_ERROR_FMT, 
			(LPCTSTR)strDescr, 
			hr);

		::MessageBox(
			hWndParent, 
			strFormatted, 
			szUpdaterTitle, 
			MB_OK | MB_ICONERROR);

		downloadUI.Terminate();
		return FALSE;
	}

	strBanner.LoadString(IDS_STATUS_DOWNLOAD_UPDATE_DONE);
	downloadUI.SetBannerText(strBanner);
	
	downloadUI.Terminate();

	STARTUPINFO si = {0};
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi = {0};

	::CreateProcess(
		szDownloaded,
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi);

	return TRUE;
}