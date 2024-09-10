//---------------------------------------------------------
bool CSelect_Location::Do_Select(CSG_Shape *pShape, int Condition)
{
	for(int i=0; i<m_pLocations->Get_Count() && Process_Get_Okay(); i++)
	{
		CSG_Shape	*pLocation	= m_pLocations->Get_Shape(i);

		if( pShape->Intersects(pLocation->Get_Extent()) )
		{
			switch( Condition )
			{
			case 0: // intersect
				if( pLocation->Intersects(pShape) )
				{
					return( true );
				}
				break;

			case 1: // are completely within
				if( pLocation->Intersects(pShape) == INTERSECTION_Contains )
				{
					return( true );
				}
				break;

			case 2: // completely contain
				if( pShape->Intersects(pLocation) == INTERSECTION_Contains )
				{
					return( true );
				}
				break;

			case 3: // have their centroid in
				if( ((CSG_Shape_Polygon *)pLocation)->Contains(pShape->Get_Centroid()) )
				{
					return( true );
				}
				break;

			case 4: // contain the centroid of
				if( ((CSG_Shape_Polygon *)pShape)->Contains(pLocation->Get_Centroid()) )
				{
					return( true );
				}
				break;
			}
		}
	}

	return( false );
}