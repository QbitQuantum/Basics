void CLocusBeam::Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )
{
	CBaseEntity *pStartEnt;
	CBaseEntity *pEndEnt;
	Vector vecStartPos;
	Vector vecEndPos;
	CBeam *pBeam;

	switch(pev->impulse)
	{
	case 0: // ents
		pStartEnt = UTIL_FindEntityByTargetname(NULL, STRING(m_iszStart), pActivator);
		pEndEnt = UTIL_FindEntityByTargetname(NULL, STRING(m_iszEnd), pActivator);

		if (pStartEnt == NULL || pEndEnt == NULL)
			return;
		pBeam = CBeam::BeamCreate( STRING(m_iszSprite), m_iWidth );
		pBeam->EntsInit( pStartEnt->entindex(), pEndEnt->entindex() );
		break;

	case 1: // pointent
		vecStartPos = CalcLocus_Position( this, pActivator, STRING(m_iszStart) );
		pEndEnt = UTIL_FindEntityByTargetname(NULL, STRING(m_iszEnd), pActivator);

		if (pEndEnt == NULL)
			return;
		pBeam = CBeam::BeamCreate( STRING(m_iszSprite), m_iWidth );
		pBeam->PointEntInit( vecStartPos, pEndEnt->entindex() );
		break;
	case 2: // points
		vecStartPos = CalcLocus_Position( this, pActivator, STRING(m_iszStart) );
		vecEndPos = CalcLocus_Position( this, pActivator, STRING(m_iszEnd) );

		pBeam = CBeam::BeamCreate( STRING(m_iszSprite), m_iWidth );
		pBeam->PointsInit( vecStartPos, vecEndPos );
		break;
	case 3: // point & offset
		vecStartPos = CalcLocus_Position( this, pActivator, STRING(m_iszStart) );
		vecEndPos = CalcLocus_Velocity( this, pActivator, STRING(m_iszEnd) );

		pBeam = CBeam::BeamCreate( STRING(m_iszSprite), m_iWidth );
		pBeam->PointsInit( vecStartPos, vecStartPos + vecEndPos );
		break;
	}
	pBeam->SetColor( pev->rendercolor.x, pev->rendercolor.y, pev->rendercolor.z );
	pBeam->SetBrightness( pev->renderamt );
	pBeam->SetNoise( m_iDistortion );
	pBeam->SetFrame( m_fFrame );
	pBeam->SetScrollRate( m_iScrollRate );
	pBeam->SetFlags( m_iFlags );
	pBeam->pev->dmg = m_fDamage;
	pBeam->pev->frags = m_iDamageType;
	pBeam->pev->spawnflags |= pev->spawnflags & (SF_BEAM_RING |
			SF_BEAM_SPARKSTART | SF_BEAM_SPARKEND | SF_BEAM_DECALS);
	if (m_fDuration)
	{
		pBeam->SetThink(&CBeam:: SUB_Remove );
		pBeam->SetNextThink( m_fDuration );
	}
	pBeam->pev->targetname = m_iszTargetName;

	if (pev->target)
	{
		FireTargets( STRING(pev->target), pBeam, this, USE_TOGGLE, 0 );
	}
}