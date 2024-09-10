void MeshGeodesic::OptimizePath()
{
	float fDijkstraLength = 0.0f;
	float fLengthBefore = 0.0f;
	size_t nCount1 = m_vDijkstraPath.size();
	if ( nCount1 == 0 )
		return;
	for ( unsigned int i = 0 ; i < nCount1-1; ++i ) 
		fDijkstraLength += (m_vDijkstraPath[i+1].Origin() - m_vDijkstraPath[i].Origin()).Length();
	size_t nCount2 = m_vOptPath.size();
	for ( unsigned int i = 0 ; i < nCount2-1; ++i ) 
		fLengthBefore += (m_vOptPath[i+1].Origin() - m_vOptPath[i].Origin()).Length();


	float fDist, fDist2;
	size_t nCount = m_vOptPath.size();
	for ( unsigned int i = 0; i < nCount-2; ++i ) {
		rms::Frame3f & vCenter = m_vOptPath[i];
		rms::Frame3f & vNext = m_vOptPath[i+1];
		rms::Frame3f & vNext2 = m_vOptPath[i+2];
		float fPathDist = 
			(vNext.Origin() - vCenter.Origin()).Length() +
			(vNext2.Origin() - vNext.Origin()).Length();
		if ( ! _finite(fPathDist) )
			lgBreakToDebugger();

		if ( true || fDijkstraLength - fLengthBefore == 0 ) 
			m_pExpGen->SetSurfaceDistances(vCenter.Origin(), 0.0f, fPathDist * 1.5f, &vCenter );
		else {
			//float fDotThresh = 0.5f;
			//m_pExpGen->ComputeExpMap(vCenter, fPathDist*1.5f, m_vLocalUVs[i], fDotThresh);
		}

		// generate mesh caches
		m_pExpGen->MeshCurrentUVs();

		Wml::Vector2f vUVNext = m_pExpGen->FindUV( vNext.Origin() );
		Wml::Vector2f vUVNext2 = m_pExpGen->FindUV( vNext2.Origin() );
		
		fDist = vUVNext.Length();		
		if ( ! _finite(fDist) ) lgBreakToDebugger();
		vUVNext.Normalize();
		fDist2 = vUVNext2.Length();	
		if ( ! _finite(fDist2) ) lgBreakToDebugger();
		vUVNext2.Normalize();
		Wml::Vector2f vNewUV = vUVNext2 * fDist;

		// save uv
		//m_vLocalUVs[i] = vNewUV;
		//m_vLocalUVs[i].Normalize();

		Wml::Vector3f vNewNorm;
		Wml::Vector3f vNew3D = m_pExpGen->Find3D( vNewUV, &vNewNorm );

		vNext.Origin() = vNew3D;
		vNext.AlignZAxis( vNewNorm );
	}

	// clean point set
	float fCleanerThreshold = 0.02f;
	std::vector<rms::Frame3f> vFrames;
	vFrames.push_back(m_vOptPath.front());
	float fAccumDist = 0.0f;
	for ( unsigned int i = 1; i < nCount; ++i ) {
		rms::Frame3f & vCenter = m_vOptPath[i];
		rms::Frame3f & vPrev = vFrames.back();
		float fDist = (vPrev.Origin() - vCenter.Origin()).Length();
		fAccumDist += fDist;
		if ( fAccumDist < fCleanerThreshold )
			continue;
		fAccumDist = 0.0f;
		vFrames.push_back(vCenter);
	}
	if ( fAccumDist > 0 )
		vFrames.push_back(m_vOptPath.back());
	m_vOptPath = vFrames;

	float fLengthAfter = 0.0f;
	for ( unsigned int i = 0 ; i < nCount2-1; ++i ) 
		fLengthAfter += (m_vOptPath[i+1].Origin() - m_vOptPath[i].Origin()).Length();
	_RMSInfo("DJ: %.5f  BEF: %.5f  AFT: %.5f  DT: %.5f\n",
		fDijkstraLength, fLengthBefore, fLengthAfter, (fLengthAfter-fLengthBefore) );
}