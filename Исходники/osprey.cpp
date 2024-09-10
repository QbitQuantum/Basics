CBaseMonster *COsprey :: MakeGrunt( Vector vecSrc )
{
	CBaseEntity *pEntity;
	CBaseMonster *pGrunt;

	TraceResult tr;
	UTIL_TraceLine( vecSrc, vecSrc + Vector( 0, 0, -4096.0), dont_ignore_monsters, ENT(pev), &tr);
	if ( tr.pHit && Instance( tr.pHit )->pev->solid != SOLID_BSP) 
		return NULL;

	for (int i = 0; i < m_iUnits; i++)
	{
		if (m_hGrunt[i] == NULL || !m_hGrunt[i]->IsAlive())
		{
			if (m_hGrunt[i] != NULL && m_hGrunt[i]->pev->rendermode == kRenderNormal)
			{
				m_hGrunt[i]->SUB_StartFadeOut( );
			}
			pEntity = Create( "monster_human_grunt", vecSrc, GetAbsAngles() );
			pGrunt = pEntity->MyMonsterPointer( );
			pGrunt->pev->movetype = MOVETYPE_FLY;
			pGrunt->SetAbsVelocity( Vector( 0, 0, RANDOM_FLOAT( -196, -128 ) ));
			pGrunt->SetActivity( ACT_GLIDE );

			CBeam *pBeam = CBeam::BeamCreate( "sprites/rope.spr", 10 );
			pBeam->PointEntInit( vecSrc + Vector(0,0,112), pGrunt->entindex() );
			pBeam->SetFlags( BEAM_FSOLID );
			pBeam->SetColor( 255, 255, 255 );
			pBeam->SetThink( SUB_Remove );
			pBeam->pev->nextthink = gpGlobals->time + -4096.0 * tr.flFraction / pGrunt->GetAbsVelocity().z + 0.5;

			// ALERT( at_console, "%d at %.0f %.0f %.0f\n", i, m_vecOrigin[i].x, m_vecOrigin[i].y, m_vecOrigin[i].z );  
			pGrunt->m_vecLastPosition = m_vecOrigin[i];
			m_hGrunt[i] = pGrunt;
			return pGrunt;
		}
	}
	// ALERT( at_console, "none dead\n");
	return NULL;
}