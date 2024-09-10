/*--------------------------------------------------------------------------*/
httpdownloadfile_error_code httpDownloadFile(char * szURL,char * szSaveFilePath)
{
	if (isValidURL(szURL))
	{
		HINTERNET hiConnex = NULL;
		/* * / * : /*rfc 2616 protocole http.  all files type accepted*/
		char szHeader[]="Accept: */*\r\n\r\n"; 
		HINTERNET hiDownload;

		hiConnex = dynlib_InternetOpen("Scilab_Download", OPENURL_MODE,NULL,NULL,0);
		if(hiConnex == NULL) return HTTP_DOWNLOAD_ERROR_INTERNET_OPEN;

        hiDownload = dynlib_InternetOpenUrl(hiConnex,szURL,szHeader,lstrlen(szHeader),INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD | INTERNET_FLAG_PRAGMA_NOCACHE,0);
		if(!hiDownload)
		{
			dynlib_InternetCloseHandle(hiConnex);
			return HTTP_DOWNLOAD_ERROR_OPEN_URL;
		}
		else
		{
			HANDLE haFile;

			haFile = CreateFile(szSaveFilePath,GENERIC_WRITE,FILE_SHARE_WRITE,0,CREATE_ALWAYS,0,0);
			if(haFile == INVALID_HANDLE_VALUE)
			{
				dynlib_InternetCloseHandle(hiConnex);
				return HTTP_DOWNLOAD_ERROR_CREATEFILE;
			}
			else
			{
				char *szBuff = NULL;

				DWORD dwBytesRequired = 0;
				DWORD dwSizeOfByReq = 4;
				DWORD dwBytesRead = 0;
				DWORD dwBytesWritten = 0;

				/* Get file size */
				if(!dynlib_HttpQueryInfo(hiDownload,HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER,(LPVOID)&dwBytesRequired,&dwSizeOfByReq,0))
				{
					dynlib_InternetCloseHandle(hiConnex);
					return HTTP_DOWNLOAD_ERROR_INVALID_FILE_SIZE;
				}
				else
				{
					if(dwBytesRequired > MO)
					{
						szBuff = (char*)MALLOC(MO);
						if(szBuff == NULL)
						{
							CloseHandle(haFile);
							dynlib_InternetCloseHandle(hiConnex);
							return HTTP_DOWNLOAD_OUTOFMEMORY;
						}
					}
					else
					{
						szBuff = (char*)MALLOC(dwBytesRequired);
						if(szBuff == NULL)
						{
							CloseHandle(haFile);
							dynlib_InternetCloseHandle(hiConnex);
							return HTTP_DOWNLOAD_OUTOFMEMORY;
						}
					}

					while(dwBytesRequired > 0)
					{
						/* we read 1Mo from file. */
						if(dwBytesRequired >= MO)
						{
							if(!dynlib_InternetReadFile(hiDownload,szBuff,MO,&dwBytesRead) || dwBytesRead != MO)
							{
								CloseHandle(haFile);
								dynlib_InternetCloseHandle(hiConnex);
								FREE(szBuff);
								return HTTP_DOWNLOAD_ERROR_INTERNET_READFILE;
							}
							dwBytesRequired -= MO;


							/* we write buffer */
							if(!WriteFile(haFile,szBuff,MO,&dwBytesWritten,NULL) || dwBytesWritten != MO)
							{
								CloseHandle(haFile);
								dynlib_InternetCloseHandle(hiConnex);
								FREE(szBuff);
								return HTTP_DOWNLOAD_ERROR_WRITEFILE;
							}
						}
						else
						{
							if(!dynlib_InternetReadFile(hiDownload,szBuff,dwBytesRequired,&dwBytesRead) || dwBytesRead != dwBytesRequired)
							{
								CloseHandle(haFile);
								dynlib_InternetCloseHandle(hiConnex);
								FREE(szBuff);
								return HTTP_DOWNLOAD_ERROR_INTERNET_READFILE;
							}

							/* we write buffer in a backup file*/
							if(!WriteFile(haFile,szBuff,dwBytesRequired,&dwBytesWritten,NULL) || dwBytesWritten != dwBytesRequired)
							{
								CloseHandle(haFile);
								dynlib_InternetCloseHandle(hiConnex);
								FREE(szBuff);
								return HTTP_DOWNLOAD_ERROR_WRITEFILE;
							}

							dwBytesRequired = 0;
						}
					}

					dynlib_InternetCloseHandle(hiConnex);
					CloseHandle(haFile);
					FREE(szBuff);
					return HTTP_DOWNLOAD_ERROR_OK;
				}
			}
		}
	}
	else return HTTP_DOWNLOAD_ERROR_INVALID_URL;
}