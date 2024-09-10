//---------------------------------------------------------
bool CSG_Rect::Intersect(const CSG_Rect &Rect)
{
	switch( Intersects(Rect) )
	{
	case INTERSECTION_None: default:
		return( false );

	case INTERSECTION_Identical:
	case INTERSECTION_Contained:
		break;

	case INTERSECTION_Contains:
		m_rect	= Rect.m_rect;
		break;

	case INTERSECTION_Overlaps:
		if( m_rect.xMin < Rect.Get_XMin() )
		{
			m_rect.xMin	= Rect.Get_XMin();
		}

		if( m_rect.yMin < Rect.Get_YMin() )
		{
			m_rect.yMin	= Rect.Get_YMin();
		}

		if( m_rect.xMax > Rect.Get_XMax() )
		{
			m_rect.xMax	= Rect.Get_XMax();
		}

		if( m_rect.yMax > Rect.Get_YMax() )
		{
			m_rect.yMax	= Rect.Get_YMax();
		}
		break;
	}

	return( true );
}