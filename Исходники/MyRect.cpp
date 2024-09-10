BOOL CMyRect::IsSelected(CPoint point)
{
    CRgn rgn;

    rgn.CreateRectRgn(m_ptBegin.x, m_ptBegin.y,
                      m_ptEnd.x, m_ptEnd.y);

    if (rgn.PtInRegion(point))
    {
        return TRUE;
    }

    return FALSE;
}