////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出
VOID CChildWnd::OnFileExport()
{
	if (m_bExporting == FALSE)
	{
		BOOL bPlay = Stop();
		if (CExportDlg::Show(this))
		{
			_BeginThread(vExportProc, this);
		}
		else if (bPlay)
		{
			Play();
		}
	}
}