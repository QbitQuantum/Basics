void CGenericMonster::MakeGas( void )
{
	Vector posGun, angleGun;
	TraceResult tr;
	UTIL_MakeVectors( pev->angles );
	{
	KillGas();
		m_pBeam = CBeam::BeamCreate( "sprites/laserbeam.spr", 7 );
		if ( m_pBeam )
		{
			GetAttachment( 4, posGun, angleGun );
			GetAttachment( 3, posGun, angleGun );

			Vector vecEnd = (gpGlobals->v_forward * 5) + posGun;
			UTIL_TraceLine( posGun, vecEnd, dont_ignore_monsters, edict(), &tr );

			m_pBeam->EntsInit( edict(), edict() );
			m_pBeam->SetColor( 24, 121, 239 );
			m_pBeam->SetBrightness( 190 );
		         	m_pBeam->SetScrollRate( 20 );
			m_pBeam->SetStartAttachment( 4 );
			m_pBeam->SetEndAttachment( 3 );
			m_pBeam->DamageDecal( 28 );
			m_pBeam->DoSparks( tr.vecEndPos, posGun );
			m_pBeam->SetFlags( FBEAM_SHADEIN );
			m_pBeam->RelinkBeam();

			UTIL_Sparks( tr.vecEndPos );
			UTIL_DecalTrace(&tr, 28 + RANDOM_LONG(0,4));
		}
	}
	// m_flNextAttack = gpGlobals->time + RANDOM_FLOAT( 0.5, 4.0 );
	if ( int gas = 1 )
	{
		pev->nextthink = gpGlobals->time;
	}
}