void CRelaxReminderDlg::RelaxNotify()
{
    UINT    nLS = 0;
    BOOL    bShortRelax = FALSE;

    nLS     = m_tm.GetLS();
    switch (m_tm.GetStatus())
    {
    case STATUS_SHORT_RELAX:
        bShortRelax = TRUE;
    	break;
    case STATUS_LONG_RELAX:
        bShortRelax = FALSE;
        break;
    default:
        return;
    }

    if (nLS == 0)
    {
        CalcNotifyWindowPos();
        if (m_bDarkerScreen)
        {
            // 先显示ScreenMask
            ShowDarkerScreen(m_iDarkerScreenAlpha,
                m_colorDarkerScreen,
                m_eDarkerScreenAnimateType);
        }
    }
    if ((!m_bDarkerScreen && (nLS == 0)) ||
        (m_bDarkerScreen && (nLS == TRAY_WINDOW_DELAY)))
    {
        // 再显示TrayWindow
        m_dlgRelaxNotify.ShowTrayWindow(
            m_str.GetStr(bShortRelax ? TRAY_WINDOW_CAPTION_SHORT_RELAX : TRAY_WINDOW_CAPTION_LONG_RELAX),
            GetFixedColonTime());
    }
    
    // 更新任务栏提示窗口显示的时间
    m_dlgRelaxNotify.UpdateTrayWindow(NULL, GetTwinklingTime());
    
    // 如果启用了休息时锁定鼠标键盘，则在休息开始后10秒钟时锁定
    if (m_bLockInput && nLS == (UINT)m_iGraceTimeBeforeLockInput)
    {
        switch (m_iLockType)
        {
        case RELAX_LOCK_KEYBOARD:
            LockKeyboard(TRUE);
            break;
        case RELAX_LOCK_MOUSE:
            LockMouse(TRUE);
            break;
        case RELAX_LOCK_BOTH:
            LockKeyBoardAndMouse(TRUE);
            break;
        default:
            LockMouse(TRUE);
            break;
        }
        m_dlgRelaxNotify.GetDlgItem(IDC_BUTTON_DELAY)->EnableWindow(FALSE);
        m_dlgRelaxNotify.GetDlgItem(IDC_BUTTON_SKIP)->EnableWindow(FALSE);
        m_dlgRelaxNotify.GetDlgItem(IDC_BUTTON_HIDE)->EnableWindow(FALSE);
    }
    
    // 如果启用了锁定计算机，则在休息开始后17秒钟时锁定
    if (m_bLockComputer && nLS == 17)
    {
        LockWorkStation();
    }
    
    // 如果启用了关闭显示器，则在休息开始后20秒钟时关闭
    if (m_bCloseMonitor && nLS == 20)
    {
        ::SendMessage(GetSafeHwnd(), WM_SYSCOMMAND, SC_MONITORPOWER, 1);
    }
}