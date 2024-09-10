//---------------------------------------------------------
bool CGCS_Graticule::Get_Coordinate(const CSG_Rect &Extent, CSG_Shapes *pCoordinates, CSG_Shape *pLine, int Axis)
{
	if( !pCoordinates || !Extent.Intersects(pLine->Get_Extent()) || pLine->Get_Point_Count(0) < 2 )
	{
		return( false );
	}

	TSG_Point	A[2], B[2], C;

	switch( Axis )
	{
	case AXIS_LEFT  : A[0].x = A[1].x = Extent.Get_XMin(); A[0].y = Extent.Get_YMin(); A[1].y = Extent.Get_YMax(); break;
	case AXIS_RIGHT : A[0].x = A[1].x = Extent.Get_XMax(); A[0].y = Extent.Get_YMin(); A[1].y = Extent.Get_YMax(); break;
	case AXIS_BOTTOM: A[0].y = A[1].y = Extent.Get_YMin(); A[0].x = Extent.Get_XMin(); A[1].x = Extent.Get_XMax(); break;
	case AXIS_TOP   : A[0].y = A[1].y = Extent.Get_YMax(); A[0].x = Extent.Get_XMin(); A[1].x = Extent.Get_XMax(); break;

	default:
		return( false );
	}

	//-----------------------------------------------------
	B[1]	= pLine->Get_Point(0);

	for(int i=1; i<pLine->Get_Point_Count(); i++)
	{
		B[0]	= B[1];
		B[1]	= pLine->Get_Point(i);

		if( SG_Get_Crossing(C, A[0], A[1], B[0], B[1], true) )
		{
			CSG_Shape	*pPoint	= pCoordinates->Add_Shape();
			pPoint->Add_Point(C);
			pPoint->Set_Value(0, CSG_String(pLine->asString(0)) + (Axis == AXIS_LEFT || Axis == AXIS_BOTTOM ? "_MIN" : "_MAX"));
			pPoint->Set_Value(1, pLine->asString(1));

			return( true );
		}
	}

	//-----------------------------------------------------
	switch( Axis )
	{
	case AXIS_LEFT  : C	= pLine->Get_Point(0, 0, true ); break;
	case AXIS_RIGHT : C	= pLine->Get_Point(0, 0, false); break;
	case AXIS_BOTTOM: C	= pLine->Get_Point(0, 0, true ); break;
	case AXIS_TOP   : C	= pLine->Get_Point(0, 0, false); break;
	}

	if( Extent.Contains(C) )
	{
		CSG_Shape	*pPoint	= pCoordinates->Add_Shape();
		pPoint->Add_Point(C);
		pPoint->Set_Value(0, CSG_String(pLine->asString(0)) + (Axis == AXIS_LEFT || Axis == AXIS_BOTTOM ? "_MIN" : "_MAX"));
		pPoint->Set_Value(1, pLine->asString(1));

		return( true );
	}

	//-----------------------------------------------------
	return( false );
}