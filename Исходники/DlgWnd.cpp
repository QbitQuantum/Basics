void CDlgWin::UpdateClientColor()
{
    BYTE nRed = m_pRedSlider->GetPos();
    BYTE nGreen = m_pGreenSlider->GetPos();
    BYTE nBlue = m_pBlueSlider->GetPos();

    // Set brush to desired background color
    CBrush br(RGB(nRed, nGreen, nBlue));

    // Save old brush
    CDC* pDC = GetDC();
    CBrush* pbrOld = pDC->SelectObject(&br);

    CRect rc;
    pDC->GetClipBox(&rc);  // Erase only the area needed
    pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
    pDC->SelectObject(pbrOld);
}