UINT _DownloadThread(LPVOID p)
{
    bRunning = true;
    CFginstDlg *pDlg = (CFginstDlg*)p;
    CString csLink, csHost, csObj, csFile, csName;
    unsigned short nPort = 80;
    DWORD service;
    int urlType = -1;
    csLink = GetLink(nTodayDay);
    urlType = GetURLType(csLink);
    if (urlType == -1) {
        pDlg->SetTimer(4, 100, NULL);
        bRunning = false;
        return 3;
    }

// 	csObj = csHost.Mid(csHost.Find('/'));
// 	csHost = csHost.Left(csHost.Find('/'));
//
// 	if (csHost.Find(':') != -1){
// 		nPort = atoi(csHost.Mid(csHost.Find(':') + 1));
// 		csHost = csHost.Left(csHost.Find(':'));
// 	}
//
// 	csName = csObj.Mid(csObj.Find('/') + 1);

    if (!AfxParseURL(csLink, service, csHost, csObj, nPort)) {
        pDlg->SetTimer(4, 100, NULL);
        bRunning = false;
        return 2;
    }
    csName = csObj.Mid(csObj.ReverseFind('/') + 1);

//	char sCurPath[MAX_PATH];
//	GetCurrentDirectory(MAX_PATH, sCurPath);
//	if(sCurPath[strlen(sCurPath) - 1] != '\\'){
//		strcat(sCurPath, "\\");
//	}
    TCHAR szPath[MAX_PATH];
    if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, 0, szPath)))
    {
        if(szPath[strlen(szPath) - 1] != '\\') {
            strcat(szPath, "\\");
        }
    } else {
        strcpy(szPath, "c:\\");
    }

    sprintf(sFilePath, "%s%s%s%s%d.exe", szPath, option.filename_base, FILE_NAME_MID, option.filename_group, nTodayDay);


    CString csNewURL, csCookie;
    if (urlType == URL_TYPE_WIKIFORTIO) {
        if(!DownloadUrl_wiki(csHost, nPort, csObj, csName, csNewURL, csCookie)) {
            pDlg->SetTimer(4, 100, NULL);
            bRunning = false;
            return 1;
        }
    } else if(urlType == URL_TYPE_LIVE) {
        if(!DownloadUrl_live(csHost, nPort, csObj, csName, csNewURL)) {
            pDlg->SetTimer(4, 100, NULL);
            bRunning = false;
            return 1;
        } else {
            csCookie == "";
        }
    }

    if (!AfxParseURL(csNewURL, service, csHost, csObj, nPort)) {
        pDlg->SetTimer(4, 100, NULL);
        bRunning = false;
        return 2;
    }


    if(csCookie != "") {
        csCookie += "\r\n";
    }


    unsigned long fsize = 0;  //we should know the size
    BOOL re = MDownloadUrl(csHost, nPort, csObj, fsize,  sFilePath, 5, csCookie);
    if(re) {
        pDlg->SetTimer(3, 100, NULL);
    } else {
        pDlg->SetTimer(4, 100, NULL);
    }
    Sleep(400);
    pDlg->KillTimer(2);
    bRunning = false;
    return 0;
}