int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetGestureConfig(&m_gestureConfig);

	// Only rotation is not enabled by default
	m_gestureConfig.EnableRotate();

	SetGestureConfig(&m_gestureConfig);

	return 0;
}