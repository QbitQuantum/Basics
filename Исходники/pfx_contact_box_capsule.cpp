PfxFloat pfxContactBoxCapsule(
	PfxVector3 &normal,PfxPoint3 &pointA,PfxPoint3 &pointB,
	void *shapeA,const PfxTransform3 &transformA,
	void *shapeB,const PfxTransform3 &transformB,
	PfxFloat distanceThreshold)
{
	PfxBox boxA = *((PfxBox*)shapeA);
	PfxCapsule capsuleB = *((PfxCapsule*)shapeB);

	PfxVector3 ident[3] = {
		PfxVector3(1.0,0.0,0.0),
		PfxVector3(0.0,1.0,0.0),
		PfxVector3(0.0,0.0,1.0),
	};

	// get capsule position and direction in box's coordinate system

	PfxMatrix3 matrixA = transformA.getUpper3x3();
	PfxMatrix3 matrixAinv = transpose(matrixA);

	PfxVector3 directionB = transformB.getUpper3x3().getCol0();
	PfxVector3 translationB = transformB.getTranslation();

	PfxVector3 capsDirection = matrixAinv * directionB;
	PfxVector3 absCapsDirection = absPerElem(capsDirection);
	PfxVector3 offsetAB = matrixAinv * (translationB - transformA.getTranslation());

	// find separating axis with largest gap between projections

	BoxCapsSepAxisType axisType;
	PfxVector3 axisA;
	PfxFloat maxGap;
	int faceDimA = 0, edgeDimA = 0;

	// face axes

	// can compute all the gaps at once with VU0

	PfxVector3 gapsA = absPerElem(offsetAB) - boxA.m_half - absCapsDirection * capsuleB.m_halfLen;

	AaxisTest( 0, X, true );
	AaxisTest( 1, Y, false );
	AaxisTest( 2, Z, false );

	// cross product axes

	// compute gaps on all cross product axes using some VU0 math.  suppose there's a tradeoff
	// between doing this with SIMD all at once or without SIMD in each cross product test, since
	// some test might exit early.

	PfxVector3 lsqrs, projOffset, projAhalf;

	PfxMatrix3 crossProdMat = crossMatrix(capsDirection) * PfxMatrix3::identity();
	PfxMatrix3 crossProdMatT = crossMatrix(-capsDirection) * PfxMatrix3::identity();

	lsqrs = mulPerElem( crossProdMatT.getCol0(), crossProdMatT.getCol0() ) +
			mulPerElem( crossProdMatT.getCol1(), crossProdMatT.getCol1() ) +
			mulPerElem( crossProdMatT.getCol2(), crossProdMatT.getCol2() );

	projOffset = crossProdMatT * offsetAB;
	projAhalf = absPerElem(crossProdMatT) * boxA.m_half;

	PfxVector3 gapsAxB = absPerElem(projOffset) - projAhalf;

	CrossAxisTest( 0, X );
	CrossAxisTest( 1, Y );
	CrossAxisTest( 2, Z );

	// make axis point from box center towards capsule center.

	if ( dot(axisA,offsetAB) < 0.0f )
		axisA = -axisA;

	// find the face on box whose normal best matches the separating axis. will use the entire
	// face only in degenerate cases.
	//
	// to make things simpler later, change the coordinate system so that the face normal is the z
	// direction.  if an edge cross product axis was chosen above, also align the box edge to the y
	// axis.  this saves the later tests from having to know which face was chosen.  changing the
	// coordinate system involves permuting vector elements, so construct a permutation matrix.
	// I believe this is a faster way to permute a bunch of vectors than using arrays.

	int dimA[3];

	if ( axisType == CROSS_AXIS ) {
		PfxVector3 absAxisA = PfxVector3(absPerElem(axisA));

		dimA[1] = edgeDimA;

		if ( edgeDimA == 0 ) {
			if ( absAxisA[1] > absAxisA[2] ) {
				dimA[0] = 2;
				dimA[2] = 1;
			} else                             {
				dimA[0] = 1;
				dimA[2] = 2;
			}
		} else if ( edgeDimA == 1 ) {
			if ( absAxisA[2] > absAxisA[0] ) {
				dimA[0] = 0;
				dimA[2] = 2;
			} else                             {
				dimA[0] = 2;
				dimA[2] = 0;
			}
		} else {
			if ( absAxisA[0] > absAxisA[1] ) {
				dimA[0] = 1;
				dimA[2] = 0;
			} else                             {
				dimA[0] = 0;
				dimA[2] = 1;
			}
		}
	} else {
		dimA[2] = faceDimA;
		dimA[0] = (faceDimA+1)%3;
		dimA[1] = (faceDimA+2)%3;
	}

	PfxMatrix3 aperm_col;

	aperm_col.setCol0(ident[dimA[0]]);
	aperm_col.setCol1(ident[dimA[1]]);
	aperm_col.setCol2(ident[dimA[2]]);

	PfxMatrix3 aperm_row = transpose(aperm_col);

	// permute vectors to be in face coordinate system.

	PfxVector3 offsetAB_perm = aperm_row * offsetAB;
	PfxVector3 halfA_perm = aperm_row * boxA.m_half;
	PfxVector3 signsA_perm = copySignPerElem(PfxVector3(1.0f), aperm_row * axisA);
	PfxVector3 scalesA_perm = mulPerElem( signsA_perm, halfA_perm );
	PfxVector3 capsDirection_perm = aperm_row * capsDirection;
	PfxFloat signB = (-dot(capsDirection,axisA) > 0.0f)? 1.0f : -1.0f;
	PfxFloat scaleB = signB * capsuleB.m_halfLen;

	// compute the vector between the center of the box face and the capsule center

	offsetAB_perm.setZ( offsetAB_perm.getZ() - scalesA_perm.getZ() );

	// if box and capsule overlap, this will separate them for finding points of penetration.

	if ( maxGap < 0.0f ) {
		offsetAB_perm -= aperm_row * axisA * maxGap * 1.01f;
	}

	// for each vertex/face or edge/edge pair of box face and line segment, find the closest
	// points.
	//
	// these points each have an associated feature (vertex, edge, or face).  if each
	// point is in the external Voronoi region of the other's feature, they are the
	// closest points of the objects, and the algorithm can exit.
	//
	// the feature pairs are arranged so that in the general case, the first test will
	// succeed.  degenerate cases (line segment parallel to face) may require up to all tests
	// in the worst case.
	//
	// if for some reason no case passes the Voronoi test, the features with the minimum
	// distance are returned.

	PfxVector3 closestPtsVec_perm;
	PfxPoint3 localPointA_perm;
	PfxFloat minDistSqr;
	PfxFloat segmentParamB;
	PfxBool done;

	localPointA_perm.setZ( scalesA_perm.getZ() );
	scalesA_perm.setZ(0.0f);

	PfxVector3 hA_perm( halfA_perm );

	int otherFaceDimA;

	if ( axisType == CROSS_AXIS ) {
		EdgeEdgeTests( done, minDistSqr, closestPtsVec_perm, localPointA_perm, segmentParamB,
					   otherFaceDimA,
					   hA_perm, capsuleB.m_halfLen, offsetAB_perm, capsDirection_perm, signsA_perm,
					   scalesA_perm, true );

		if ( !done ) {
			VertexBFaceATests( done, minDistSqr, closestPtsVec_perm, localPointA_perm, segmentParamB,
							   hA_perm, offsetAB_perm, capsDirection_perm, signB, scaleB, false );
		}
	} else {
		VertexBFaceATests( done, minDistSqr, closestPtsVec_perm, localPointA_perm, segmentParamB,
						   hA_perm, offsetAB_perm, capsDirection_perm, signB, scaleB, true );

		if ( !done ) {
			EdgeEdgeTests( done, minDistSqr, closestPtsVec_perm, localPointA_perm, segmentParamB,
						   otherFaceDimA,
						   hA_perm, capsuleB.m_halfLen, offsetAB_perm, capsDirection_perm, signsA_perm,
						   scalesA_perm, false );
		}
	}

	// compute normal

	PfxBool centerInside = ( signsA_perm.getZ() * closestPtsVec_perm.getZ() < 0.0f );

	if ( centerInside || ( minDistSqr < lenSqrTol ) ) {
		normal = matrixA * axisA;
	} else {
		PfxVector3 closestPtsVec = aperm_col * closestPtsVec_perm;
		normal = matrixA * ( closestPtsVec * (1.0f/sqrtf( minDistSqr )) );
	}

	// compute box point

	pointA = PfxPoint3( aperm_col * PfxVector3( localPointA_perm ) );

	// compute capsule point

	pointB = PfxPoint3( transpose(transformB.getUpper3x3()) * ( directionB * segmentParamB - normal * capsuleB.m_radius ) );

	if ( centerInside ) {
		return (-sqrtf( minDistSqr ) - capsuleB.m_radius);
	} else {
		return (sqrtf( minDistSqr ) - capsuleB.m_radius);
	}
}