void CColorButtonCtrl::FrameButton(CBrush& br)
{
    CDC* pDC = GetDC();

    CRect rc;

    GetClientRect(&rc);

    pDC->FrameRect(&rc, &br);

    ReleaseDC(pDC);
}