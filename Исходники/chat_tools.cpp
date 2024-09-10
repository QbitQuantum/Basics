BOOL LogToFile(SESSION_INFO *si, GCEVENT *gce)
{
	TCHAR szBuffer[4096];
	TCHAR szLine[4096];
	TCHAR p = '\0';
	szBuffer[0] = '\0';

	GetChatLogsFilename(si, gce->time);
	BOOL bFileJustCreated = !PathFileExists(si->pszLogFileName);

	TCHAR tszFolder[MAX_PATH];
	_tcsncpy_s(tszFolder, si->pszLogFileName, _TRUNCATE);
	PathRemoveFileSpec(tszFolder);
	if (!PathIsDirectory(tszFolder))
		CreateDirectoryTreeT(tszFolder);

	TCHAR szTime[100];
	mir_tstrncpy(szTime, chatApi.MakeTimeStamp(g_Settings->pszTimeStampLog, gce->time), 99);

	FILE *hFile = _tfopen(si->pszLogFileName, _T("ab+"));
	if (hFile == NULL)
		return FALSE;

	TCHAR szTemp[512], szTemp2[512];
	TCHAR* pszNick = NULL;
	if (bFileJustCreated)
		fputws((const wchar_t*)"\377\376", hFile);		//UTF-16 LE BOM == FF FE
	if (gce->ptszNick) {
		if (g_Settings->bLogLimitNames && mir_tstrlen(gce->ptszNick) > 20) {
			mir_tstrncpy(szTemp2, gce->ptszNick, 20);
			mir_tstrncpy(szTemp2 + 20, _T("..."), 4);
		}
		else mir_tstrncpy(szTemp2, gce->ptszNick, 511);

		if (gce->ptszUserInfo)
			mir_sntprintf(szTemp, _T("%s (%s)"), szTemp2, gce->ptszUserInfo);
		else
			_tcsncpy_s(szTemp, szTemp2, _TRUNCATE);
		pszNick = szTemp;
	}

	switch (gce->pDest->iType) {
	case GC_EVENT_MESSAGE:
	case GC_EVENT_MESSAGE | GC_EVENT_HIGHLIGHT:
		p = '*';
		mir_sntprintf(szBuffer, _T("%s: %s"), gce->ptszNick, chatApi.RemoveFormatting(gce->ptszText));
		break;
	case GC_EVENT_ACTION:
	case GC_EVENT_ACTION | GC_EVENT_HIGHLIGHT:
		p = '*';
		mir_sntprintf(szBuffer, _T("%s %s"), gce->ptszNick, chatApi.RemoveFormatting(gce->ptszText));
		break;
	case GC_EVENT_JOIN:
		p = '>';
		mir_sntprintf(szBuffer, TranslateT("%s has joined"), pszNick);
		break;
	case GC_EVENT_PART:
		p = '<';
		if (!gce->ptszText)
			mir_sntprintf(szBuffer, TranslateT("%s has left"), pszNick);
		else
			mir_sntprintf(szBuffer, TranslateT("%s has left (%s)"), pszNick, chatApi.RemoveFormatting(gce->ptszText));
		break;
	case GC_EVENT_QUIT:
		p = '<';
		if (!gce->ptszText)
			mir_sntprintf(szBuffer, TranslateT("%s has disconnected"), pszNick);
		else
			mir_sntprintf(szBuffer, TranslateT("%s has disconnected (%s)"), pszNick, chatApi.RemoveFormatting(gce->ptszText));
		break;
	case GC_EVENT_NICK:
		p = '^';
		mir_sntprintf(szBuffer, TranslateT("%s is now known as %s"), gce->ptszNick, gce->ptszText);
		break;
	case GC_EVENT_KICK:
		p = '~';
		if (!gce->ptszText)
			mir_sntprintf(szBuffer, TranslateT("%s kicked %s"), gce->ptszStatus, gce->ptszNick);
		else
			mir_sntprintf(szBuffer, TranslateT("%s kicked %s (%s)"), gce->ptszStatus, gce->ptszNick, chatApi.RemoveFormatting(gce->ptszText));
		break;
	case GC_EVENT_NOTICE:
		p = 'o';
		mir_sntprintf(szBuffer, TranslateT("Notice from %s: %s"), gce->ptszNick, chatApi.RemoveFormatting(gce->ptszText));
		break;
	case GC_EVENT_TOPIC:
		p = '#';
		if (!gce->ptszNick)
			mir_sntprintf(szBuffer, TranslateT("The topic is '%s'"), chatApi.RemoveFormatting(gce->ptszText));
		else
			mir_sntprintf(szBuffer, TranslateT("The topic is '%s' (set by %s)"), chatApi.RemoveFormatting(gce->ptszText), gce->ptszNick);
		break;
	case GC_EVENT_INFORMATION:
		p = '!';
		_tcsncpy_s(szBuffer, chatApi.RemoveFormatting(gce->ptszText), _TRUNCATE);
		break;
	case GC_EVENT_ADDSTATUS:
		p = '+';
		mir_sntprintf(szBuffer, TranslateT("%s enables '%s' status for %s"), gce->ptszText, gce->ptszStatus, gce->ptszNick);
		break;
	case GC_EVENT_REMOVESTATUS:
		p = '-';
		mir_sntprintf(szBuffer, TranslateT("%s disables '%s' status for %s"), gce->ptszText, gce->ptszStatus, gce->ptszNick);
		break;
	}

	// formatting strings don't need to be translatable - changing them via language pack would
	// only screw up the log format.
	if (p)
		mir_sntprintf(szLine, _T("%s %c %s\r\n"), szTime, p, szBuffer);
	else
		mir_sntprintf(szLine, _T("%s %s\r\n"), szTime, szBuffer);

	if (szLine[0]) {
		_fputts(szLine, hFile);

		if (g_Settings->LoggingLimit > 0) {
			fseek(hFile, 0, SEEK_END);
			long dwSize = ftell(hFile);
			rewind(hFile);

			long trimlimit = g_Settings->LoggingLimit * 1024;
			if (dwSize > trimlimit) {
				time_t now = time(0);

				TCHAR tszTimestamp[20];
				_tcsftime(tszTimestamp, 20, _T("%Y%m%d-%H%M%S"), _localtime32((__time32_t *)&now));
				tszTimestamp[19] = 0;

				// max size reached, rotate the log
				// move old logs to /archived sub folder just inside the log root folder.
				// add a time stamp to the file name.
				TCHAR tszDrive[_MAX_DRIVE], tszDir[_MAX_DIR], tszName[_MAX_FNAME], tszExt[_MAX_EXT];
				_tsplitpath(si->pszLogFileName, tszDrive, tszDir, tszName, tszExt);

				TCHAR tszNewPath[_MAX_DRIVE + _MAX_DIR + _MAX_FNAME + _MAX_EXT + 20];
				mir_sntprintf(tszNewPath, _T("%s%sarchived\\"), tszDrive, tszDir);
				CreateDirectoryTreeT(tszNewPath);

				TCHAR tszNewName[_MAX_DRIVE + _MAX_DIR + _MAX_FNAME + _MAX_EXT + 20];
				mir_sntprintf(tszNewName, _T("%s%s-%s%s"), tszNewPath, tszName, tszTimestamp, tszExt);
				fclose(hFile);
				hFile = 0;
				if (!PathFileExists(tszNewName))
					CopyFile(si->pszLogFileName, tszNewName, TRUE);
				DeleteFile(si->pszLogFileName);
			}
		}
	}

	if (hFile)
		fclose(hFile);
	return TRUE;
}