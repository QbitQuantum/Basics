/*
============
idBrush::Split
============
*/
int idBrush::Split( const idPlane& plane, int planeNum, idBrush** front, idBrush** back ) const
{
	int res, i, j;
	idBrushSide* side, *frontSide, *backSide;
	float dist, maxBack, maxFront, *maxBackWinding, *maxFrontWinding;
	idWinding* w, *mid;
	
	assert( windingsValid );
	
	if( front )
	{
		*front = NULL;
	}
	if( back )
	{
		*back = NULL;
	}
	
	res = bounds.PlaneSide( plane, -BRUSH_EPSILON );
	if( res == PLANESIDE_FRONT )
	{
		if( front )
		{
			*front = Copy();
		}
		return res;
	}
	if( res == PLANESIDE_BACK )
	{
		if( back )
		{
			*back = Copy();
		}
		return res;
	}
	
	maxBackWinding = ( float* ) _alloca16( sides.Num() * sizeof( float ) );
	maxFrontWinding = ( float* ) _alloca16( sides.Num() * sizeof( float ) );
	
	maxFront = maxBack = 0.0f;
	for( i = 0; i < sides.Num(); i++ )
	{
		side = sides[i];
		
		w = side->winding;
		
		if( !w )
		{
			continue;
		}
		
		maxBackWinding[i] = 10.0f;
		maxFrontWinding[i] = -10.0f;
		
		for( j = 0; j < w->GetNumPoints(); j++ )
		{
		
			dist = plane.Distance( ( *w )[j].ToVec3() );
			if( dist > maxFrontWinding[i] )
			{
				maxFrontWinding[i] = dist;
			}
			if( dist < maxBackWinding[i] )
			{
				maxBackWinding[i] = dist;
			}
		}
		
		if( maxFrontWinding[i] > maxFront )
		{
			maxFront = maxFrontWinding[i];
		}
		if( maxBackWinding[i] < maxBack )
		{
			maxBack = maxBackWinding[i];
		}
	}
	
	if( maxFront < BRUSH_EPSILON )
	{
		if( back )
		{
			*back = Copy();
		}
		return PLANESIDE_BACK;
	}
	
	if( maxBack > -BRUSH_EPSILON )
	{
		if( front )
		{
			*front = Copy();
		}
		return PLANESIDE_FRONT;
	}
	
	mid = new idWinding( plane.Normal(), plane.Dist() );
	
	for( i = 0; i < sides.Num() && mid; i++ )
	{
		mid = mid->Clip( -sides[i]->plane, BRUSH_EPSILON, false );
	}
	
	if( mid )
	{
		if( mid->IsTiny() )
		{
			delete mid;
			mid = NULL;
		}
		else if( mid->IsHuge() )
		{
			// if the winding is huge then the brush is unbounded
			common->Warning( "brush %d on entity %d is unbounded"
							 "( %1.2f %1.2f %1.2f )-( %1.2f %1.2f %1.2f )-( %1.2f %1.2f %1.2f )", primitiveNum, entityNum,
							 bounds[0][0], bounds[0][1], bounds[0][2], bounds[1][0], bounds[1][1], bounds[1][2],
							 bounds[1][0] - bounds[0][0], bounds[1][1] - bounds[0][1], bounds[1][2] - bounds[0][2] );
			delete mid;
			mid = NULL;
		}
	}
	
	if( !mid )
	{
		if( maxFront > - maxBack )
		{
			if( front )
			{
				*front = Copy();
			}
			return PLANESIDE_FRONT;
		}
		else
		{
			if( back )
			{
				*back = Copy();
			}
			return PLANESIDE_BACK;
		}
	}
	
	if( !front && !back )
	{
		delete mid;
		return PLANESIDE_CROSS;
	}
	
	*front = new idBrush();
	( *front )->SetContents( contents );
	( *front )->SetEntityNum( entityNum );
	( *front )->SetPrimitiveNum( primitiveNum );
	*back = new idBrush();
	( *back )->SetContents( contents );
	( *back )->SetEntityNum( entityNum );
	( *back )->SetPrimitiveNum( primitiveNum );
	
	for( i = 0; i < sides.Num(); i++ )
	{
		side = sides[i];
		
		if( !side->winding )
		{
			continue;
		}
		
		// if completely at the front
		if( maxBackWinding[i] >= BRUSH_EPSILON )
		{
			( *front )->sides.Append( side->Copy() );
		}
		// if completely at the back
		else if( maxFrontWinding[i] <= -BRUSH_EPSILON )
		{
			( *back )->sides.Append( side->Copy() );
		}
		else
		{
			// split the side
			side->Split( plane, &frontSide, &backSide );
			if( frontSide )
			{
				( *front )->sides.Append( frontSide );
			}
			else if( maxFrontWinding[i] > -BRUSH_EPSILON )
			{
				// favor an overconstrained brush
				side = side->Copy();
				side->winding = side->winding->Clip( idPlane( plane.Normal(), ( plane.Dist() - ( BRUSH_EPSILON + 0.02f ) ) ), 0.01f, true );
				assert( side->winding );
				( *front )->sides.Append( side );
			}
			if( backSide )
			{
				( *back )->sides.Append( backSide );
			}
			else if( maxBackWinding[i] < BRUSH_EPSILON )
			{
				// favor an overconstrained brush
				side = side->Copy();
				side->winding = side->winding->Clip( idPlane( -plane.Normal(), -( plane.Dist() + ( BRUSH_EPSILON + 0.02f ) ) ), 0.01f, true );
				assert( side->winding );
				( *back )->sides.Append( side );
			}
		}
	}
	
	side = new idBrushSide( -plane, planeNum ^ 1 );
	side->winding = mid->Reverse();
	side->flags |= SFL_SPLIT;
	( *front )->sides.Append( side );
	( *front )->windingsValid = true;
	( *front )->BoundBrush( this );
	
	side = new idBrushSide( plane, planeNum );
	side->winding = mid;
	side->flags |= SFL_SPLIT;
	( *back )->sides.Append( side );
	( *back )->windingsValid = true;
	( *back )->BoundBrush( this );
	
	return PLANESIDE_CROSS;
}