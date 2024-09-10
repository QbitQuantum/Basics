void CDrawBlockRotate::Paint(CContext &dc, paint_options options)
{
	// Draw marquee
	dc.SelectBrush();
	if (m_point_a.x < m_point_b.x)
	{
		dc.SelectPen(PS_MARQUEE, 1, cBLOCK);
	}
	else
	{
		// Other marquee pen for right to left selection
		dc.SelectPen(PS_MARQUEE2, 1, cBLOCK);
	}

	dc.SetROP2(R2_COPYPEN);
	dc.Rectangle(theArea);
}