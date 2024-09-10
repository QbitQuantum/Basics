BOOL COSMCtrlMapOperationsDlg::DownloadTiles(BOOL bSkipIfTileAlreadyExists)
{
  //Validate our parameters
  AFXASSUME(m_pOSMCtrl);

  //What will be the return value from this function (assume the best)
  BOOL bSuccess = TRUE;

  CSingleLock sl(&m_pOSMCtrl->m_csData, TRUE);
  IOSMCtrlTileProvider* pTileProvider = m_pOSMCtrl->GetTileProvider();
  CString sCacheDirectory(m_pOSMCtrl->m_sCacheDirectory);
  ASSERT(sCacheDirectory.GetLength());
  BOOL bUseIfModifiedSinceHeader(m_pOSMCtrl->m_bUseIfModifiedSinceHeader);
  sl.Unlock();

  //Next get the server to connect to
  CString sServer(pTileProvider->GetDownloadServer());

  //Accumulate how many tiles we have deleted and not deleted
  int nTilesDownloaded = 0;
  int nTilesNotDownloaded = 0;

  //Next create the Wininet session object
  ASSERT(m_hSession == NULL);
  HRESULT hr = m_pOSMCtrl->CreateSession(m_hSession);
  if (SUCCEEDED(hr))
  {
    //Now create the connection object from the session object
    HINTERNET hConnection = NULL;
    hr = m_pOSMCtrl->CreateConnection(m_hSession, sServer, 80, hConnection);
    if (SUCCEEDED(hr))
    {
      //Iterate across the array of tiles to download
      for (INT_PTR i=0; i<m_Tiles.GetSize() && bSuccess; i++)
      {
        //Pull out the next tile to download
        const COSMCtrlMapOperationsDlgTile& tile = m_Tiles.ElementAt(i);

        //Create the sub directories if we can
        CString sSubDirectory;
        sSubDirectory.Format(_T("%s\\%d"), sCacheDirectory.operator LPCTSTR(), tile.m_nZoom);
        CreateDirectory(sSubDirectory, NULL);
        sSubDirectory.Format(_T("%s\\%d\\%d"), sCacheDirectory.operator LPCTSTR(), tile.m_nZoom, tile.m_nTileX);
        CreateDirectory(sSubDirectory, NULL);

        //Form the name of the tile we will be downloading
        CString sObject(pTileProvider->GetDownloadObject(tile.m_nZoom, tile.m_nTileX, tile.m_nTileY));

        //Form the path to the tile we will be downloading to  and determine if we should do the download
        CString sFile(COSMCtrl::GetTileCachePath(sCacheDirectory, tile.m_nZoom, tile.m_nTileX, tile.m_nTileY, FALSE));
        BOOL bDownload = TRUE;
        if (bSkipIfTileAlreadyExists)
          bDownload = (GetFileAttributes(sFile) == INVALID_FILE_ATTRIBUTES);

        //Now download the specific tile to the cache if required
        COSMCtrlMapOperationsDlgEvent dlgEvent;
        dlgEvent.m_bSuccess = false;
        if (bDownload)
        {
          hr = m_pOSMCtrl->DownloadTile(hConnection, sObject, bUseIfModifiedSinceHeader, !bSkipIfTileAlreadyExists, tile.m_nZoom, tile.m_nTileX, tile.m_nTileY, sFile);
          if (FAILED(hr))
          {
            //report the error
            TRACE(_T("COSMCtrlMapOperationsDlg::DownloadTiles, Failed to download tile \"%s\", Error:%08X\n"), sFile.operator LPCTSTR(), hr);
            
            //Ensure any remants of a bad download file are nuked
            DeleteFile(sFile);
            
            //Update the stats
            ++nTilesNotDownloaded;
          }
          else
          {
            //Update the stats
            ++nTilesDownloaded;
            dlgEvent.m_bSuccess = true;
          }
        }
        else
        {
          //Update the stats
          ++nTilesNotDownloaded;
        }

        //Update the UI          
        dlgEvent.m_Event = COSMCtrlMapOperationsDlgEvent::SimpleStringStatus;
        dlgEvent.m_sString = sFile;
        dlgEvent.m_nItemData = i + 1;
        AddEvent(dlgEvent);

        //Check if we have been cancelled before we loop around
        bSuccess = (WaitForSingleObject(m_WorkerTerminateEvent, 0) == WAIT_TIMEOUT);
      }
      
      //Close the wininet connection
    #ifdef COSMCTRL_NOWINHTTP
      InternetCloseHandle(hConnection);
    #else
      WinHttpCloseHandle(hConnection);
    #endif
    }

    //Clean up the wininet session before we exit
  #ifdef COSMCTRL_NOWINHTTP
    InternetCloseHandle(m_hSession);
  #else
    WinHttpCloseHandle(m_hSession);
  #endif
    m_hSession = NULL;
  }

  //Finally add a event about how many items have been downloaded
  COSMCtrlMapOperationsDlgEvent dlgEvent;
  dlgEvent.m_Event = COSMCtrlMapOperationsDlgEvent::SimpleStringStatus;
  CString sTilesDownloaded;
  sTilesDownloaded.Format(_T("%d"), nTilesDownloaded);
  CString sTilesNotDownloaded;
  sTilesNotDownloaded.Format(_T("%d"), nTilesNotDownloaded);
  AfxFormatString2(dlgEvent.m_sString, IDS_OSMCTRL_DOWNLOAD_TILES_STATS, sTilesDownloaded, sTilesNotDownloaded);
  AddEvent(dlgEvent);

  return TRUE;
}