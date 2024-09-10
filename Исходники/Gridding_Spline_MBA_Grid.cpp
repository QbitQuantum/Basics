//---------------------------------------------------------
bool CGridding_Spline_MBA_Grid::_Get_Difference(CSG_Grid &Phi)
{
	int				xPoint, yPoint, nErrors;
	double			x, y, z, zMax, zMean;
	TSG_Point_Z	p;
	CSG_String		s;

	//-----------------------------------------------------
	for(yPoint=0, p.y=m_Points.Get_YMin(), zMax=0.0, nErrors=0, zMean=0.0; yPoint<m_Points.Get_NY() && Set_Progress(yPoint, m_Points.Get_NY()); yPoint++, p.y+=m_Points.Get_Cellsize())
	{
		for(xPoint=0, p.x=m_Points.Get_XMin(); xPoint<m_Points.Get_NX(); xPoint++, p.x+=m_Points.Get_Cellsize())
		{
			if( !m_Points.is_NoData(xPoint, yPoint) )
			{
				x	= (p.x - Phi.Get_XMin()) / Phi.Get_Cellsize();
				y	= (p.y - Phi.Get_YMin()) / Phi.Get_Cellsize();
				z	= m_Points.asDouble(xPoint, yPoint) - BA_Get_Value(x, y, Phi);

				m_Points.Set_Value(xPoint, yPoint, z);

				if( (z = fabs(z)) > m_Epsilon )
				{
					nErrors	++;
					zMean	+= fabs(z);

					if( fabs(z) > zMax )
					{
						zMax	= fabs(z);
					}
				}
				else
				{
				//	m_Points.Set_Value(xPoint, yPoint, 0.0);
					m_Points.Set_NoData(xPoint, yPoint);
				}
			}
		}
	}

	if( nErrors > 0 )
	{
		zMean	/= nErrors;
	}

	//-----------------------------------------------------
	int	i	= 1 + (int)(0.5 + log(Phi.Get_NX() - 4.0) / log(2.0));

	s.Printf(SG_T("%s:%d, %s:%d, %s:%f, %s:%f"),
		_TL("level"), i,
		_TL("error"), nErrors,
		_TL("max")	, zMax,
		_TL("mean")	, zMean
	);

	Process_Set_Text(s);
	Message_Add     (s);

	return( zMax >= m_Epsilon && i < m_Level_Max && Process_Get_Okay(false) );
}