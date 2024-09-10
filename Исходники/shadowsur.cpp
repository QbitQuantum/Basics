void ShadowSur::PolygonSkew(const Vertex2D * const rgv, const int count, const float * const rgz) const
{
	POINT * const rgpt = new POINT[count];

	for (int i=0;i<count;i++)
	{
		rgpt[i].x = SCALEXf(rgv[i].x + rgz[i]);
		rgpt[i].y = SCALEYf(rgv[i].y - rgz[i]);
	}

	SelectObject(m_hdc, GetStockObject(BLACK_PEN));
	SelectObject(m_hdc, GetStockObject(BLACK_BRUSH));

	SetViewportOrgEx(m_hdc, 0, 0, NULL);
	::Polygon(m_hdc, rgpt, count);

	delete [] rgpt;

	SetViewportOrgEx(m_hdc, 0, 0, NULL);
}