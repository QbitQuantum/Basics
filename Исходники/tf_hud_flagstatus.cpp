//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFHudFlagObjectives::OnTick()
{
	// iterate through the flags to set their position in our HUD
	for ( int i = 0; i < g_Flags.Count(); i++ )
	{
		CCaptureFlag *pFlag = dynamic_cast< CCaptureFlag* >( ClientEntityList().GetEnt( g_Flags[i] ) );

		if ( pFlag )
		{
			if (!pFlag->IsDisabled())
			{
				if (m_pRedFlag && pFlag->GetTeamNumber() == TF_TEAM_RED)
				{
					m_pRedFlag->SetEntity(pFlag);
				}
				else if (m_pBlueFlag && pFlag->GetTeamNumber() == TF_TEAM_BLUE)
				{
					m_pBlueFlag->SetEntity(pFlag);
				}
				else if (m_pGreenFlag && pFlag->GetTeamNumber() == TF_TEAM_GREEN)
				{
					m_pGreenFlag->SetEntity(pFlag);
				}
				else if (m_pYellowFlag && pFlag->GetTeamNumber() == TF_TEAM_YELLOW)
				{
					m_pYellowFlag->SetEntity(pFlag);
				}
			}
		}
		else
		{
			// this isn't a valid index for a flag
			g_Flags.Remove( i );
		}
	}

	// are we playing captures for rounds?
	if ( tf_flag_caps_per_round.GetInt() > 0 )
	{
		C_TFTeam *pTeam = GetGlobalTFTeam( TF_TEAM_BLUE );
		if ( pTeam )
		{
			SetDialogVariable( "bluescore", pTeam->GetFlagCaptures() );
		}

		pTeam = GetGlobalTFTeam( TF_TEAM_RED );
		if ( pTeam )
		{
			SetDialogVariable( "redscore", pTeam->GetFlagCaptures() );
		}

		SetPlayingToLabelVisible( true );
		SetDialogVariable( "rounds", tf_flag_caps_per_round.GetInt() );
	}
	else // we're just playing straight score
	{
		C_TFTeam *pTeam = GetGlobalTFTeam( TF_TEAM_BLUE );
		if ( pTeam )
		{
			SetDialogVariable( "bluescore", pTeam->Get_Score() );
		}

		pTeam = GetGlobalTFTeam( TF_TEAM_RED );
		if ( pTeam )
		{
			SetDialogVariable( "redscore", pTeam->Get_Score() );
		}

		SetPlayingToLabelVisible( false );
	}

	// check the local player to see if they're spectating, OBS_MODE_IN_EYE, and the target entity is carrying the flag
	bool bSpecCarriedImage = false;
	C_TFPlayer *pPlayer = C_TFPlayer::GetLocalTFPlayer();
	if ( pPlayer && ( pPlayer->GetObserverMode() == OBS_MODE_IN_EYE ) )
	{
		// does our target have the flag?
		C_BaseEntity *pEnt = pPlayer->GetObserverTarget();
		if ( pEnt && pEnt->IsPlayer() )
		{
			C_TFPlayer *pTarget = static_cast< C_TFPlayer* >( pEnt );
			if ( pTarget->HasTheFlag() )
			{
				bSpecCarriedImage = true;

				CCaptureFlag *pPlayerFlag = dynamic_cast<CCaptureFlag*>(pTarget->GetItem());

				if (m_pSpecCarriedImage)
				{
					switch (pPlayerFlag->GetTeamNumber())
					{
						case TF_TEAM_RED:
							m_pSpecCarriedImage->SetImage(("%s_red", STRING(pPlayerFlag->m_szHudIcon)));
							break;
						case TF_TEAM_BLUE:
							m_pSpecCarriedImage->SetImage(("%s_blue", STRING(pPlayerFlag->m_szHudIcon)));
							break;
						case TF_TEAM_GREEN:
							m_pSpecCarriedImage->SetImage(("%s_green", STRING(pPlayerFlag->m_szHudIcon)));
							break;
						case TF_TEAM_YELLOW:
							m_pSpecCarriedImage->SetImage(("%s_yellow", STRING(pPlayerFlag->m_szHudIcon)));
							break;
					}
				}
			}
		}
	}

	if ( bSpecCarriedImage )
	{
		if ( m_pSpecCarriedImage && !m_pSpecCarriedImage->IsVisible() )
		{
			m_pSpecCarriedImage->SetVisible( true );
		}
	}
	else
	{
		if ( m_pSpecCarriedImage && m_pSpecCarriedImage->IsVisible() )
		{
			m_pSpecCarriedImage->SetVisible( false );
		}
	}
}