void CPPgSecurity::OnLoadIPFFromURL()
{
	bool bHaveNewFilterFile = false;
	CString url;
	GetDlgItemText(IDC_UPDATEURL,url);
	//Xman auto update IPFilter
	SYSTEMTIME SysTime;
	memset(&SysTime, 0, sizeof(SYSTEMTIME)); //just to avoid the warning
	//Xman end
	if (!url.IsEmpty())
	{
		// add entered URL to LRU list even if it's not yet known whether we can download from this URL (it's just more convenient this way)
		if (m_pacIPFilterURL && m_pacIPFilterURL->IsBound())
			m_pacIPFilterURL->AddItem(url, 0);

		// ==> Advanced Updates [MorphXT/Stulle] - Stulle
		if(thePrefs.IsIPFilterViaDynDNS(url))
		{
			theApp.emuledlg->CheckIPFilter();
			return;
		}
		// <== Advanced Updates [MorphXT/Stulle] - Stulle

		CString strTempFilePath;
		_tmakepathlimit(strTempFilePath.GetBuffer(MAX_PATH), NULL, thePrefs.GetMuleDirectory(EMULE_CONFIGDIR), DFLT_IPFILTER_FILENAME, _T("tmp"));
		strTempFilePath.ReleaseBuffer();

		CHttpDownloadDlg dlgDownload;
		dlgDownload.m_strTitle = GetResString(IDS_DWL_IPFILTERFILE);
		dlgDownload.m_sURLToDownload = url;
		dlgDownload.m_sFileToDownloadInto = strTempFilePath;
		
		//Xman auto update IPFilter
		memset(&SysTime, 0, sizeof(SYSTEMTIME));
		dlgDownload.m_pLastModifiedTime = &SysTime; //Xman remark: m_pLastModifiedTime is a pointer which points to the SysTime-struct
		//Xman end

		if (dlgDownload.DoModal() != IDOK)
		{
			(void)_tremove(strTempFilePath);
			CString strError = GetResString(IDS_DWLIPFILTERFAILED);
			if (!dlgDownload.GetError().IsEmpty())
				strError += _T("\r\n\r\n") + dlgDownload.GetError();
			AfxMessageBox(strError, MB_ICONERROR);
			return;
		}

		CString strMimeType;
		GetMimeType(strTempFilePath, strMimeType);

		bool bIsArchiveFile = false;
		bool bUncompressed = false;
		CZIPFile zip;
		if (zip.Open(strTempFilePath))
		{
			bIsArchiveFile = true;

			CZIPFile::File* zfile = zip.GetFile(_T("ipfilter.dat"));
			if (zfile == NULL)
				zfile = zip.GetFile(_T("guarding.p2p"));
			if (zfile == NULL)
				zfile = zip.GetFile(_T("guardian.p2p"));
			if (zfile)
			{
				CString strTempUnzipFilePath;
				_tmakepathlimit(strTempUnzipFilePath.GetBuffer(_MAX_PATH), NULL, thePrefs.GetMuleDirectory(EMULE_CONFIGDIR), DFLT_IPFILTER_FILENAME, _T(".unzip.tmp"));
				strTempUnzipFilePath.ReleaseBuffer();

				if (zfile->Extract(strTempUnzipFilePath))
				{
					zip.Close();
					zfile = NULL;

					if (_tremove(theApp.ipfilter->GetDefaultFilePath()) != 0)
						TRACE(_T("*** Error: Failed to remove default IP filter file \"%s\" - %s\n"), theApp.ipfilter->GetDefaultFilePath(), _tcserror(errno));
					if (_trename(strTempUnzipFilePath, theApp.ipfilter->GetDefaultFilePath()) != 0)
						TRACE(_T("*** Error: Failed to rename uncompressed IP filter file \"%s\" to default IP filter file \"%s\" - %s\n"), strTempUnzipFilePath, theApp.ipfilter->GetDefaultFilePath(), _tcserror(errno));
					if (_tremove(strTempFilePath) != 0)
						TRACE(_T("*** Error: Failed to remove temporary IP filter file \"%s\" - %s\n"), strTempFilePath, _tcserror(errno));
					bUncompressed = true;
					bHaveNewFilterFile = true;
				}
				else {
					CString strError;
					strError.Format(GetResString(IDS_ERR_IPFILTERZIPEXTR), strTempFilePath);
					AfxMessageBox(strError, MB_ICONERROR);
				}
			}
			else {
				CString strError;
				strError.Format(GetResString(IDS_ERR_IPFILTERCONTENTERR), strTempFilePath);
				AfxMessageBox(strError, MB_ICONERROR);
			}

			zip.Close();
		}
		else if (strMimeType.CompareNoCase(_T("application/x-rar-compressed")) == 0)
		{
			bIsArchiveFile = true;

			CRARFile rar;
			if (rar.Open(strTempFilePath))
			{
				CString strFile;
				if (rar.GetNextFile(strFile)
					&& (   strFile.CompareNoCase(_T("ipfilter.dat")) == 0 
					    || strFile.CompareNoCase(_T("guarding.p2p")) == 0
						|| strFile.CompareNoCase(_T("guardian.p2p")) == 0))
				{
					CString strTempUnzipFilePath;
					_tmakepathlimit(strTempUnzipFilePath.GetBuffer(MAX_PATH), NULL, thePrefs.GetMuleDirectory(EMULE_CONFIGDIR), DFLT_IPFILTER_FILENAME, _T(".unzip.tmp"));
					strTempUnzipFilePath.ReleaseBuffer();
					if (rar.Extract(strTempUnzipFilePath))
					{
						rar.Close();

						if (_tremove(theApp.ipfilter->GetDefaultFilePath()) != 0)
							TRACE(_T("*** Error: Failed to remove default IP filter file \"%s\" - %s\n"), theApp.ipfilter->GetDefaultFilePath(), _tcserror(errno));
						if (_trename(strTempUnzipFilePath, theApp.ipfilter->GetDefaultFilePath()) != 0)
							TRACE(_T("*** Error: Failed to rename uncompressed IP filter file \"%s\" to default IP filter file \"%s\" - %s\n"), strTempUnzipFilePath, theApp.ipfilter->GetDefaultFilePath(), _tcserror(errno));
						if (_tremove(strTempFilePath) != 0)
							TRACE(_T("*** Error: Failed to remove temporary IP filter file \"%s\" - %s\n"), strTempFilePath, _tcserror(errno));
						bUncompressed = true;
						bHaveNewFilterFile = true;
					}
					else
					{
						CString strError;
						strError.Format(_T("Failed to extract IP filter file from RAR file \"%s\"."), strTempFilePath);
						AfxMessageBox(strError, MB_ICONERROR);
					}
				}
				else
				{
					CString strError;
					strError.Format(_T("Failed to find IP filter file \"guarding.p2p\" or \"ipfilter.dat\" in RAR file \"%s\"."), strTempFilePath);
					AfxMessageBox(strError, MB_ICONERROR);
				}
				rar.Close();
			}
			else
			{
				CString strError;
				strError.Format(_T("Failed to open file \"%s\".\r\n\r\nInvalid file format?\r\n\r\nDownload latest version of UNRAR.DLL from http://www.rarlab.com and copy UNRAR.DLL into eMule installation folder."), url);
				AfxMessageBox(strError, MB_ICONERROR);
			}
		}
		else
		{
			CGZIPFile gz;
			if (gz.Open(strTempFilePath))
			{
				bIsArchiveFile = true;

				CString strTempUnzipFilePath;
				_tmakepathlimit(strTempUnzipFilePath.GetBuffer(_MAX_PATH), NULL, thePrefs.GetMuleDirectory(EMULE_CONFIGDIR), DFLT_IPFILTER_FILENAME, _T(".unzip.tmp"));
				strTempUnzipFilePath.ReleaseBuffer();

				// add filename and extension of uncompressed file to temporary file
				CString strUncompressedFileName = gz.GetUncompressedFileName();
				if (!strUncompressedFileName.IsEmpty())
				{
					strTempUnzipFilePath += _T('.');
					strTempUnzipFilePath += strUncompressedFileName;
				}

				if (gz.Extract(strTempUnzipFilePath))
				{
					gz.Close();

					if (_tremove(theApp.ipfilter->GetDefaultFilePath()) != 0)
						TRACE(_T("*** Error: Failed to remove default IP filter file \"%s\" - %s\n"), theApp.ipfilter->GetDefaultFilePath(), _tcserror(errno));
					if (_trename(strTempUnzipFilePath, theApp.ipfilter->GetDefaultFilePath()) != 0)
						TRACE(_T("*** Error: Failed to rename uncompressed IP filter file \"%s\" to default IP filter file \"%s\" - %s\n"), strTempUnzipFilePath, theApp.ipfilter->GetDefaultFilePath(), _tcserror(errno));
					if (_tremove(strTempFilePath) != 0)
						TRACE(_T("*** Error: Failed to remove temporary IP filter file \"%s\" - %s\n"), strTempFilePath, _tcserror(errno));
					bUncompressed = true;
					bHaveNewFilterFile = true;
				}
				else {
					CString strError;
					strError.Format(GetResString(IDS_ERR_IPFILTERZIPEXTR), strTempFilePath);
					AfxMessageBox(strError, MB_ICONERROR);
				}
			}
			gz.Close();
		}

		if (!bIsArchiveFile && !bUncompressed)
		{
			// Check first lines of downloaded file for potential HTML content (e.g. 404 error pages)
			bool bValidIPFilterFile = true;
			FILE* fp = _tfsopen(strTempFilePath, _T("rb"), _SH_DENYWR);
			if (fp)
			{
				char szBuff[16384];
				int iRead = fread(szBuff, 1, _countof(szBuff)-1, fp);
				if (iRead <= 0)
					bValidIPFilterFile = false;
				else
				{
					szBuff[iRead-1] = '\0';

					const char* pc = szBuff;
					while (*pc == ' ' || *pc == '\t' || *pc == '\r' || *pc == '\n')
						pc++;
					if (_strnicmp(pc, "<html", 5) == 0
						|| _strnicmp(pc, "<xml", 4) == 0
						|| _strnicmp(pc, "<!doc", 5) == 0)
					{
						bValidIPFilterFile = false;
					}
				}
				fclose(fp);
			}

			if (bValidIPFilterFile)
			{
				(void)_tremove(theApp.ipfilter->GetDefaultFilePath());
				VERIFY( _trename(strTempFilePath, theApp.ipfilter->GetDefaultFilePath()) == 0 );
				bHaveNewFilterFile = true;
			}
			else
			{
				AfxMessageBox(GetResString(IDS_DWLIPFILTERFAILED), MB_ICONERROR);
			}
		}
	}

	//Xman auto update IPFilter
	// ==> Advanced Updates [MorphXT/Stulle] - Stulle
	/*
	struct tm tmTemp;
	thePrefs.m_last_ipfilter_check = safe_mktime(CTime::GetCurrentTime().GetLocalTm(&tmTemp));
	*/
	// <== Advanced Updates [MorphXT/Stulle] - Stulle
	//Xman end

	if (url.IsEmpty() || bHaveNewFilterFile)
		OnReloadIPFilter();

	// In case we received an invalid IP-filter file (e.g. an 404 HTML page with HTTP status "OK"),
	// warn the user that there are no IP-filters available any longer.
	if (bHaveNewFilterFile && theApp.ipfilter->GetIPFilter().GetCount() == 0)
	{
		CString strLoaded;
		strLoaded.Format(GetResString(IDS_IPFILTERLOADED), theApp.ipfilter->GetIPFilter().GetCount());
		CString strError;
		strError.Format(_T("%s\r\n\r\n%s"), GetResString(IDS_DWLIPFILTERFAILED), strLoaded);
		AfxMessageBox(strError, MB_ICONERROR);
	}
	//Xman auto update IPFilter
	else if(bHaveNewFilterFile)
		memcpy(&thePrefs.m_IPfilterVersion, &SysTime, sizeof SysTime); 
	//Xman end
}