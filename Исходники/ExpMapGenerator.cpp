void ExpMapGenerator::PropagateFrameFromNearest_Average( ExpMapParticle * pParticle )
{
	ExpMapParticle * pNearest = pParticle->NearestParticle();

	if ( pParticle->SurfaceDistance() == 0.0f )  {
		// pathological case where seed point == input point (or other duplicate points)
		pParticle->SurfaceVector() = pNearest->SurfaceVector();
		return;
	}

	static std::vector<NbrInfo> vNbrs;
	ExtPlane3f vTangentPlane;
	Frame3f vCenterWorldFrame;
	Wml::Matrix2f matFrameRotate;

	float fWeightSum = 0.0f;
	vNbrs.resize(0);

	//! need to look for nearest particle, because if it is seed
	//! point, it's not in nbr lists...
	if ( pNearest->State() != ExpMapParticle::Frozen )
		lgBreakToDebugger();

	bool bSawNearest = false;
	ExpMapParticle::ListEntry * pCurNbr = GetNeighbourList(pParticle);
	while ( pCurNbr != NULL ) {

		ExpMapParticle * pCenterParticle = pCurNbr->pParticle;
		if ( pCenterParticle == pNearest )
			bSawNearest = true;

		if ( pCenterParticle->State() == ExpMapParticle::Frozen ) {
			PrecomputePropagationData( pCenterParticle, vTangentPlane, vCenterWorldFrame, matFrameRotate );

			NbrInfo info;
			info.vNbrUV = ComputeSurfaceVector( pCenterParticle, pParticle, 
				vTangentPlane, vCenterWorldFrame, matFrameRotate );

			if ( ! _finite(info.vNbrUV.Length()) )
				lgBreakToDebugger();

			info.fNbrWeight = 1.0f / ( ( pCenterParticle->Position() - pParticle->Position() ).Length() + (0.00001f*m_fMaxEdgeLength) );
			if ( ! _finite(info.fNbrWeight) )
				lgBreakToDebugger();

			// weight by geodesic delta - tries to avoid bias from neigbours w/ same "time-of-arrival" (ie at same front-timestep)
			// [RMS: not sure if this has a significant effect - note that need to enable below as well....
			// [RMS] also this is broken for particles at the same 3D position, which seems to happen w/ surface tree...
			//float fGeoDelta = fabs(pCenterParticle->SurfaceVector().Length() - info.vNbrUV.Length());
			//info.fNbrWeight *= fGeoDelta;

			fWeightSum += info.fNbrWeight;

			vNbrs.push_back(info);
		}

		pCurNbr = pCurNbr->pNext;
	}

	if ( ! _finite(fWeightSum) )
		lgBreakToDebugger();

	// add un-seen "nearest" particle
	if ( ! bSawNearest ) {
		PrecomputePropagationData( pNearest, vTangentPlane, vCenterWorldFrame, matFrameRotate );
		NbrInfo info;
		info.vNbrUV =  ComputeSurfaceVector( pNearest, pParticle, 
				vTangentPlane, vCenterWorldFrame, matFrameRotate );

		info.fNbrWeight = 1.0f / ( ( pNearest->Position() - pParticle->Position() ).Length() + (0.00001f*m_fMaxEdgeLength) );

		// weight by geo delta
		//float fGeoDelta = fabs(pNearest->SurfaceVector().Length() - info.vNbrUV.Length());
		//info.fNbrWeight *= fGeoDelta;

		fWeightSum += info.fNbrWeight;
		vNbrs.push_back(info);
	}

	if ( ! _finite(fWeightSum) )
		lgBreakToDebugger();

	// take weighted average to get real UV
	Wml::Vector2f vUV = Wml::Vector2f::ZERO;
	size_t nCount = vNbrs.size();
	for ( unsigned int i = 0; i < nCount; ++i ) {
		float fWeight = vNbrs[i].fNbrWeight / fWeightSum;
		vUV += fWeight * vNbrs[i].vNbrUV;
	}

	if ( ! _finite(vUV.Length()) )
		lgBreakToDebugger();

	pParticle->SurfaceVector() = vUV;


	// check error and re-set distance if it is too high
#if 1
	float fVecLengthSqr = pParticle->SurfaceVector().SquaredLength();
	float fError = fabs(
		fVecLengthSqr / (pParticle->SurfaceDistance()*pParticle->SurfaceDistance()) - 1.0f );
	static const float s_fMaxErr = 2*0.5f - 0.5f*0.5f;		// 0.5f == 50% - arbitrary threshold...
	if ( fError > s_fMaxErr ) {
		if ( true ) {
			pParticle->SurfaceVector().Normalize();
			pParticle->SurfaceVector() *= pParticle->SurfaceDistance();
//			_RMSInfo("Fix!\n");
		}
	}
#endif

}