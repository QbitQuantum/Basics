void CScheduleTableCfgDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    int nXPos = cx - m_DefaultSize.cx;
    int nYPos = cy - m_DefaultSize.cy;
    HDWP hDefer = NULL;

    hDefer = vUpdateWindowPosition(nXPos, nYPos);

    if (hDefer != NULL)
    {
        EndDeferWindowPos(hDefer);
    }
    vAdjustColumns();
}