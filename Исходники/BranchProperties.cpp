void C_BranchProperties::DrawJoinStyle(C_DC &dc, unsigned int style, unsigned int width, OLE_COLOR colour)
{
	LOGBRUSH lbr;
	lbr.lbStyle = BS_SOLID;
	lbr.lbHatch = 0;
	lbr.lbColor = colour;

	switch (style) {
	
	case 0:
		dc.ExtCreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_ROUND, width, &lbr, 0, NULL);
		break;
	case 1:		
		dc.ExtCreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_BEVEL, width, &lbr, 0, NULL);
		break;
	case 2:
		::SetMiterLimit(dc.GetHandle(), 2.0, NULL);
		dc.ExtCreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_MITER, width, &lbr, 0, NULL);
		break;
	}

	POINT pts[2] = {
		{ width, 0 },
		{ width, width }
	};

	dc.MoveToEx(0, 0);
	dc.PolylineTo(pts, 2);
}