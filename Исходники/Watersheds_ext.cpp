//---------------------------------------------------------
bool CWatersheds_ext::Get_Basin(CSG_Grid *pBasins, CSG_Shapes *pPolygons, int xMouth, int yMouth, int Main_ID)
{
	int						x, y, Basin_ID	= 1 + pPolygons->Get_Count();
	CSG_Shape				*pPolygon;
	CSG_Grid_Stack			Stack;
	CSG_Simple_Statistics	s_Height, s_Distance;

	//-----------------------------------------------------
	Stack.Push(x = xMouth, y = yMouth);

	pBasins		->Set_Value(x, y, Basin_ID);
	m_Distance	 .Set_Value(x, y, 0.0);

	s_Height	+= m_pDEM->asDouble(x, y);
	s_Distance	+= 0.0;

	//-----------------------------------------------------
	while( Stack.Get_Size() > 0 && Process_Get_Okay() )
	{
		Stack.Pop(x, y);

		double	d	= m_Distance.asDouble(x, y);

		//-------------------------------------------------
		for(int i=0; i<8; i++)
		{
			int	ix	= Get_xFrom(i, x);
			int	iy	= Get_yFrom(i, y);

			if( is_InGrid(ix, iy) && pBasins->is_NoData(ix, iy) && i == m_Direction.asInt(ix, iy) )
			{
				Stack.Push(ix, iy);

				pBasins		->Set_Value(ix, iy, Basin_ID);
				m_Distance	 .Set_Value(ix, iy, d + Get_Length(i));

				s_Height	+= m_pDEM->asDouble(ix, iy);
				s_Distance	+= d + Get_Length(i);
			}
		}
	}

	//-----------------------------------------------------
	if( s_Height.Get_Count() > 1 && (pPolygon = Get_Basin(pBasins, pPolygons)) != NULL )
	{
		double		d, Area, Perimeter, Side_A, Side_B;
		CSG_String	Gravelius;

	//	Area		= s_Height.Get_Count() * Get_System()->Get_Cellarea();
		Area		= ((CSG_Shape_Polygon*)pPolygon)->Get_Area();
		Perimeter	= ((CSG_Shape_Polygon*)pPolygon)->Get_Perimeter();

		d			= 0.28 * Perimeter / sqrt(Area);
		Gravelius	= d > 1.75 ? _TL("rectangular")
					: d > 1.5  ? _TL("ovalooblonga-rectangularoblonga")
					: d > 1.25 ? _TL("ovaloredonda-ovalooblonga")
					:            _TL("redonda-ovaloredonda");

		d			= pow(Perimeter, 2.0) - 8.0 * Area;
		Side_A		= d > 0.0 ? (Perimeter + sqrt(d))      / 4.0 : -1.0;
		Side_B		= d > 0.0 ? (Perimeter - 2.0 * Side_A) / 2.0 : -1.0;

		pPolygon->Set_Value(FIELD_ID			, Basin_ID);
		pPolygon->Set_Value(FIELD_ID_MAIN		, Main_ID);

		pPolygon->Set_Value(FIELD_MOUTH_X		, Get_System()->Get_xGrid_to_World(xMouth));
		pPolygon->Set_Value(FIELD_MOUTH_Y		, Get_System()->Get_yGrid_to_World(yMouth));

		pPolygon->Set_Value(FIELD_PERIMETER		, Perimeter);
		pPolygon->Set_Value(FIELD_AREA			, Area);

		pPolygon->Set_Value(FIELD_CENTROID_X	, ((CSG_Shape_Polygon*)pPolygon)->Get_Centroid().x);
		pPolygon->Set_Value(FIELD_CENTROID_Y	, ((CSG_Shape_Polygon*)pPolygon)->Get_Centroid().y);

		pPolygon->Set_Value(FIELD_Z_MEAN		, s_Height  .Get_Mean());
		pPolygon->Set_Value(FIELD_Z_RANGE		, s_Height  .Get_Range());

		pPolygon->Set_Value(FIELD_DIST_MEAN		, s_Distance.Get_Mean());
		pPolygon->Set_Value(FIELD_DIST_MAX		, s_Distance.Get_Maximum());

		pPolygon->Set_Value(FIELD_CONCTIME		, s_Height.Get_Range() <= 0.0 ? -1.0 :
			pow(0.87 * pow(s_Distance.Get_Maximum() / 1000.0, 3.0) / s_Height.Get_Range(),  0.385)
		);

		pPolygon->Set_Value(FIELD_BASIN_TYPE	, Gravelius);

		pPolygon->Set_Value(FIELD_EQVRECT_A		, Side_A);
		pPolygon->Set_Value(FIELD_EQVRECT_B		, Side_B);

		pPolygon->Set_Value(FIELD_OROG_IDX		, SG_Get_Square(s_Height.Get_Mean()) / (0.0001 * Area));	// Orographic index, defined as the mean catchment altitude times the ratio of the mean catchment altitude to the orthogonal projection of drainage area (Alcázar, Palau (2010): Establishing environmental flow regimes in a Mediterranean watershed based on a regional classification. Journal of Hydrology, V. 388
		pPolygon->Set_Value(FIELD_MASS_IDX		, Perimeter / (0.0001 * Area));								// Perimeter / (0.0001 * Area) ??!!

		pPolygon->Set_Value(FIELD_BASINS_UP		, 0.0);	// Upslope Basins
		pPolygon->Set_Value(FIELD_BASINS_DOWN	, 0.0);	// Downslope Basins

		return( true );
	}

	return( false );
}