void
CHelperbarWindow::UpdateLayout()
{
	RECT  rc;
	GetClientRect(&rc);

	HDWP hdwp = BeginDeferWindowPos(2);
	hdwp = m_Toolbar.DeferWindowPos(hdwp, NULL, 0, 0, rc.right, m_ToolbarHeight, SWP_NOZORDER);
	hdwp = m_Console.DeferWindowPos(hdwp, NULL, 0, m_ToolbarHeight, rc.right, rc.bottom - m_ToolbarHeight, SWP_NOZORDER);
	EndDeferWindowPos(hdwp);
}