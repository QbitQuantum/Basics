LTBOOL AISpatialNeighbor::Init(AISpatialRepresentation* pThis, AISpatialRepresentation* pNeighbor)
{
	m_pVolume = pNeighbor;

	// Compute the 2d intersection of the two volumes, and compute important
	// things about the geometry of the connection

    LTVector vFrontLeft(0,0,0);
    LTVector vFrontRight(0,0,0);
    LTVector vBackLeft(0,0,0);
    LTVector vBackRight(0,0,0);

	vFrontLeft.x = Max<LTFLOAT>(pThis->GetFrontTopLeft().x, pNeighbor->GetFrontTopLeft().x);
	vFrontLeft.z = Min<LTFLOAT>(pThis->GetFrontTopLeft().z, pNeighbor->GetFrontTopLeft().z);

	vFrontRight.x = Min<LTFLOAT>(pThis->GetFrontTopRight().x, pNeighbor->GetFrontTopRight().x);
	vFrontRight.z = Min<LTFLOAT>(pThis->GetFrontTopRight().z, pNeighbor->GetFrontTopRight().z);

	vBackLeft.x = Max<LTFLOAT>(pThis->GetBackTopLeft().x, pNeighbor->GetBackTopLeft().x);
	vBackLeft.z = Max<LTFLOAT>(pThis->GetBackTopLeft().z, pNeighbor->GetBackTopLeft().z);

	vBackRight.x = Min<LTFLOAT>(pThis->GetBackTopRight().x, pNeighbor->GetBackTopRight().x);
	vBackRight.z = Max<LTFLOAT>(pThis->GetBackTopRight().z, pNeighbor->GetBackTopRight().z);

	// We know connection position (the center of the intersection) easily.

	m_vConnectionPos = (vFrontLeft+vFrontRight+vBackLeft+vBackRight)/4.0f;

	// We need y for vertical movement

#define _A_b pThis->GetFrontBottomRight().y
#define _A_t pThis->GetFrontTopRight().y
#define _B_b pNeighbor->GetFrontBottomRight().y
#define _B_t pNeighbor->GetFrontTopRight().y

	if ( (_A_t >= _B_t) && (_A_t >= _B_b) && (_A_b >= _B_t) && (_A_b >= _B_b) )
	{
		m_vConnectionPos.y = _A_b; // or _B_t
	}
	else if ( (_A_t <= _B_t) && (_A_t <= _B_b) && (_A_b <= _B_t) && (_A_b <= _B_b) )
	{
		m_vConnectionPos.y = _A_t; // or _B_b
	}
	else if ( (_A_t >= _B_t) && (_A_t >= _B_b) && (_A_b <= _B_t) && (_A_b >= _B_b) )
	{
		m_vConnectionPos.y = (_A_b + _B_t)/2.0f;
	}
	else if ( (_A_t <= _B_t) && (_A_t >= _B_b) && (_A_b <= _B_t) && (_A_b <= _B_b) )
	{
		m_vConnectionPos.y = (_A_t + _B_b)/2.0f;
	}
	else if ( (_A_t >= _B_t) && (_A_t >= _B_b) && (_A_b <= _B_t) && (_A_b <= _B_b) )
	{
		m_vConnectionPos.y = (_B_b + _B_t)/2.0f;
	}
	else if ( (_A_t <= _B_t) && (_A_t >= _B_b) && (_A_b <= _B_t) && (_A_b >= _B_b) )
	{
		m_vConnectionPos.y = (_A_b + _A_t)/2.0f;
	}
	else
	{
		m_vConnectionPos.y = -float(INT_MAX);
        DANGER(g_pLTServer, blong);
	}

	// Find the endpoints of the line across the connection, and the vector perpendicular to this

	if ( pThis->InsideMasked(pNeighbor->GetFrontTopLeft(), eAxisAll) || pThis->InsideMasked(pNeighbor->GetBackTopRight(), eAxisAll) ||
		 pThis->InsideMasked(pNeighbor->GetFrontBottomLeft(), eAxisAll) || pThis->InsideMasked(pNeighbor->GetBackBottomRight(), eAxisAll) )
	{
        m_avConnectionEndpoints[0] = vFrontRight + LTVector(0, m_vConnectionPos.y, 0);
        m_avConnectionEndpoints[1] = vBackLeft + LTVector(0, m_vConnectionPos.y, 0);
		m_vConnectionPerpDir = vFrontRight - vBackLeft;
		m_vConnectionDir = m_avConnectionEndpoints[1] - m_avConnectionEndpoints[0];
		m_vConnectionDir.y = 0.0f;
		m_fConnectionLength = VEC_MAG(m_vConnectionDir);
		m_vConnectionDir.Normalize();
	}
	else
	{
        m_avConnectionEndpoints[0] = vFrontLeft + LTVector(0, m_vConnectionPos.y, 0);
        m_avConnectionEndpoints[1] = vBackRight + LTVector(0, m_vConnectionPos.y, 0);
		m_vConnectionPerpDir = vFrontLeft - vBackRight;
		m_vConnectionDir = m_avConnectionEndpoints[1] - m_avConnectionEndpoints[0];
		m_vConnectionDir.y = 0.0f;
		m_fConnectionLength = VEC_MAG(m_vConnectionDir);
		m_vConnectionDir.Normalize();
	}

	m_vConnectionMidpoint = m_avConnectionEndpoints[0] + ( m_vConnectionDir * ( m_fConnectionLength * 0.5f ) );

	LTFLOAT fTemp = m_vConnectionPerpDir[0];
	m_vConnectionPerpDir[0] = m_vConnectionPerpDir[2];
	m_vConnectionPerpDir[2] = fTemp;
	m_vConnectionPerpDir.Normalize();

	// Ensure that perp dir is axis-aligned.

	RoundVector( m_vConnectionPerpDir );

	// Make sure it points into this volume

    LTVector vThisCenter = (pThis->GetFrontTopLeft()+pThis->GetBackTopRight())/2.0f;
    LTVector vThisCenterDir = vThisCenter - m_vConnectionPos;
	vThisCenterDir.y = 0;
	vThisCenterDir.Normalize();

	if ( vThisCenterDir.Dot(m_vConnectionPerpDir) < 0.0f )
	{
		m_vConnectionPerpDir = -m_vConnectionPerpDir;
	}

	m_cGates = (uint32)(m_fConnectionLength/48.0f);


	// Check for invalid neighbors.

	if(m_cGates == 0)
	{
		AIError("Volume has Invalid Neighbor %s -> %s. Connection < 48 units!",
			pThis->GetName(), pNeighbor->GetName() );

		return LTFALSE;
	}

	m_vecfGateOccupancy.resize(m_cGates);

	for ( uint32 iGate = 0 ; iGate < m_cGates ; iGate++ )
	{
		m_vecfGateOccupancy[iGate] = 0.0f;
	}

	if(	m_avConnectionEndpoints[0].z == m_avConnectionEndpoints[1].z )
	{
		m_eVolumeConnectionType = eVolumeConnectionTypeHorizontal;

		if( m_pVolume->GetCenter().z < m_vConnectionPos.z )
		{
			m_eVolumeConnectionLocation = eVolumeConnectionLocationFront;
		}
		else {
			m_eVolumeConnectionLocation = eVolumeConnectionLocationBack;
		}
	}
	else
	{
		m_eVolumeConnectionType = eVolumeConnectionTypeVertical;

		if( m_pVolume->GetCenter().x < m_vConnectionPos.x )
		{
			m_eVolumeConnectionLocation = eVolumeConnectionLocationRight;
		}
		else {
			m_eVolumeConnectionLocation = eVolumeConnectionLocationLeft;
		}
	}

	//g_pLTServer->CPrint("cxn @ %f,%f,%f in %f,%f,%f : %f,%f,%f",
	//	EXPANDVEC(m_vConnectionPos), EXPANDVEC(vThisCenter), EXPANDVEC(m_vConnectionPerpDir));

	return LTTRUE;
}