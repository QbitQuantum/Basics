void CBCGPSpinButtonCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CBCGPMemDC memDC (dc, this);

	OnDraw (&memDC.GetDC ());
}