void CUIEditBox::OnLButtonDown(POINT point)
{
    screenToClient(point);
    SetFocus();
    SetPressed(true);
    //SetCapture(UIGetHWND());
    // Determine the character corresponding to the coordinates.
    int nCP, nX1st;
    bool bTrail;
    m_Buffer.CPtoX(m_nFirstVisible, FALSE, nX1st);  // X offset of the 1st visible char
    if(m_Buffer.XtoCP(point.x - m_rcText.left + nX1st, nCP, bTrail))
    {
        // Cap at the NULL character.
        if(bTrail && nCP < m_Buffer.GetTextSize())
            PlaceCaret(nCP + 1);
        else
            PlaceCaret(nCP);
        m_nSelStart = m_nCaret;
        ResetCaretBlink();
    }
}