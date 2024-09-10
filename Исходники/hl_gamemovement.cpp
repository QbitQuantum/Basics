//-----------------------------------------------------------------------------
// Purpose: 
// Input  : mounting - 
//			transit_speed - 
//			goalpos - 
//			*ladder - 
//-----------------------------------------------------------------------------
void CHL2GameMovement::StartForcedMove( bool mounting, float transit_speed, const Vector& goalpos, CFuncLadder *ladder )
{
	LadderMove_t* lm = GetLadderMove();
	Assert( lm );
	// Already active, just ignore
	if ( lm->m_bForceLadderMove )
	{
		return;
	}

#if !defined( CLIENT_DLL )
	if ( ladder )
	{
		ladder->PlayerGotOn( GetHL2Player() );

		// If the Ladder only wants to be there for automount checking, abort now
		if ( ladder->DontGetOnLadder() )
			return;
	}
		
	// Reserve goal slot here
	bool valid = false;
	lm->m_hReservedSpot = CReservePlayerSpot::ReserveSpot( 
		player, 
		goalpos, 
		GetPlayerMins( ( player->GetFlags() & FL_DUCKING ) ? true : false ), 
		GetPlayerMaxs( ( player->GetFlags() & FL_DUCKING ) ? true : false ), 
		valid );
	if ( !valid )
	{
		// FIXME:  Play a deny sound?
		if ( lm->m_hReservedSpot )
		{
			UTIL_Remove( lm->m_hReservedSpot );
			lm->m_hReservedSpot = NULL;
		}
		return;
	}
#endif

	// Use current player origin as start and new origin as dest
	lm->m_vecGoalPosition	= goalpos;
	lm->m_vecStartPosition	= mv->m_vecAbsOrigin;

	// Figure out how long it will take to make the gap based on transit_speed
	Vector delta = lm->m_vecGoalPosition - lm->m_vecStartPosition;

	float distance = delta.Length();
	
	Assert( transit_speed > 0.001f );

	// Compute time required to move that distance
	float transit_time = distance / transit_speed;
	if ( transit_time < 0.001f )
	{
		transit_time = 0.001f;
	}

	lm->m_bForceLadderMove	= true;
	lm->m_bForceMount		= mounting;

	lm->m_flStartTime		= gpGlobals->curtime;
	lm->m_flArrivalTime		= lm->m_flStartTime + transit_time;

	lm->m_hForceLadder		= ladder;

	// Don't get stuck during this traversal since we'll just be slamming the player origin
	player->SetMoveType( MOVETYPE_NONE );
	player->SetMoveCollide( MOVECOLLIDE_DEFAULT );
	player->SetSolid( SOLID_NONE );
	SetLadder( ladder );

	// Debounce the use key
	SwallowUseKey();
}