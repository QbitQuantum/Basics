//----------------------------------------------------------------------------------//
void CBCGPAutoHideDockBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CBCGPMemDC memDC (dc, this);

	CRect rectClient;
	GetClientRect (rectClient);

	CBCGPVisualManager::GetInstance ()->OnFillBarBackground (&memDC.GetDC (), this,
		rectClient, rectClient);
}