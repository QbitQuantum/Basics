BOOL CCapVideoApp::InitInstance(){
  InitCommonControls();
  CWinApp::InitInstance();
  SetRegistryKey(_T("6BEE NETWORKS PTE LTD"));
  CWinThread::InitInstance();
  CCapVideoDlg dlg;//main thread start dialog frame
  if(!InitCapture()){
    return FALSE;
  }
  dlg.m_caprawvideo = m_caprawvideo;
  if (m_caprawvideo){//derive a thread to capture video
    m_caprawvideo->PostThreadMessage(WM_STARTPREVIEW,(WPARAM)&(dlg.m_cappreview),(LPARAM)0);
  }
  INT_PTR nResponse = dlg.DoModal();
  if (nResponse == IDCANCEL && strlen(m_caprawvideo->getavfilename())!=0){
    /// @todo temp comment out this -  can use a function in 6beecommond.dll to replace it.
    ///////////////////////////// start to upload /////////////////////////////////
    /*
    USES_CONVERSION;
    CString videopath;
    videopath.Format(_T("%s%s"),_6beed_util::Get6BEEPath(_6bees_const::kVideoDir,true),A2CW(m_caprawvideo->getavfilename()));
    HWND hwndTo = ::FindWindow(0,_6bees_const::kUploader_WndTitle);
    if(!hwndTo){
      CString UploaderCmd = _6beed_util::Get6BEEPath(_6bees_const::kUploaderName);
      UploaderCmd += _T(" -m upload -f \"") + videopath + _T("\"");
      STARTUPINFO si = {sizeof(si)};
      PROCESS_INFORMATION pi;
      if (!CreateProcessW(NULL,const_cast<LPWSTR>(UploaderCmd.GetString()),NULL,NULL,false,0,NULL,NULL,&si,&pi)){
        ::AfxMessageBox(_T("ERROR: Cannot Start 6BeeUpLoader!"));
      }
    }else{
      _6beed_util::SendMsgToUploader(hwndTo,W2CA(videopath),CPYDATA_UPLOAD_2_UPLOAD_DIRECT);
    }
    */
    /////////////////////////////////////////////////////////////////////////////
  }
  return FALSE;
}