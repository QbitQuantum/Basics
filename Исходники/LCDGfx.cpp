void CLCDGfx::DrawText(int nX, int nY, LPCTSTR sText)
{
    // map mode text, with transparency
    int nOldMapMode = SetMapMode(m_hDC, MM_TEXT);
    int nOldBkMode = SetBkMode(m_hDC, TRANSPARENT); 
    
    ::TextOut(m_hDC, nX, nY, sText, (int)_tcslen(sText));
    
    // restores
    SetMapMode(m_hDC, nOldMapMode);
    SetBkMode(m_hDC, nOldBkMode);

}