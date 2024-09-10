void COXToolTipCtrl::Pop()
{
    ShowWindow(SW_HIDE);
    m_bTipCancelled = TRUE;
    m_pCurrentToolTip = NULL;
}