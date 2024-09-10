LTVector GetContouringNormal( LTVector &vPos, LTVector &vDims, LTVector &vForward, LTVector &vRight, HOBJECT *pFilterList )
{
	LTVector	avPt[4];		// points we are casting the rays from
	LTVector	avInterPt[4];	// points of intersection
	LTVector	avNormal[4];	// normals constructed from the points of intersection
	LTVector	avEdge[4];

	// Develop the points we wish to cast rays from...
	// We keep the height from the object incase the vehicle has clipped into the world.

	avPt[0] = vPos + ( vForward ) - ( vRight );	// 0----1
	avPt[1] = vPos + ( vForward ) + ( vRight );	// |    |
	avPt[2] = vPos - ( vForward ) + ( vRight );	// |    |
	avPt[3] = vPos - ( vForward ) - ( vRight );	// 3----2

	// Find the point of intersection that is under the vehicle...
	// If none was found just use the point with the height factored in.
	
	if( !GetIntersectionUnderPoint( avPt[0], pFilterList, avNormal[0], avInterPt[0] ) )
	{
		avInterPt[0] = avPt[0];
		avInterPt[0].y -= vDims.y;
	}

	if( !GetIntersectionUnderPoint( avPt[1], pFilterList, avNormal[1], avInterPt[1] ) )
	{
		avInterPt[1] = avPt[1];
		avInterPt[1].y -= vDims.y;
	}

	if( !GetIntersectionUnderPoint( avPt[2], pFilterList, avNormal[2], avInterPt[2] ) )
	{
		avInterPt[2] = avPt[2];
		avInterPt[2].y -= vDims.y;
	}

	if( !GetIntersectionUnderPoint( avPt[3], pFilterList, avNormal[3], avInterPt[3] ) )
	{
		avInterPt[3] = avPt[3];
		avInterPt[3].y -= vDims.y;
	}

	// Move the points to the origin...

	avInterPt[0] -= vPos;
	avInterPt[1] -= vPos;
	avInterPt[2] -= vPos;
	avInterPt[3] -= vPos;

	// Develop the vectors that will construct the 4 planes...

	avEdge[0] = (avInterPt[1] - avInterPt[0]).GetUnit();
	avEdge[1] = (avInterPt[2] - avInterPt[1]).GetUnit();
	avEdge[2] = (avInterPt[3] - avInterPt[2]).GetUnit();
	avEdge[3] = (avInterPt[0] - avInterPt[3]).GetUnit();

	// Find the normals of the planes...

	avNormal[0] = -avEdge[3].Cross( avEdge[0] );
	avNormal[1] = -avEdge[0].Cross( avEdge[1] );
	avNormal[2] = -avEdge[1].Cross( avEdge[2] );
	avNormal[3] = -avEdge[2].Cross( avEdge[3] );

	avNormal[0].Normalize();
	avNormal[1].Normalize();
	avNormal[2].Normalize();
	avNormal[3].Normalize();

	// Average the normals...
	
	LTVector vNormal = avNormal[0] + avNormal[1] + avNormal[2] + avNormal[3];
	vNormal.Normalize();

	return vNormal;
}