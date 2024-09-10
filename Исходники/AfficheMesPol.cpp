void CAfficheMesPol::AxeGraph(CPaintDC &dc)
{
	dc.FillSolidRect(PosGrX(0),PosGrY(255),PosGrX(255)-20,PosGrY(0)-40,RGB(255,255,255));

	CPen PenAxe(PS_SOLID,1,RGB(0,0,0));
	dc.SelectObject(&PenAxe);
	dc.MoveTo(PosGrX(0),PosGrY(0));
	dc.LineTo(PosGrX(0),PosGrY(255));
	dc.MoveTo(PosGrX(0),PosGrY(0));
	dc.LineTo(PosGrX(255),PosGrY(0));

	for(int i=5;i<255;i+=5)
	{
		dc.MoveTo(PosGrX(0),PosGrY(i));
		dc.LineTo(PosGrX(3),PosGrY(i));
		dc.MoveTo(PosGrX(i),PosGrY(0));
		dc.LineTo(PosGrX(i),PosGrY(3));
	}
	DeleteObject(&PenAxe);
}