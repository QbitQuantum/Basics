BOOL CScreenCapture::CaptureScreenRect(RECT rcCapture, CString sSaveDirName, int nIdStartFrom, std::vector<CString>& out_file_list)
{	
  // Get cursor information
  GetCursorPos(&m_ptCursorPos);
  m_CursorInfo.cbSize = sizeof(CURSORINFO);
  GetCursorInfo(&m_CursorInfo);

  m_nIdStartFrom = nIdStartFrom;
  m_sSaveDirName = sSaveDirName;
	EnumDisplayMonitors(NULL, &rcCapture, EnumMonitorsProc, (LPARAM)this);	
  out_file_list = m_out_file_list;
	return TRUE;
}