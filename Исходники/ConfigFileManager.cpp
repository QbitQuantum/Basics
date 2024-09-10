void ConfigFileManager::CreateDownloadWindow(const DownloadDialogPtr& dialog)
{
	if (m_pDownloadWindow != NULL)
	{
		delete m_pDownloadWindow;
		m_pDownloadWindow = NULL;
	}

	MONITORINFO mi = { 0 };
	mi.cbSize = sizeof(mi);
	CHECK_WIN32_BOOL(GetMonitorInfo(MonitorFromWindow(NULL, MONITOR_DEFAULTTOPRIMARY), & mi),
		L"GetMonitorInfo");

	int cx = 550;
	int cy = 250;

	m_pDownloadWindow = new DownloadWindow(dialog); // deletes itself
	m_pDownloadWindow->Create(
		(mi.rcWork.left + mi.rcWork.right) / 2 - cx / 2, 
		(mi.rcWork.top + mi.rcWork.bottom) / 2 - cy / 2, 
		cx, cy, dialog->caption.GetValue().c_str());

	CHECK_BOOL(m_pDownloadWindow->hwnd != NULL,
		L"DownloadWindow::Create");
}