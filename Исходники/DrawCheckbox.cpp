void CDrawCheckbox::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
    //  按钮可用
    if(m_nCtrlState != STATE_DISABLE)
    {
        POINT pt = {};
        GetCursorPos(&pt);
        ScreenToClient(m_hWnd, &pt);
        if(PtInRegion(m_hCtrlRgn, pt.x, pt.y))  //  鼠标在控件区域内
        {
            //  鼠标没有跟踪
            if(!m_fTrackMouse)
            {
                //  跟踪鼠标离开,触发MouseLeave消息
                TRACKMOUSEEVENT MouseEvent = {sizeof(TRACKMOUSEEVENT)};
                MouseEvent.dwFlags = TME_LEAVE;
                MouseEvent.hwndTrack = m_hWnd;
                MouseEvent.dwHoverTime = 1000;
                TrackMouseEvent(&MouseEvent);

                //  设置鼠标被跟踪
                m_fTrackMouse = TRUE;
            }

            //  按钮没有按下,则设置按钮状态为焦点
            if(m_nCtrlState != STATE_DOWN)
                m_nCtrlState = STATE_FOCUS;
        }
        else // 移动到区域外，均直接处理为鼠标弹起
        {
            m_nCtrlState = STATE_UP; 
        }
        InvalidataCtrl();
    }
}