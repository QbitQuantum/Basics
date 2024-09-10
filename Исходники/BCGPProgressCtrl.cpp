//**************************************************************************
void CBCGPProgressCtrl::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    CBCGPMemDC memDC (dc, this);
    CDC* pDC = &memDC.GetDC ();

    DoPaint(pDC);
}