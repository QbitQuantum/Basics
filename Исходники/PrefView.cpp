void CPrefView::ReSize()
{
	CRect rect;
	CRect rect_cy;
	GetClientRect(rect);
	int x=rect.right;
	int y=rect.bottom;
//	if (x<500) x=500;
//	if (y<400) y=400;
	LONG l=GetDialogBaseUnits();
	double kx=LOWORD(l)/8.0;
	double ky=HIWORD(l)/16.0;

	m_ComboY.GetClientRect(rect_cy);
	WORD dx=6;
	WORD dy=13;
	int x1,y1;
	x1=(136*dx)/4; y1=(125*dy)/8;
	//m_Grid.MoveWindow((int)(x1*kx),(int)(y1*ky),(int)(x-x1*kx-10),(int)(y-y1*ky-10));
	m_Grid.MoveWindow(rect_cy.right+30,(int)(y1*ky),(int)(x-rect_cy.right-40),(int)(y-y1*ky-10));
	GetDlgItem(IDC_STATIC_FACE)->MoveWindow((int)(x-40*kx),(int)(33*ky),32,32);
	x1=(140*dx)/4; y1=(13*dy)/8;
	//GetDlgItem(IDC_STATIC_SCALE)->MoveWindow((int)(x1*kx),(int)(33*ky),(int)(x-(x1+50)*kx),(int)(20*ky));
	GetDlgItem(IDC_STATIC_SCALE)->MoveWindow(rect_cy.right+30,(int)(33*ky),(int)(x-rect_cy.right-30-50*kx),(int)(20*ky));
	//y1=(25*dy)/8;
	//m_Slider.MoveWindow((int)(x1*kx),(int)(55*ky),(int)(x-(x1+50)*kx),(int)(30*ky));
	m_Slider.MoveWindow(rect_cy.right+30,(int)(55*ky),(int)(x-rect_cy.right-30-50*kx),(int)(30*ky));
}