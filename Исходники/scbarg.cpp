LRESULT CSizingControlBarG::OnNcHitTest(CPoint point)
{
    CRect rcBar;
    GetWindowRect(rcBar);

    UINT nRet = baseCSizingControlBarG::OnNcHitTest(point);
    if (nRet != HTCLIENT)
        return nRet;

    CRect rc = m_biHide.GetRect();
    rc.OffsetRect(rcBar.TopLeft());
    if (rc.PtInRect(point))
        return HTCLOSE;

    return HTCLIENT;
}