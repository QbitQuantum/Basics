//-----------------------------------------------------------------------------
// Purpose: Draws a colored, filled rectangle
// Input  : *rect - 
//			*color - 
//			alpha - 
//-----------------------------------------------------------------------------
void CNetGraphPanel::DrawLine2( vrect_t *rect, unsigned char *color, unsigned char *color2, unsigned char alpha, unsigned char alpha2 )
{
	VPROF( "CNetGraphPanel::DrawLine2" );

	int idx = m_Rects.AddToTail();
	CLineSegment *seg = &m_Rects[ idx ];

	seg->color[0] = color[0];
	seg->color[1] = color[1];
	seg->color[2] = color[2];
	seg->color[3] = alpha;
	seg->color2[0] = color2[0];
	seg->color2[1] = color2[1];
	seg->color2[2] = color2[2];
	seg->color2[3] = alpha2;

	if ( rect->width == 1 )
	{
		seg->x1 = rect->x;
		seg->y1 = rect->y;
		seg->x2 = rect->x;
		seg->y2 = rect->y + rect->height;
	}
	else if ( rect->height == 1 )
	{
		seg->x1 = rect->x;
		seg->y1 = rect->y;
		seg->x2 = rect->x + rect->width;
		seg->y2 = rect->y;
	}
	else
	{
		Assert( 0 );
		m_Rects.Remove( idx );
	}
}