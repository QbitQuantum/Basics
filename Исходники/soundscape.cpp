// look for dead/spectating players in our volume, to call touch on
void CTriggerSoundscape::PlayerUpdateThink()
{
	int i;
	SetNextThink( gpGlobals->curtime + 0.2 );

	CUtlVector<CBasePlayerHandle> oldSpectators;
	oldSpectators = m_spectators;
	m_spectators.RemoveAll();

	for ( i=1; i <= gpGlobals->maxClients; ++i )
	{
		CBasePlayer *player = UTIL_PlayerByIndex( i );

		if ( !player )
			continue;

		if ( player->IsAlive() )
			continue;

		// if the spectator is intersecting the trigger, track it, and start a touch if it is just starting to touch
		if ( Intersects( player ) )
		{
			if ( !oldSpectators.HasElement( player ) )
			{
				StartTouch( player );
			}
			m_spectators.AddToTail( player );
		}
	}

	// check for spectators who are no longer intersecting
	for ( i=0; i<oldSpectators.Count(); ++i )
	{
		CBasePlayer *player = oldSpectators[i];

		if ( !player )
			continue;

		if ( !m_spectators.HasElement( player ) )
		{
			EndTouch( player );
		}
	}
}