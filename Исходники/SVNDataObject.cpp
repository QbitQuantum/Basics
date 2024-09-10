//////////////////////////////////////////////////////////////////////////
// IDataObject
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP SVNDataObject::GetData(FORMATETC* pformatetcIn, STGMEDIUM* pmedium)
{
	if (pformatetcIn == NULL)
		return E_INVALIDARG;
	if (pmedium == NULL)
		return E_POINTER;
	pmedium->hGlobal = NULL;

	if ((pformatetcIn->tymed & TYMED_ISTREAM) && (pformatetcIn->dwAspect == DVASPECT_CONTENT) && (pformatetcIn->cfFormat == CF_FILECONTENTS))
	{
		// supports the IStream format.
		// The lindex param is the index of the file to return

		// Note: we don't get called for directories since those are simply created and don't
		// need to be fetched.

		// Note2: It would be really nice if we could get a stream from the subversion library
		// from where we could read the file contents. But the Subversion lib is not implemented
		// to *read* from a remote stream but so that the library *writes* to a stream we pass.
		// Since we can't get such a read stream, we have to fetch the file in whole first to
		// a temp location and then pass the shell an IStream for that temp file.
		CTSVNPath filepath;
		IStream * pIStream = NULL;
		if (m_revision.IsWorking())
		{
			if ((pformatetcIn->lindex >= 0)&&(pformatetcIn->lindex < (LONG)m_allPaths.size()))
			{
				filepath = m_allPaths[pformatetcIn->lindex].rootpath;
			}
		}
		else
		{
			filepath = CTempFiles::Instance().GetTempFilePath(true);
			if ((pformatetcIn->lindex >= 0)&&(pformatetcIn->lindex < (LONG)m_allPaths.size()))
			{
				if (!m_svn.Cat(CTSVNPath(m_allPaths[pformatetcIn->lindex].infodata.url), m_pegRev, m_revision, filepath))
				{
					DeleteFile(filepath.GetWinPath());
					return STG_E_ACCESSDENIED;
				}
			}
		}
		HRESULT res = SHCreateStreamOnFile(filepath.GetWinPath(), STGM_READ, &pIStream);
		if (res == S_OK)
		{
			pmedium->pstm = pIStream;
			pmedium->tymed = TYMED_ISTREAM;
			return S_OK;
		}
		return res;
	}
	else if ((pformatetcIn->tymed & TYMED_HGLOBAL) && (pformatetcIn->dwAspect == DVASPECT_CONTENT) && (pformatetcIn->cfFormat == CF_FILEDESCRIPTOR))
	{
		// now it is time to get all sub folders for the directories we have
		SVNInfo svnInfo;
		// find the common directory of all the paths
		CTSVNPath commonDir;
		bool bAllUrls = true;
		for (int i=0; i<m_svnPaths.GetCount(); ++i)
		{
			if (!m_svnPaths[i].IsUrl())
				bAllUrls = false;
			if (commonDir.IsEmpty())
				commonDir = m_svnPaths[i].GetContainingDirectory();
			if (!commonDir.IsEquivalentTo(m_svnPaths[i].GetContainingDirectory()))
			{
				commonDir.Reset();
				break;
			}
		}
		if (bAllUrls && (m_svnPaths.GetCount() > 1) && !commonDir.IsEmpty())
		{
			// if all paths are in the same directory, we can fetch the info recursively
			// from the parent folder to save a lot of time.
			const SVNInfoData * infodata = svnInfo.GetFirstFileInfo(commonDir, m_pegRev, m_revision, svn_depth_infinity);
			while (infodata)
			{
				// check if the returned item is one in our list
				for (int i=0; i<m_svnPaths.GetCount(); ++i)
				{
					if (m_svnPaths[i].IsAncestorOf(CTSVNPath(infodata->url)))
					{
						SVNDataObject::SVNObjectInfoData id = {m_svnPaths[i], *infodata};
						m_allPaths.push_back(id);
						break;
					}
				}
				infodata = svnInfo.GetNextFileInfo();
			}
		}
		else
		{
			for (int i = 0; i < m_svnPaths.GetCount(); ++i)
			{
				if (m_svnPaths[i].IsUrl())
				{
					const SVNInfoData * infodata = svnInfo.GetFirstFileInfo(m_svnPaths[i], m_pegRev, m_revision, svn_depth_infinity);
					while (infodata)
					{
						SVNDataObject::SVNObjectInfoData id = {m_svnPaths[i], *infodata};
						m_allPaths.push_back(id);
						infodata = svnInfo.GetNextFileInfo();
					}
				}
				else
				{
					SVNDataObject::SVNObjectInfoData id = {m_svnPaths[i], SVNInfoData()};
					m_allPaths.push_back(id);
				}
			}
		}
		size_t dataSize = sizeof(FILEGROUPDESCRIPTOR) + ((m_allPaths.size() - 1) * sizeof(FILEDESCRIPTOR));
		HGLOBAL data = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, dataSize);

		FILEGROUPDESCRIPTOR* files = (FILEGROUPDESCRIPTOR*)GlobalLock(data);
		files->cItems = static_cast<UINT>(m_allPaths.size());
		int index = 0;
		for (vector<SVNDataObject::SVNObjectInfoData>::const_iterator it = m_allPaths.begin(); it != m_allPaths.end(); ++it)
		{
			CString temp;
			if (it->rootpath.IsUrl())
			{
				temp = CUnicodeUtils::GetUnicode(CPathUtils::PathEscape(CUnicodeUtils::GetUTF8(it->rootpath.GetContainingDirectory().GetSVNPathString())));
				temp = it->infodata.url.Mid(temp.GetLength()+1);
				// we have to unescape the urls since the local file system doesn't need them
				// escaped and it would only look really ugly (and be wrong).
				temp = CPathUtils::PathUnescape(temp);
			}
			else
			{
				temp = it->rootpath.GetUIFileOrDirectoryName();
			}
			_tcscpy_s(files->fgd[index].cFileName, MAX_PATH, (LPCTSTR)temp);
			files->fgd[index].dwFlags = FD_ATTRIBUTES | FD_PROGRESSUI | FD_FILESIZE | FD_LINKUI;
			if (it->rootpath.IsUrl())
			{
				files->fgd[index].dwFileAttributes = (it->infodata.kind == svn_node_dir) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
			}
			else
			{
				files->fgd[index].dwFileAttributes = it->rootpath.IsDirectory() ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
			}
			// Always set the file size to 0 even if we 'know' the file size (infodata.size64).
			// Because for text files, the file size is too low due to the EOLs getting converted
			// to CRLF (from LF as stored in the repository). And a too low file size set here
			// prevents the shell from reading the full file later - it only reads the stream up
			// to the number of bytes specified here. Which means we would end up with a truncated
			// text file (binary files are still ok though).
			files->fgd[index].nFileSizeLow = 0;
			files->fgd[index].nFileSizeHigh = 0;

			++index;
		}

		GlobalUnlock(data);

		pmedium->hGlobal = data;
		pmedium->tymed = TYMED_HGLOBAL;
		return S_OK;
	}
	// handling CF_PREFERREDDROPEFFECT is necessary to tell the shell that it should *not* ask for the
	// CF_FILEDESCRIPTOR until the drop actually occurs. If we don't handle CF_PREFERREDDROPEFFECT, the shell
	// will ask for the file descriptor for every object (file/folder) the mouse pointer hovers over and is
	// a potential drop target.
	else if ((pformatetcIn->tymed & TYMED_HGLOBAL) && (pformatetcIn->cfFormat == CF_PREFERREDDROPEFFECT))
	{
		HGLOBAL data = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, sizeof(DWORD));
		DWORD* effect = (DWORD*) GlobalLock(data);
		(*effect) = DROPEFFECT_COPY;
		GlobalUnlock(data);
		pmedium->hGlobal = data;
		pmedium->tymed = TYMED_HGLOBAL;
		return S_OK;
	}
	else if ((pformatetcIn->tymed & TYMED_HGLOBAL) && (pformatetcIn->dwAspect == DVASPECT_CONTENT) && (pformatetcIn->cfFormat == CF_TEXT))
	{
		// caller wants text
		// create the string from the path list
		CString text;
		if (m_svnPaths.GetCount())
		{
			// create a single string where the URLs are separated by newlines
			for (int i=0; i<m_svnPaths.GetCount(); ++i)
			{
				if (m_svnPaths[i].IsUrl())
					text += m_svnPaths[i].GetSVNPathString();
				else
					text += m_svnPaths[i].GetWinPathString();
				text += _T("\r\n");
			}
		}
		CStringA texta = CUnicodeUtils::GetUTF8(text);
		pmedium->tymed = TYMED_HGLOBAL;
		pmedium->hGlobal = GlobalAlloc(GHND, (texta.GetLength()+1)*sizeof(char));
		if (pmedium->hGlobal)
		{
			char* pMem = (char*)GlobalLock(pmedium->hGlobal);
			strcpy_s(pMem, texta.GetLength()+1, (LPCSTR)texta);
			GlobalUnlock(pmedium->hGlobal);
		}
		pmedium->pUnkForRelease = NULL;
		return S_OK;
	}
	else if ((pformatetcIn->tymed & TYMED_HGLOBAL) && (pformatetcIn->dwAspect == DVASPECT_CONTENT) && (pformatetcIn->cfFormat == CF_UNICODETEXT))
	{
		// caller wants Unicode text
		// create the string from the path list
		CString text;
		if (m_svnPaths.GetCount())
		{
			// create a single string where the URLs are separated by newlines
			for (int i=0; i<m_svnPaths.GetCount(); ++i)
			{
				if (m_svnPaths[i].IsUrl())
					text += m_svnPaths[i].GetSVNPathString();
				else
					text += m_svnPaths[i].GetWinPathString();
				text += _T("\r\n");
			}
		}
		pmedium->tymed = TYMED_HGLOBAL;
		pmedium->hGlobal = GlobalAlloc(GHND, (text.GetLength()+1)*sizeof(TCHAR));
		if (pmedium->hGlobal)
		{
			TCHAR* pMem = (TCHAR*)GlobalLock(pmedium->hGlobal);
			_tcscpy_s(pMem, text.GetLength()+1, (LPCTSTR)text);
			GlobalUnlock(pmedium->hGlobal);
		}
		pmedium->pUnkForRelease = NULL;
		return S_OK;
	}
	else if ((pformatetcIn->tymed & TYMED_HGLOBAL) && (pformatetcIn->dwAspect == DVASPECT_CONTENT) && (pformatetcIn->cfFormat == CF_SVNURL))
	{
		// caller wants the svn url
		// create the string from the path list
		CString text;
		if (m_svnPaths.GetCount())
		{
			// create a single string where the URLs are separated by newlines
			for (int i=0; i<m_svnPaths.GetCount(); ++i)
			{
				if (m_svnPaths[i].IsUrl())
				{
					text += m_svnPaths[i].GetSVNPathString();
					text += _T("?");
					text += m_revision.ToString();
				}
				else
					text += m_svnPaths[i].GetWinPathString();
				text += _T("\r\n");
			}
		}
		pmedium->tymed = TYMED_HGLOBAL;
		pmedium->hGlobal = GlobalAlloc(GHND, (text.GetLength()+1)*sizeof(TCHAR));
		if (pmedium->hGlobal)
		{
			TCHAR* pMem = (TCHAR*)GlobalLock(pmedium->hGlobal);
			_tcscpy_s(pMem, text.GetLength()+1, (LPCTSTR)text);
			GlobalUnlock(pmedium->hGlobal);
		}
		pmedium->pUnkForRelease = NULL;
		return S_OK;
	}
	else if ((pformatetcIn->tymed & TYMED_HGLOBAL) && (pformatetcIn->dwAspect == DVASPECT_CONTENT) && (pformatetcIn->cfFormat == CF_HDROP))
	{
		int nLength = 0;

		for (int i=0;i<m_svnPaths.GetCount();i++)
		{
			nLength += m_svnPaths[i].GetWinPathString().GetLength();
			nLength += 1; // '\0' separator
		}

		int nBufferSize = sizeof(DROPFILES) + (nLength+1)*sizeof(TCHAR);
		char * pBuffer = new char[nBufferSize];

		SecureZeroMemory(pBuffer, nBufferSize);

		DROPFILES* df = (DROPFILES*)pBuffer;
		df->pFiles = sizeof(DROPFILES);
		df->fWide = 1;

		TCHAR* pFilenames = (TCHAR*)(pBuffer + sizeof(DROPFILES));
		TCHAR* pCurrentFilename = pFilenames;

		for (int i=0;i<m_svnPaths.GetCount();i++)
		{
			CString str = m_svnPaths[i].GetWinPathString();
			wcscpy_s(pCurrentFilename, str.GetLength()+1, (LPCWSTR)str);
			pCurrentFilename += str.GetLength();
			*pCurrentFilename = '\0'; // separator between file names
			pCurrentFilename++;
		}
		*pCurrentFilename = '\0'; // terminate array

		pmedium->tymed = TYMED_HGLOBAL;
		pmedium->hGlobal = GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE, nBufferSize);
		if (pmedium->hGlobal)
		{
			LPVOID pMem = ::GlobalLock(pmedium->hGlobal);
			if (pMem)
				memcpy(pMem, pBuffer, nBufferSize);
			GlobalUnlock(pmedium->hGlobal);
		}
		pmedium->pUnkForRelease = NULL;
		delete [] pBuffer;
		return S_OK;
	}

	for (size_t i=0; i<m_vecFormatEtc.size(); ++i)
	{
		if ((pformatetcIn->tymed == m_vecFormatEtc[i]->tymed) &&
			(pformatetcIn->dwAspect == m_vecFormatEtc[i]->dwAspect) &&
			(pformatetcIn->cfFormat == m_vecFormatEtc[i]->cfFormat))
		{
			CopyMedium(pmedium, m_vecStgMedium[i], m_vecFormatEtc[i]);
			return S_OK;
		}
	}

	return DV_E_FORMATETC;
}