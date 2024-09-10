//-----------------------------------------------------------------------------
// Purpose: Called when an entity stops touching us.
// Input  : pOther - The entity that was touching us.
//-----------------------------------------------------------------------------
void CTriggerWateryDeath::EndTouch( CBaseEntity *pOther )
{
	if ( IsTouching( pOther ) )
	{
		EHANDLE hOther;
		hOther = pOther;

		// Remove the time from our list
		int iIndex = m_hTouchingEntities.Find( hOther );
		if ( iIndex != m_hTouchingEntities.InvalidIndex() )
		{
			m_flEntityKillTimes.Remove( iIndex );
		}
	}

#ifdef HL2_DLL
	if ( pOther->IsPlayer() )
	{
		for (int i = 0; i < m_hLeeches.Count(); i++ )
		{
			CWateryDeathLeech *pLeech = dynamic_cast<CWateryDeathLeech*>( m_hLeeches[i].Get() );

			if ( pLeech )
			{
				pLeech->m_iFadeState = -1;
			}
		}

		if ( m_hLeeches.Count() > 0 )
			 m_hLeeches.Purge();

		CHL2_Player *pHL2Player = dynamic_cast<CHL2_Player*>( pOther );

		if ( pHL2Player )
		{
			//Adrian: Hi, you might be wondering why I'm doing this, yes?
			//        Well, EndTouch is called not only when the player leaves
			//		  the trigger, but also on level shutdown. We can't let the
			//		  soundpatch fade the sound out since we'll hit a nasty assert
			//        cause it'll try to fade out a sound using an entity that might
			//        be gone since we're shutting down the server.
			if ( !(pHL2Player->GetFlags() & FL_DONTTOUCH ) )
				  pHL2Player->StopWaterDeathSounds();
		}
	}
#endif

	BaseClass::EndTouch( pOther );
}