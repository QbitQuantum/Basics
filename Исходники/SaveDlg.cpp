HRESULT CSaveTaskDlg::InitFileCopy()
{
	AppSettings& s = AfxGetAppSettings();

	if (OpenImageCheck(m_in) && s.strSnapShotExt != _T(".*")) {
		OpenImageDIB(m_in, m_out, s.iThumbQuality, 0);
		return S_OK;
	}

	if (FAILED(pGB.CoCreateInstance(CLSID_FilterGraph)) || !(pMC = pGB) || !(pME = pGB) || !(pMS = pGB)) {
		SetFooterIcon(MAKEINTRESOURCE(IDI_ERROR));
		SetFooterText(ResStr(IDS_AG_ERROR));
		return S_FALSE;
	}

	HRESULT hr;

	CStringW fnw = m_in;
	CComPtr<IFileSourceFilter> pReader;

	if (!pReader && m_in.Mid(m_in.ReverseFind('.')+1).MakeLower() == _T("cda")) {
		hr = S_OK;
		CComPtr<IUnknown> pUnk = (IUnknown*)(INonDelegatingUnknown*)DNew CCDDAReader(NULL, &hr);

		if (FAILED(hr) || !(pReader = pUnk) || FAILED(pReader->Load(fnw, NULL))) {
			pReader.Release();
		}
	}

	if (!pReader) {
		hr = S_OK;
		CComPtr<IUnknown> pUnk = (IUnknown*)(INonDelegatingUnknown*)DNew CCDXAReader(NULL, &hr);

		if (FAILED(hr) || !(pReader = pUnk) || FAILED(pReader->Load(fnw, NULL))) {
			pReader.Release();
		}
	}

	if (!pReader ) {
		hr = S_OK;
		CComPtr<IUnknown> pUnk = (IUnknown*)(INonDelegatingUnknown*)DNew CVTSReader(NULL, &hr);

		if (FAILED(hr) || !(pReader = pUnk) || FAILED(pReader->Load(fnw, NULL))) {
			pReader.Release();
		} else {
			CPath pout(m_out);
			pout.RenameExtension(_T(".ifo"));
			CopyFile(m_in, pout, FALSE);
		}
	}

	if (!pReader) {
		hr = S_OK;
		CComPtr<IUnknown> pUnk;
		pUnk.CoCreateInstance(CLSID_AsyncReader);

		if (!(pReader = pUnk) || FAILED(pReader->Load(fnw, NULL))) {
			pReader.Release();
		}
	}

	if (!pReader) {
		hr = S_OK;
		CComPtr<IUnknown> pUnk;
		pUnk.CoCreateInstance(CLSID_URLReader);

		if (CComQIPtr<IBaseFilter> pSrc = pUnk) {
			pGB->AddFilter(pSrc, fnw);

			if (!(pReader = pUnk) || FAILED(hr = pReader->Load(fnw, NULL))) {
				pReader.Release();
				pGB->RemoveFilter(pSrc);
			}
		}
	}

	CComQIPtr<IBaseFilter> pSrc = pReader;

	if (FAILED(pGB->AddFilter(pSrc, fnw))) {
		SetFooterIcon(MAKEINTRESOURCE(IDI_ERROR));
		SetFooterText(_T("Sorry, can't save this file, press Cancel"));
		return S_FALSE;
	}

	CComQIPtr<IBaseFilter> pMid = DNew CStreamDriveThruFilter(NULL, &hr);

	if (FAILED(pGB->AddFilter(pMid, L"StreamDriveThru"))) {
		SetFooterIcon(MAKEINTRESOURCE(IDI_ERROR));
		SetFooterText(ResStr(IDS_AG_ERROR));

		return S_FALSE;
	}

	CComQIPtr<IBaseFilter> pDst;
	pDst.CoCreateInstance(CLSID_FileWriter);
	CComQIPtr<IFileSinkFilter2> pFSF = pDst;
	pFSF->SetFileName(CStringW(m_out), NULL);
	pFSF->SetMode(AM_FILE_OVERWRITE);

	if (FAILED(pGB->AddFilter(pDst, L"File Writer"))) {
		SetFooterIcon(MAKEINTRESOURCE(IDI_ERROR));
		SetFooterText(ResStr(IDS_AG_ERROR));

		return S_FALSE;
	}

	hr = pGB->Connect(
			 GetFirstPin((pSrc), PINDIR_OUTPUT),
			 GetFirstPin((pMid), PINDIR_INPUT));

	if (FAILED(hr)) {
		SetFooterIcon(MAKEINTRESOURCE(IDI_ERROR));
		SetFooterText(_T("Error Connect pSrc / pMid"));

		return S_FALSE;
	}

	hr = pGB->Connect(
			 GetFirstPin((pMid), PINDIR_OUTPUT),
			 GetFirstPin((pDst), PINDIR_INPUT));
	if (FAILED(hr)) {
		SetFooterIcon(MAKEINTRESOURCE(IDI_ERROR));
		SetFooterText(_T("Error Connect pMid / pDst"));

		return S_FALSE;
	}

	pMS = pMid;

	pMC->Run();

	return S_OK;
}