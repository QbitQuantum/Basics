/*
=========================
R_PreciseCullSurface

Check the surface for visibility on a per-triangle basis
for cases when it is going to be VERY expensive to draw (subviews)

If not culled, also returns the bounding box of the surface in
Normalized Device Coordinates, so it can be used to crop the scissor rect.

OPTIMIZE: we could also take exact portal passing into consideration
=========================
*/
bool R_PreciseCullSurface( const drawSurf_t* drawSurf, idBounds& ndcBounds )
{
	const srfTriangles_t* tri = drawSurf->frontEndGeo;
	
	unsigned int pointOr = 0;
	unsigned int pointAnd = ( unsigned int )~0;
	
	// get an exact bounds of the triangles for scissor cropping
	ndcBounds.Clear();
	
	const idJointMat* joints = ( tri->staticModelWithJoints != NULL && r_useGPUSkinning.GetBool() ) ? tri->staticModelWithJoints->jointsInverted : NULL;
	
	for( int i = 0; i < tri->numVerts; i++ )
	{
		const idVec3 vXYZ = idDrawVert::GetSkinnedDrawVertPosition( tri->verts[i], joints );
		
		idPlane eye, clip;
		R_TransformModelToClip( vXYZ, drawSurf->space->modelViewMatrix, tr.viewDef->projectionMatrix, eye, clip );
		
		unsigned int pointFlags = 0;
		for( int j = 0; j < 3; j++ )
		{
			if( clip[j] >= clip[3] )
			{
				pointFlags |= ( 1 << ( j * 2 + 0 ) );
			}
			else if( clip[j] <= -clip[3] )  	// FIXME: the D3D near clip plane is at zero instead of -1
			{
				pointFlags |= ( 1 << ( j * 2 + 1 ) );
			}
		}
		
		pointAnd &= pointFlags;
		pointOr |= pointFlags;
	}
	
	// trivially reject
	if( pointAnd != 0 )
	{
		return true;
	}
	
	// backface and frustum cull
	idVec3 localViewOrigin;
	R_GlobalPointToLocal( drawSurf->space->modelMatrix, tr.viewDef->renderView.vieworg, localViewOrigin );
	
	for( int i = 0; i < tri->numIndexes; i += 3 )
	{
		const idVec3 v1 = idDrawVert::GetSkinnedDrawVertPosition( tri->verts[ tri->indexes[ i + 0 ] ], joints );
		const idVec3 v2 = idDrawVert::GetSkinnedDrawVertPosition( tri->verts[ tri->indexes[ i + 1 ] ], joints );
		const idVec3 v3 = idDrawVert::GetSkinnedDrawVertPosition( tri->verts[ tri->indexes[ i + 2 ] ], joints );
		
		// this is a hack, because R_GlobalPointToLocal doesn't work with the non-normalized
		// axis that we get from the gui view transform.  It doesn't hurt anything, because
		// we know that all gui generated surfaces are front facing
		if( tr.guiRecursionLevel == 0 )
		{
			// we don't care that it isn't normalized,
			// all we want is the sign
			const idVec3 d1 = v2 - v1;
			const idVec3 d2 = v3 - v1;
			const idVec3 normal = d2.Cross( d1 );
			
			const idVec3 dir = v1 - localViewOrigin;
			
			const float dot = normal * dir;
			if( dot >= 0.0f )
			{
				return true;
			}
		}
		
		// now find the exact screen bounds of the clipped triangle
		idFixedWinding w;
		w.SetNumPoints( 3 );
		R_LocalPointToGlobal( drawSurf->space->modelMatrix, v1, w[0].ToVec3() );
		R_LocalPointToGlobal( drawSurf->space->modelMatrix, v2, w[1].ToVec3() );
		R_LocalPointToGlobal( drawSurf->space->modelMatrix, v3, w[2].ToVec3() );
		w[0].s = w[0].t = w[1].s = w[1].t = w[2].s = w[2].t = 0.0f;
		
		for( int j = 0; j < 4; j++ )
		{
			if( !w.ClipInPlace( -tr.viewDef->frustums[FRUSTUM_PRIMARY][j], 0.1f ) )
			{
				break;
			}
		}
		for( int j = 0; j < w.GetNumPoints(); j++ )
		{
			idVec3 screen;
			
			R_GlobalToNormalizedDeviceCoordinates( w[j].ToVec3(), screen );
			ndcBounds.AddPoint( screen );
		}
	}
	
	// if we don't enclose any area, return
	if( ndcBounds.IsCleared() )
	{
		return true;
	}
	
	return false;
}