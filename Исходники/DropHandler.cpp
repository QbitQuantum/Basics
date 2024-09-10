HRESULT CDropHandler::CopyFileDescriptorData(IDataObject *pDataObject,
	list<PastedFile_t> *pPastedFileList)
{
	STGMEDIUM stg;
	HRESULT hr;

	hr = pDataObject->GetData(&m_ftcFileDescriptor,&stg);

	if(hr == S_OK)
	{
		FILEGROUPDESCRIPTOR *pfgd = (FILEGROUPDESCRIPTOR *)GlobalLock(stg.hGlobal);

		if(pfgd != NULL)
		{
			FILETIME *pftCreationTime = NULL;
			FILETIME *pftLastAccessTime = NULL;
			FILETIME *pftLastWriteTime = NULL;
			DWORD dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
			DWORD nBytesToWrite = 0;

			for(unsigned int i = 0;i < pfgd->cItems;i++)
			{
				if(pfgd->fgd[i].dwFlags & FD_ATTRIBUTES)
				{
					dwFileAttributes = pfgd->fgd[i].dwFileAttributes;
				}

				if(pfgd->fgd[i].dwFlags & FD_FILESIZE)
				{
					nBytesToWrite = pfgd->fgd[i].nFileSizeLow;
				}

				if(pfgd->fgd[i].dwFlags & FD_LINKUI)
				{
					/* TODO: Complete. */
				}

				if(pfgd->fgd[i].dwFlags & FD_CREATETIME)
				{
					pftCreationTime = &pfgd->fgd[i].ftCreationTime;
				}

				if(pfgd->fgd[i].dwFlags & FD_ACCESSTIME)
				{
					pftLastAccessTime = &pfgd->fgd[i].ftLastAccessTime;
				}

				if(pfgd->fgd[i].dwFlags & FD_WRITESTIME)
				{
					pftLastWriteTime = &pfgd->fgd[i].ftLastWriteTime;
				}

				/*if(pfgd->fgd[i].dwFlags & FD_UNICODE)
				{
				}*/

				FORMATETC ftcfchg;
				FORMATETC ftcfcis;
				FORMATETC ftcfcstg;
				STGMEDIUM stgFileContents = {0};
				BOOL bDataRetrieved = FALSE;
				LPBYTE pBuffer = NULL;

				SetFORMATETC(&ftcfchg,(CLIPFORMAT)RegisterClipboardFormat(CFSTR_FILECONTENTS),
					NULL,DVASPECT_CONTENT,-1,TYMED_HGLOBAL);
				SetFORMATETC(&ftcfcis,(CLIPFORMAT)RegisterClipboardFormat(CFSTR_FILECONTENTS),
					NULL,DVASPECT_CONTENT,-1,TYMED_ISTREAM);
				SetFORMATETC(&ftcfcstg,(CLIPFORMAT)RegisterClipboardFormat(CFSTR_FILECONTENTS),
					NULL,DVASPECT_CONTENT,-1,TYMED_ISTORAGE);

				if(pDataObject->QueryGetData(&ftcfchg) == S_OK)
				{
					ftcfchg.lindex = i;

					hr = pDataObject->GetData(&ftcfchg,&stgFileContents);

					if(hr == S_OK)
					{
						pBuffer = (LPBYTE)malloc(GlobalSize(stgFileContents.hGlobal) * sizeof(BYTE));

						if(pBuffer != NULL)
						{
							if(!(pfgd->fgd[i].dwFlags & FD_FILESIZE))
								nBytesToWrite = (DWORD)GlobalSize(stgFileContents.hGlobal);

							LPBYTE pTemp = (LPBYTE)GlobalLock(stgFileContents.hGlobal);

							if(pTemp != NULL)
							{
								memcpy(pBuffer,pTemp,GlobalSize(stgFileContents.hGlobal));

								GlobalUnlock(stgFileContents.hGlobal);

								bDataRetrieved = TRUE;
							}

							ReleaseStgMedium(&stgFileContents);
						}
					}
				}
				else if(pDataObject->QueryGetData(&ftcfcis) == S_OK)
				{
					STATSTG sstg;
					ULONG cbRead;

					ftcfcis.lindex = i;

					hr = pDataObject->GetData(&ftcfcis,&stgFileContents);

					if(hr == S_OK)
					{
						hr = stgFileContents.pstm->Stat(&sstg,STATFLAG_NONAME);

						if(hr == S_OK)
						{
							pBuffer = (LPBYTE)malloc(sstg.cbSize.LowPart * sizeof(BYTE));

							if(pBuffer != NULL)
							{
								/* If the file size isn't explicitly given,
								use the size of the stream. */
								if(!(pfgd->fgd[i].dwFlags & FD_FILESIZE))
									nBytesToWrite = sstg.cbSize.LowPart;

								stgFileContents.pstm->Read(pBuffer,sstg.cbSize.LowPart,&cbRead);

								bDataRetrieved = TRUE;
							}
						}

						ReleaseStgMedium(&stgFileContents);
					}
				}
				else if(pDataObject->QueryGetData(&ftcfcstg) == S_OK)
				{
					IStream *pStream;
					STATSTG sstg;
					ULONG cbRead;

					ftcfcstg.lindex = i;

					hr = pDataObject->GetData(&ftcfcstg,&stgFileContents);

					if(hr == S_OK)
					{
						hr = stgFileContents.pstg->Stat(&sstg,STATFLAG_DEFAULT);

						if(hr == S_OK)
						{
							hr = stgFileContents.pstg->OpenStream(sstg.pwcsName,NULL,
								STGM_READ|STGM_SHARE_EXCLUSIVE,0,&pStream);

							if(hr == S_OK)
							{
								CoTaskMemFree(sstg.pwcsName);

								hr = pStream->Stat(&sstg,STATFLAG_NONAME);

								if(hr == S_OK)
								{
									pBuffer = (LPBYTE)malloc(sstg.cbSize.LowPart * sizeof(BYTE));

									if(pBuffer != NULL)
									{
										/* If the file size isn't explicitly given,
										use the size of the stream. */
										if(!(pfgd->fgd[i].dwFlags & FD_FILESIZE))
											nBytesToWrite = sstg.cbSize.LowPart;

										pStream->Read(pBuffer,sstg.cbSize.LowPart,&cbRead);

										bDataRetrieved = TRUE;
									}
								}
							}
						}

						ReleaseStgMedium(&stgFileContents);
					}
				}

				if(bDataRetrieved)
				{
					TCHAR szFullFileName[MAX_PATH];

					StringCchCopy(szFullFileName,SIZEOF_ARRAY(szFullFileName),m_szDestDirectory);
					PathAppend(szFullFileName,pfgd->fgd[i].cFileName);

					HANDLE hFile = CreateFile(szFullFileName,GENERIC_WRITE,0,NULL,
						CREATE_ALWAYS,dwFileAttributes,NULL);

					if(hFile != INVALID_HANDLE_VALUE)
					{
						PastedFile_t pf;
						DWORD nBytesWritten;

						SetFileTime(hFile,pftCreationTime,pftLastAccessTime,pftLastWriteTime);

						WriteFile(hFile,pBuffer,nBytesToWrite,&nBytesWritten,NULL);

						CloseHandle(hFile);

						StringCchCopy(pf.szFileName,SIZEOF_ARRAY(pf.szFileName),szFullFileName);
						PathStripPath(pf.szFileName);

						pPastedFileList->push_back(pf);
					}

					HGLOBAL hglb = NULL;
					DWORD *pdwCopyEffect = NULL;
					FORMATETC ftc;
					STGMEDIUM stg1;

					ftc.cfFormat	= (CLIPFORMAT)RegisterClipboardFormat(CFSTR_PERFORMEDDROPEFFECT);
					ftc.ptd			= NULL;
					ftc.dwAspect	= DVASPECT_CONTENT;
					ftc.lindex		= -1;
					ftc.tymed		= TYMED_HGLOBAL;

					hglb = GlobalAlloc(GMEM_MOVEABLE,sizeof(DWORD));

					pdwCopyEffect = (DWORD *)GlobalLock(hglb);

					*pdwCopyEffect = DROPEFFECT_COPY;

					GlobalUnlock(hglb);

					stg1.tymed			= TYMED_HGLOBAL;
					stg1.pUnkForRelease	= 0;
					stg1.hGlobal		= hglb;

					pDataObject->SetData(&ftc,&stg1,FALSE);
				}

				if(pBuffer != NULL)
				{
					free(pBuffer);
				}
			}

			GlobalUnlock(stg.hGlobal);
		}

		ReleaseStgMedium(&stg);
	}

	return hr;
}