void CQTTDemoView::MakeStarPath(GraphicsPath& path, int points, int innerRadius, int outerRadius)
{
	path.Reset();

	REAL phi = 2 * (REAL) atan(1.0f);	// 90 degrees
	REAL dPhi = 2 * phi / points;

	PointF * pnt = new PointF[points * 2];

	for (int i = 0; i < points; i++)
	{
		pnt[2 * i].X = (REAL) (innerRadius * sin(phi - dPhi));
		pnt[2 * i].Y = (REAL) (innerRadius * cos(phi - dPhi));
		pnt[2 * i + 1].X = (REAL) (outerRadius * sin(phi));
		pnt[2 * i + 1].Y = (REAL) (outerRadius * cos(phi));
		phi += 2 * dPhi;
	}
	path.AddLines(pnt, points * 2);
	path.CloseFigure();

	delete[] pnt;
}