int CDuiScrollBar::SetPos(int nPos)
{
    if(nPos>(m_si.nMax-(int)m_si.nPage+1)) nPos=(m_si.nMax-m_si.nPage+1);
    if(nPos<m_si.nMin) nPos=m_si.nMin;
    if(nPos!=m_si.nPos)
    {
        if(m_si.nTrackPos==-1)
        {
            CRect rcOldThumb=GetPartRect(SB_THUMBTRACK);
            m_si.nTrackPos=nPos;
            CRect rcNewThumb=GetPartRect(SB_THUMBTRACK);
            CRect rcUnion;
            rcUnion.UnionRect(&rcOldThumb,&rcNewThumb);
            HDC hdc=GetDuiDC(&rcUnion,OLEDC_PAINTBKGND);
            m_pSkin->Draw(hdc,rcUnion,MAKESBSTATE(SB_PAGEDOWN,SBST_NORMAL,IsVertical()));
            m_pSkin->Draw(hdc,rcNewThumb,MAKESBSTATE(SB_THUMBTRACK,SBST_NORMAL,IsVertical()));
            ReleaseDuiDC(hdc);
            m_si.nTrackPos=-1;
        }
        m_si.nPos=nPos;
    }
    return m_si.nPos;
}