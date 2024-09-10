void BiliPlayer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	EnumChildWindows(m_hWnd, EnumChildWindowsProc, -1);
	// 不为绘图消息调用 CDialogEx::OnPaint()
}