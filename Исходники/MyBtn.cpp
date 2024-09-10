void CMyBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
    BOOL OldFlag = bTrackLeave;
	if (!bTrackLeave)
	{

       // 鼠标第一次移入窗口时， 请求一个WM_MOUSELEAVE 消息
      
        TRACKMOUSEEVENT tme;

        tme.cbSize = sizeof(tme);

        tme.hwndTrack = m_hWnd;

        tme.dwFlags = TME_LEAVE;

        _TrackMouseEvent(&tme);

        bTrackLeave = TRUE;
        // 在这里添加处理鼠标进入的代码 ：

    }

    if(OldFlag != bTrackLeave)
	{
		this->Invalidate(FALSE);
	}
	CWnd::OnMouseMove(nFlags, point);
}