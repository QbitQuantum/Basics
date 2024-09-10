void IGameSystem::UpdateAllSystems( float frametime )
{
	#ifdef USE_FMOD
		//DHL - Skillet - FMOD: Update every frame
		if ( DHLShared::GetFMODSystem() )
		{
			DHLShared::GetFMODSystem()->update();

			//Unfortunately, the change callback functions for the volume CVARs aren't called
			//when they're changed through the VGUI.  Therefore this awful think-based hack is required
			//to update the volume for FMOD stuffs.  Damn.  Hopefully it isn't too expensive.

			//Check for snd_musicvolume changes
			FMOD::ChannelGroup *pBGMusic = DHLShared::GetChannelGroups()->pChanBGMusic;
			int iNumChannels;
			pBGMusic->getNumChannels( &iNumChannels );
			const float flMusicVolInterval = 0.5f, flVolInterval = 1.0f; //Seconds
			//This CVAR only concerns menu music, therefore we only need to update it while at the menu
			if ( iNumChannels > 0 && !engine->IsInGame() )
			{
				static float flNextMusicVolUpdate = gpGlobals->realtime + flMusicVolInterval;
				if ( gpGlobals->realtime >= flNextMusicVolUpdate )
				{
					flNextMusicVolUpdate = gpGlobals->realtime + flMusicVolInterval;
					static ConVar* musicVolume = cvar->FindVar( "snd_musicvolume" );
					static float flLastMusicVolume = musicVolume->GetFloat();
					float flVolume = 0.0f;
					pBGMusic->getVolume( &flVolume );
					if ( flLastMusicVolume != musicVolume->GetFloat() || flLastMusicVolume != flVolume )
					{
						pBGMusic->overrideVolume( musicVolume->GetFloat() );
						flLastMusicVolume = musicVolume->GetFloat();
					}
				}
			}

			//Update volume CVAR
			FMOD::ChannelGroup *pGameMaster = DHLShared::GetChannelGroups()->pChanGameMaster;
			static float flNextVolUpdate = gpGlobals->realtime + flVolInterval;
			if ( gpGlobals->realtime >= flNextVolUpdate )
			{
				flNextVolUpdate = gpGlobals->realtime + flVolInterval;
				static ConVar* Volume = cvar->FindVar( "volume" );
				static float flLastVolume = Volume->GetFloat();
				float flVolume = 0.0f;
				pGameMaster->getVolume( &flVolume );
				if ( flLastVolume != Volume->GetFloat() || flLastVolume != flVolume )
				{
					pGameMaster->setVolume( Volume->GetFloat() );
					flLastVolume = Volume->GetFloat();
				}
			}

			C_DHL_Player* pPlayer = ToDHLPlayer(CBasePlayer::GetLocalPlayer());
			if ( pPlayer )
			{
				Vector vecForward;
				Vector vecUp;
				pPlayer->GetVectors( &vecForward, NULL, &vecUp );

				//Use the actual view position, not origin
				FMOD_VECTOR fmodPos;
				DHLShared::VectorToFMOD( pPlayer->m_vecClientViewPos, &fmodPos );
				/*if ( pPlayer->IsAlive() || pPlayer->GetObserverMode == OBS_MODE_ROAMING )
					DHLShared::VectorToFMOD( pPlayer->GetAbsOrigin(), &fmodPos );
				else
					DHLShared::VectorToFMOD( pPlayer->m_vecClientViewPos, &fmodPos );*/

				FMOD_VECTOR fmodVelocity;
				if ( pPlayer->IsAlive() || pPlayer->GetObserverMode() == OBS_MODE_ROAMING )
					DHLShared::VectorToFMOD( pPlayer->GetAbsVelocity(), &fmodVelocity );
				else
					//Velocity will be invalid while dead and not roaming
					DHLShared::VectorToFMOD( vec3_origin, &fmodVelocity );
					

				FMOD_VECTOR fmodForward;
				DHLShared::VectorToFMOD( vecForward, &fmodForward );

				FMOD_VECTOR fmodUp;
				DHLShared::VectorToFMOD( vecUp, &fmodUp );

				FMOD_RESULT result;
				result = DHLShared::GetFMODSystem()->set3DListenerAttributes( 0, &fmodPos, &fmodVelocity, &fmodForward, &fmodUp );
				DHLShared::HandleFMODError( result );

				if ( dhl_fmod_visualizelistenpos.GetBool() )
				{
					Vector visorigin = vec3_origin;
					DHLShared::FMODToVector( fmodPos, &visorigin );
					char Command[128];
					Q_snprintf( Command, sizeof( Command ), "drawcross %f %f %f \n", visorigin.x, visorigin.y, visorigin.z );
					engine->ClientCmd( Command );
				}
			}
		}
	#endif


	SafeRemoveIfDesiredAllSystems();

	int i;
	int c = s_GameSystemsPerFrame.Count();
	for ( i = 0; i < c; ++i )
	{
		IGameSystemPerFrame *sys = s_GameSystemsPerFrame[i];
		MDLCACHE_CRITICAL_SECTION();
		sys->Update( frametime );
	}
}