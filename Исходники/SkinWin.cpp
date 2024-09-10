CRect CSkinWin::GetButtonRect(int i)
{
    CWnd *pWnd = CWnd::FromHandle(m_hWnd);
    CRect wr;
    pWnd->GetWindowRect(wr);

    CRect r;
    if ( i == 0 && m_bmpCloseBtn.GetSafeHandle() )
    {
        //close
        r = m_rectCloseBtn;
        r.left = wr.Width() - m_rectCloseBtn.right;
        r.right = wr.Width() - m_rectCloseBtn.left;
    }
    if ( i == 2 && m_bmpMaxBtn.GetSafeHandle())
    {
        //max
        
        if ( m_winstate != 1 || !m_bmpRestoreBtn.GetSafeHandle() )
        {
            r = m_rectMaxBtn;
            r.left = wr.Width() - m_rectMaxBtn.right;
            r.right = wr.Width() - m_rectMaxBtn.left;
        }
        else
        {
            r = m_rectRestoreBtn;
            r.left = wr.Width() - m_rectRestoreBtn.right;
            r.right = wr.Width() - m_rectRestoreBtn.left;
        }
            
    }
    if ( i == 1/*2*/ && m_bmpMinBtn.GetSafeHandle())//modify by liu 修正最小化按钮鼠标进入的闪烁错误
    {
        //min
        r = m_rectMinBtn;
        r.left = wr.Width() - m_rectMinBtn.right;
        r.right = wr.Width() - m_rectMinBtn.left;
    }

    return r;

}