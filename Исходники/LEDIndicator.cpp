void CLEDIndicator::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    CRect rc;
    GetClientRect(&rc);

    if (m_pieIndicator)
    {
        CDC memDC;
        CBitmap memBitmap;

        memDC.CreateCompatibleDC(&dc);
        memBitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
        memDC.SelectObject(&memBitmap);
        memDC.FillRect(&rc, &m_bkBrush); //background

        DrawLED(memDC, rc);

        // copy the resulting bitmap to the destination DC
        dc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);
    }
    else
        DrawLED(dc, rc);

// Do not call CStatic::OnPaint() for painting messages
}