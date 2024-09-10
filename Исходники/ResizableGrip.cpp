void CResizableGrip::CSizeGrip::SetTriangularShape(BOOL bEnable)
{
	m_bTriangular = bEnable;

	if (bEnable)
	{
		// set a triangular window region
		CRect rect;
		GetWindowRect(rect);
		rect.OffsetRect(-rect.TopLeft());
		POINT arrPoints[] =
		{
			{ rect.left, rect.bottom },
			{ rect.right, rect.bottom },
			{ rect.right, rect.top }
		};
		CRgn rgnGrip;
		rgnGrip.CreatePolygonRgn(arrPoints, 3, WINDING);
		SetWindowRgn((HRGN)rgnGrip.Detach(), IsWindowVisible());
	}
	else
	{
		SetWindowRgn((HRGN)NULL, IsWindowVisible());
	}
}