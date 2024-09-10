void CLCDGfxBase::EndDraw(void)
{
    LCDUIASSERT(NULL != m_hPrevBitmap);
    if(NULL != m_hPrevBitmap)
    {
        GdiFlush();
        m_hPrevBitmap = (HBITMAP) SelectObject(m_hDC, m_hPrevBitmap);
        LCDUIASSERT(m_hPrevBitmap == m_hBitmap);
        m_hPrevBitmap = NULL;
    }
}