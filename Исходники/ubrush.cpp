/*
==================
BrushMostlyOnSide

==================
*/
int BrushMostlyOnSide( uBrush_t *brush, idPlane &plane )
{
	int			i, j;
	idWinding	*w;
	float		d, max = 0;
	int			side = PSIDE_FRONT;
	
	for( i = 0; i < brush->numsides; i++ )
	{
		w = brush->sides[i].winding;
		
		if( !w )
		{
			continue;
		}
		
		for( j = 0; j < w->GetNumPoints(); j++ )
		{
			d = plane.Distance( ( *w ) [j].ToVec3() );
			
			if( d > max )
			{
				max = d;
				side = PSIDE_FRONT;
			}
			
			if( -d > max )
			{
				max = -d;
				side = PSIDE_BACK;
			}
		}
	}
	return side;
}