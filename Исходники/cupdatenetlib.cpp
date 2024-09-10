BOOL cupdatenetlib::downloadList(){
	if ( !(_wmkdir(szUpdfilesPath) < 0 && errno == EEXIST) ){
		SVP_LogMsg( _T("UPD dir not exist and writeable! "));
		return 0;
	}
	resetCounter();

	CString szBranch = svpToolBox.fileGetContent(szUpdfilesPath + _T("branch") );

	if(szBranch.IsEmpty() ){
		/* 如果 mtime 小于 stable 版本的 mtime 就更新 stable ， 大于就更新 beta */
//		struct __stat64  sbuf;
		CString szPlayerPath = svpToolBox.GetPlayerPath(_T("splayer.exe"));
		if(!svpToolBox.ifFileExist(szPlayerPath) ){
			szPlayerPath = svpToolBox.GetPlayerPath(_T("mplayerc.exe"));
			if (!svpToolBox.ifFileExist(szPlayerPath)){
				szPlayerPath = svpToolBox.GetPlayerPath(_T("svplayer.exe"));
			}
		}
		if(svpToolBox.ifFileExist(szPlayerPath) ){
			CMD5Checksum cmd5;
			//szBranch.Format( _T("%I64d") , sbuf.st_mtime );
			szBranch = cmd5.GetMD5((LPCTSTR)szPlayerPath).c_str();
			//AfxMessageBox(szBranch);
		}
		else
			szBranch = _T("stable");
	}

	WCHAR* wsz = this->svpToolBox.getTmpFileName();
    CString szTmpFilename(wsz);
	delete wsz;

    CString szPostPerm;
    szPostPerm.Format(_T("ver=%s&branch=%s"), BRANCHVER, szBranch);

	int rret = 0;
	CString szLog;
	if (PostUsingCurl(szPostPerm, szTmpFilename)){
        rret = 1;
		GetD3X9Dll();
		//iSVPCU_TOTAL_FILE = 0;
		iSVPCU_TOTAL_FILEBYTE  = 0;
		CString szData = svpToolBox.fileGetContent( szTmpFilename ) ;
		CStringArray szaLines;
		svpToolBox.Explode( szData, _T("\n") , &szaLines );
		for(int i = 0; i < szaLines.GetCount(); i++){
			if (szaLines.GetAt(i).IsEmpty()){break;}
			this->iSVPCU_TOTAL_FILE++;
			
			//szLog.Format(_T("Total Files need to download: %d"), iSVPCU_TOTAL_FILE);
			//SVP_LogMsg(szLog);
			CStringArray szaTmp;
			svpToolBox.Explode( szaLines.GetAt(i), _T(";") , &szaTmp );
			if(szaTmp.GetCount() < LFILETOTALPARMS){
				continue;
			}

            if (SkipThisFile(szaTmp.GetAt(LFILESETUPPATH), szaTmp.GetAt(LFILEACTION)))
                continue;

            //检查是否需要下载
			CString szSetupPath = szaTmp.GetAt(LFILESETUPPATH);

			if (szSetupPath.CompareNoCase( _T("splayer.exe")) == 0){
				if(!svpToolBox.ifFileExist(szBasePath + szSetupPath) ){
					if (svpToolBox.ifFileExist(szBasePath + _T("mplayerc.exe")))
						szSetupPath = _T("mplayerc.exe");
					if (svpToolBox.ifFileExist(szBasePath + _T("svplayer.exe")))
						szSetupPath = _T("svplayer.exe");
				}
			}

			bool bDownloadThis = FALSE;

      //check file hash
      CMD5Checksum cmd5;
      CString updTmpHash ;
      CString currentHash ;
      if( svpToolBox.ifFileExist(szUpdfilesPath + szaTmp.GetAt(LFILETMPATH)))
      {
        updTmpHash = cmd5.GetMD5((LPCTSTR)(szUpdfilesPath +
          szaTmp.GetAt(LFILETMPATH))).c_str(); //Get Hash for current Temp File
      }

      if( svpToolBox.ifFileExist(szBasePath + szSetupPath ) ){
        currentHash = cmd5.GetMD5((LPCTSTR)(szBasePath + szSetupPath)).c_str(); //Get Hash for bin file
      }

            if (currentHash.CompareNoCase( szaTmp.GetAt(LFILEHASH) ) == 0 )
                continue;
            if ( updTmpHash.CompareNoCase( szaTmp.GetAt(LFILEHASH) ) != 0 ){
                bDownloadThis = TRUE;
            }

            UpdateInfo* puinfo = new UpdateInfo;
            puinfo->bDownload = bDownloadThis;
            puinfo->dwDowloadedLength = _wtoi(szaTmp.GetAt(LFILEGZLEN));
            puinfo->dwFileLength = _wtoi(szaTmp.GetAt(LFILELEN));
            puinfo->strId = (szaTmp.GetAt(LFILEID));
            puinfo->strAction = szaTmp.GetAt(LFILEACTION);
            puinfo->strDownloadfileMD5 = szaTmp.GetAt(LFILEGZHASH);
            puinfo->strFileMd5 = szaTmp.GetAt(LFILEHASH);
            puinfo->strPath = szaTmp.GetAt(LFILESETUPPATH);
            puinfo->strTempName = szaTmp.GetAt(LFILETMPATH);
            puinfo->strCurrentMD5 = currentHash;
            puinfo->bReadyToCopy = !bDownloadThis;

            m_UpdateFileArray.Add(puinfo);

			if(bDownloadThis){
				iSVPCU_TOTAL_FILEBYTE += _wtoi(szaTmp.GetAt(LFILEGZLEN));
				//szaTmp.SetSize(LFILETOTALPARMS);
				//szaLists.Append( szaTmp );
			}
		}
		szLog.Format(_T("Total Files: %d ; Total Len %d"), iSVPCU_TOTAL_FILE, iSVPCU_TOTAL_FILEBYTE);
		SVP_LogMsg(szLog);
	}
    DeleteFile(szTmpFilename);
	return rret;
}