BOOL CDlgExportHistory::ExportHistory(LPCSTR pszFile, fs::list <fsDLHistoryRecord*> &vpHist, BOOL bAppend)
{
	HANDLE hFile = CreateFile (pszFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	CString str;

	if (bAppend && GetLastError () == ERROR_ALREADY_EXISTS)
	{
		

		

		DWORD  dwSize = GetFileSize (hFile, NULL);
		if (dwSize > 10000)
		{
			SetFilePointer (hFile, dwSize - 10000, NULL, FILE_BEGIN);
			dwSize = 10000;
		}

		DWORD dw;
		LPSTR psz = new char [dwSize+1];
		ReadFile (hFile, psz, dwSize, &dw, NULL);
		psz [dwSize] = 0;

		int nLen = lstrlen (psz);

		if (nLen != (int) dwSize)
		{
			
			CloseHandle (hFile);
			return FALSE;
		}

		
		LPSTR psz2 = psz + nLen - 7;
		while (psz2 != psz)
		{
			if (_memicmp (psz2, "</body>", 7) == 0)
			{
				*psz2 = 0;
				break;
			}

			*psz2--;
		}

		if (psz2 == psz)
		{
			
			CloseHandle (hFile);
			return FALSE;
		}

		

		SetFilePointer (hFile, (psz2 - psz) - nLen, NULL, FILE_END);
		SetEndOfFile (hFile);

		delete [] psz;
	}
	else
	{
		

		SetEndOfFile (hFile);
		str = "<html>\n"; 
		str += "<style type=\"text/css\">\n";
		str += "<!--\n";
		str += "H3 { font-size: 19px; font-family: Tahoma; color: #cc0000;}\n";
		str += "TR { font-size: 12px; font-family: Tahoma; color: #000033}\n";
		str += "TD { font-size: 12px; font-family: Tahoma; color: #000033}\n";
		str += "A,A:visited,A:active { text-decoration: none; }\n";
		str += "A:hover { text-decoration: underline; }\n";
		str += "-->\n";
		str += "</style>\n";
		str += "<body>\n";
		str += "<h3>"; str += LS (L_FDMHIST); str += "</h3>\n";
		
	}

	for (int i = 0; i < vpHist.size (); i++)
	{
		fsDLHistoryRecord* rec = vpHist [i];

		str += "<table width=\"75%\" border=\"1\">\n";
		str += "<tr><td width=\"180\">"; str += LS (L_URLOFDOWNLOAD); str += ":</td>"; 
		str += "<td><a href=\""; str += rec->strURL; str += "\"> "; str += rec->strURL; str += "</a></td></tr>\n";

		if (rec->dateDownloaded.dwHighDateTime) {
			str += "<tr><td>"; str += LS (L_DLDEDTOFILE); str += ":</td><td>"; str += rec->strSavedTo; str += "</td></tr>\n";
			str += "<tr><td>"; str += LS (L_SIZEOFFILE); str += ":</td><td>"; str += BytesToString (rec->uFileSize); str += "</td></tr>\n";
			str += "<tr><td>"; str += LS (L_DLDWASCOMPLETED); str += ":</td><td>"; str += TimeToStr (rec->dateDownloaded); str += "</td></tr>\n";
		}
		else {	
			str += "<tr><td>"; str += LS (L_DLDWASDELETED); str += ":</td><td>"; str += TimeToStr (rec->dateRecordAdded); str += "</td></tr>\n";
		}
		
		if (rec->strComment != "")
		{
			CString str2 = rec->strComment; str2.Replace ("\n", "<br>");
			str += "<tr><td>"; str += LS (L_DESC); str += ":</td><td>"; str += str2; str += "</td></tr>\n";
		}

		str += "</table><br>\n";
	}

	
	str += "</body></html>";

	DWORD dw;
	WriteFile (hFile, str, str.GetLength (), &dw, NULL);

	CloseHandle (hFile);

	return TRUE;
}