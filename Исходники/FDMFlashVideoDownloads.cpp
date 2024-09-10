STDMETHODIMP CFDMFlashVideoDownloads::ShowAddDownloadsDialog(BSTR bstrSrcWebPageUrl, SAFEARRAY *psaDownloads)
{
	USES_CONVERSION;

	CComObject <CFdmUiWindow> *pUiWindow = NULL;
	CComObject <CFdmUiWindow>::CreateInstance (&pUiWindow);

	vmsAUTOLOCKSECTION (m_csLastUiWindow);
	m_spLastUiWindow = pUiWindow;
	vmsAUTOLOCKSECTION_UNLOCK (m_csLastUiWindow);

	if (psaDownloads == NULL)
		return E_INVALIDARG;

	UINT cDim = SafeArrayGetDim (psaDownloads);
	if (cDim != 1)
		return E_INVALIDARG;

	LONG lLBound = 0, lUBound = 0;
	SafeArrayGetLBound (psaDownloads, 1, &lLBound);
	SafeArrayGetUBound (psaDownloads, 1, &lUBound);

	std::vector <vmsNewDownloadInfo> *pvDlds = new std::vector <vmsNewDownloadInfo>;

	for (long i = lLBound; i <= lUBound; i++)
	{
		IDispatchPtr spDisp;
		SafeArrayGetElement (psaDownloads, &i, &spDisp);

		IFdmFlvDownloadPtr spFlvDld (spDisp);

		if (spFlvDld == NULL)
		{
			delete pvDlds;
			return E_INVALIDARG;
		}
		IWGUrlReceiverPtr spUrl;
		spFlvDld->get_Url (&spUrl);
		if (spUrl == NULL)
		{
			delete pvDlds;
			return E_INVALIDARG;
		}

		CComBSTR bstr;
		spUrl->get_Url (&bstr);

		CString strUrl = W2CT (bstr);
		bool bSkip = false;

		for (size_t j = 0; j < pvDlds->size (); j++)
		{
			if (pvDlds->at (j).strUrl == strUrl)
			{
				bSkip = true; 
				break;
			}
		}

		if (bSkip)
			continue;

		vmsNewDownloadInfo dlInfo;

		dlInfo.strUrl = W2CA (bstr);

		spUrl->get_Referer (&bstr);
		dlInfo.strReferer = W2CA (bstr);

		spUrl->get_Comment (&bstr);
		dlInfo.strComment = bstr;

		dlInfo.dwWhatIsValid = NDIV_AP;

		dlInfo.ap.dwMask = DWCDAP_FLAGS;
		dlInfo.ap.dwFlags = DWDCDAP_F_FLASHVIDEODOWNLOAD;

		spUrl->get_Cookies (&bstr);
		if (bstr.Length ())
		{
			dlInfo.ap.dwMask |= DWCDAP_COOKIES;
			dlInfo.ap.strCookies = W2CA (bstr);
		}

		spUrl->get_PostData (&bstr);
		if (bstr.Length ())
		{
			dlInfo.ap.dwMask |= DWCDAP_POSTDATA;
			dlInfo.ap.strPostData = W2CA (bstr);
		}

		spUrl->get_FileName (&bstr);
		if (bstr.Length ())
		{
			dlInfo.ap.dwMask |= DWCDAP_FILENAME;
			dlInfo.ap.strFileName = W2CA (bstr);
		}

		spUrl->get_FileSize (&bstr);
		if (bstr.Length ())
		{
			dlInfo.ap.dwMask |= DWCDAP_FILESIZE;
			dlInfo.ap.uFileSize = (UINT64)_wtoi64 (bstr);
		}

		pvDlds->push_back (dlInfo);
	}

	CFlashVideoDownloadsWnd::WmFvdwLparam *lp = new CFlashVideoDownloadsWnd::WmFvdwLparam;
	lp->strSrcWebPageUrl = W2CA(bstrSrcWebPageUrl);
	lp->pvDlds = pvDlds;
	lp->pUiWindow = pUiWindow; 
	if (pUiWindow)
		pUiWindow->AddRef ();
	_pwndFVDownloads->PostMessage (WM_FVDW_CREATEDOWNLOADS, 0, (LPARAM)lp);

	return S_OK;
}