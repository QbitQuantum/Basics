// called each frame
void CClient :: think ()
{
	extern ConVar bot_cmd_enable_wpt_sounds;

	//if ( m_pPlayer  )
	//	HookGiveNamedItem(m_pPlayer);

	/*if ( m_pPlayer.get() == NULL )
	{
		clientDisconnected();
		return;
	}
	*/

	//if ( m_fMonitorHighFiveTime > engine->Time() )
	//{

	if ( (m_pPlayer != NULL) && (m_pPlayerInfo == NULL) )
	{
		m_pPlayerInfo = playerinfomanager->GetPlayerInfo(m_pPlayer);
	}

	if ( CBotGlobals::isMod(MOD_TF2) )
	{
		if ( (m_fMonitorHighFiveTime < engine->Time()) && (m_pPlayer != NULL) && (m_pPlayerInfo != NULL) && m_pPlayerInfo->IsConnected() && 
			!m_pPlayerInfo->IsDead() && m_pPlayerInfo->IsPlayer() && !m_pPlayerInfo->IsObserver() && 
			CClassInterface::getTF2HighFiveReady(m_pPlayer) )
		{
			m_fMonitorHighFiveTime = engine->Time() + 0.25f;

			if ( CClassInterface::getHighFivePartner(m_pPlayer) == NULL )
			{
				// wanting high five partner
				// search for bots nearby who can see this player
				CBotFunc_HighFiveSearch *newFunc = new CBotFunc_HighFiveSearch(m_pPlayer,CClassInterface::getTeam(m_pPlayer));

				CBots::botFunction(newFunc);

				CBot *pBot = newFunc->getNearestBot();

				if ( pBot != NULL )
				{
					((CBotTF2*)pBot)->highFivePlayer(m_pPlayer,CClassInterface::getTF2TauntYaw(m_pPlayer));
					m_fMonitorHighFiveTime = engine->Time() + 3.0f;
				}				

				delete newFunc;
			}
		}
	}

	if ( m_szSoundToPlay[0] != 0 )
	{
		if ( bot_cmd_enable_wpt_sounds.GetBool() )
			engine->ClientCommand(m_pPlayer,m_szSoundToPlay);

		m_szSoundToPlay[0] = 0;
	}

	if ( m_bIsTeleporting )
	{
		if ( m_fTeleportTime < engine->Time() )
		{
			m_bIsTeleporting = false;
			m_fTeleportTime = 0;
			//reset movetypes
			byte *pMoveType = CClassInterface::getMoveTypePointer(m_pPlayer);
			int *pPlayerFlags = CClassInterface::getPlayerFlagsPointer(m_pPlayer);

			*pMoveType &= ~15;
			*pMoveType |= MOVETYPE_WALK;

			*pPlayerFlags &= ~FL_FLY;
			*pPlayerFlags |= FL_ONGROUND;
		}
	}

	if ( m_bShowMenu )
	{
		m_bShowMenu = false;
		engine->ClientCommand(m_pPlayer,"cancelselect");
	}

	if ( m_pMenu != NULL )
	{
		if ( needToRenderMenu() )
			m_pMenu->render(this);
		//CBotMenuList::render(pClient);
	}

	if ( isWaypointOn() )
		CWaypoints::drawWaypoints(this);

	if ( m_fUpdatePos < engine->Time() )
	{
		m_vVelocity = (getOrigin()-m_vLastPos);
		m_fSpeed = m_vVelocity.Length();
		m_vLastPos = getOrigin();

		if ( (m_fUpdatePos > 0) && (m_fSpeed > 0) )
		{
			if ( !m_bSentWelcomeMessage )
			{
				m_bSentWelcomeMessage = true;

				giveMessage(CStrings::getString(BOT_WELCOME_MESSAGE));

				giveMessage(CStrings::getString(CWaypoints::getWelcomeMessage()),5.0f);
			}
		}

		m_fUpdatePos = engine->Time() + 1.0f;
	}

	if ( isDebugging() )
	{
		IPlayerInfo *p = playerinfomanager->GetPlayerInfo(m_pPlayer);


		if ( isDebugOn(BOT_DEBUG_SPEED) )
		{
			CBotGlobals::botMessage(m_pPlayer,0,"speed = %0.0f",m_fSpeed);
		}

		if ( isDebugOn(BOT_DEBUG_USERCMD) )
		{

			if ( p )
			{
				CBotCmd cmd = p->GetLastUserCommand();

				CBotGlobals::botMessage(m_pPlayer,0,"Btns = %d, cmd_no = %d, impulse = %d, weapselect = %d, weapsub = %d",cmd.buttons,cmd.command_number,cmd.impulse,cmd.weaponselect,cmd.weaponsubtype);

			}
		}


		if ( (m_pDebugBot!=NULL) && isDebugOn(BOT_DEBUG_HUD) )
		{
			if ( m_fNextPrintDebugInfo < engine->Time() )
			{
				char msg[1024];
				CBot *pBot = CBots::getBotPointer(m_pDebugBot);

				QAngle eyes = p->GetLastUserCommand().viewangles;
				Vector vForward;
				// in fov? Check angle to edict
				AngleVectors(eyes,&vForward);

				vForward = vForward / vForward.Length(); // normalize
				Vector vLeft = (vForward-p->GetAbsOrigin()).Cross(Vector(0,0,1));
				vLeft = vLeft/vLeft.Length();
				
				Vector vDisplay = p->GetAbsOrigin() + vForward*300.0f; 
				vDisplay = vDisplay - vLeft*300.0f;

				// get debug message
				pBot->debugBot(msg);

#ifndef __linux__
				int i = 0; 
				int n = 0;
				char line[256];
				int linenum = 0;
				int iIndex = ENTINDEX(m_pDebugBot);

				do
				{
					while ( (msg[i]!=0) && (msg[i]!='\n') ) 
						line[n++] = msg[i++];

					line[n]=0;
					debugoverlay->AddEntityTextOverlay(iIndex,linenum++,1.0f,255,255,255,255,line);
					n = 0;

					if ( msg[i] == 0 )
						break;
					i++;
				}while ( 1 ) ;
				//int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...
			//	debugoverlay->AddEntityTextOverlay();
#endif
				m_fNextPrintDebugInfo = engine->Time() + 1.0f;
			}
		}
			//this->cm_pDebugBot->getTaskDebug();
		//m_pDebugBot->canAvoid();
	}

	if ( m_fNextBotServerMessage < engine->Time() )
	{
		if ( !m_NextTooltip.empty() )
		{
			CToolTip *pTooltip = m_NextTooltip.front();
			
			pTooltip->send(m_pPlayer);

			m_NextTooltip.pop();

			delete pTooltip;

			m_fNextBotServerMessage = engine->Time() + 11.0f;
		}
		else
			m_fNextBotServerMessage = engine->Time() + 1.0f;
	}


	/***** Autowaypoint stuff below borrowed and converted from RCBot1 *****/
	
	if ( m_bAutoWaypoint )
	{
		if ( !m_pPlayerInfo )
			m_pPlayerInfo = playerinfomanager->GetPlayerInfo(m_pPlayer);

		if ( !m_bSetUpAutoWaypoint || !m_pPlayerInfo || m_pPlayerInfo->IsDead() )
		{
			int i;
			int start = 0;

			if ( !m_pPlayerInfo->IsDead() )
				start = 1; // grab one location


			m_fLastAutoWaypointCheckTime = engine->Time() + 0.5f;

			if ( !m_pPlayerInfo->IsDead() )
				m_vLastAutoWaypointCheckPos[0].SetVector(getOrigin());

			for ( i = start; i < MAX_STORED_AUTOWAYPOINT; i++ )
			{
				m_vLastAutoWaypointCheckPos[i].UnSetPoint();
			}

			m_vLastAutoWaypointPlacePos = getOrigin();
			m_bSetUpAutoWaypoint = TRUE;
			m_fCanPlaceJump = 0;
			m_iLastButtons = 0;

			m_iLastJumpWaypointIndex = -1;
			m_iLastLadderWaypointIndex = -1;
			m_iLastMoveType = 0;
			m_fCanPlaceLadder = 0;
			m_iJoinLadderWaypointIndex = -1;
		}
		else
		{			
			int iMoveType = CClassInterface::getMoveType(m_pPlayer);
			int iPlayerFlags = CClassInterface::getPlayerFlags(m_pPlayer);
			CBotCmd cmd = m_pPlayerInfo->GetLastUserCommand();

			Vector vPlayerOrigin = getOrigin();

			// ****************************************************
			// Jump waypoint
			//
			// wait until checkJump is not -1 (meaning that bot is in the air)
			// set checkJump to time+0.5 after landing 
			// 
			// ****************************************************

			if ( m_iAutoEventWaypoint != 0 )
			{
				int iWpt = CWaypointLocations::NearestWaypoint(m_vAutoEventWaypointOrigin,m_fAutoEventWaypointRadius,-1,false,false,false,NULL,false,m_iAutoEventWaypointTeam,false,false,Vector(0,0,0),m_iAutoEventWaypoint);

				CWaypoint *pWpt = CWaypoints::getWaypoint(iWpt);

				if ( !pWpt )
				{
					//updateCurrentWaypoint();

					//pWpt = CWaypoints::getWaypoint(currentWaypoint());
					
					//if ( !pWpt || pWpt->distanceFrom(m_vAutoEventWaypointOrigin) > 32.0f )
					//{

					if ( m_bAutoEventWaypointAutoType )
					{
						CWaypointType *pMainType = CWaypointTypes::getTypeByFlags(m_iAutoEventWaypoint);

						if ( pMainType )
							CWaypoints::addWaypoint(this,pMainType->getName(),"","","");
						else
							CWaypoints::addWaypoint(m_pPlayer,m_vAutoEventWaypointOrigin,(m_iAutoEventWaypointTeam==0)?(m_iAutoEventWaypoint):((m_iAutoEventWaypoint|m_iAutoEventWaypointTeamOn)&~m_iAutoEventWaypointTeamOff),true,cmd.viewangles.y,0,32.0f);
					}
					else
						CWaypoints::addWaypoint(m_pPlayer,m_vAutoEventWaypointOrigin,(m_iAutoEventWaypointTeam==0)?(m_iAutoEventWaypoint):((m_iAutoEventWaypoint|m_iAutoEventWaypointTeamOn)&~m_iAutoEventWaypointTeamOff),true,cmd.viewangles.y,0,32.0f);
					//}
					/*else
					{
						pWpt->addFlag(m_iAutoEventWaypoint);
					}*/
				}

				m_iAutoEventWaypoint = 0;
			}
			//g_pBotManager->GetBotController(m_pPlayer)->IsEFlagSet();

			if ( /*(pev->waterlevel < 3) &&*/ (m_fCanPlaceJump < engine->Time()) )
			{	
				Vector v_floor;

				if ( (m_fCanPlaceJump != -1) && (m_iLastButtons & IN_JUMP) && !(iPlayerFlags & FL_ONGROUND) )
				{
					int iNearestWpt = CWaypointLocations::NearestWaypoint(vPlayerOrigin, 80.0, -1, true, false, false, NULL);

					m_iLastJumpWaypointIndex = -1;
					
					if ( iNearestWpt == -1 )
					{
						m_iLastJumpWaypointIndex = CWaypoints::addWaypoint(m_pPlayer,vPlayerOrigin,CWaypointTypes::W_FL_JUMP,true);
					}
					else
						m_iLastJumpWaypointIndex = iNearestWpt; // can still update a current waypoint for land position
					
					m_vLastAutoWaypointPlacePos = vPlayerOrigin;

					m_fCanPlaceJump = -1;
				}
				// ****************************************************
				// Join jump waypoint to the landed waypoint
				// ****************************************************
				else if ( (m_fCanPlaceJump == -1) && (iPlayerFlags & FL_ONGROUND) )
				{
					if ( m_iLastJumpWaypointIndex != -1 )
					{
						int iNearestWpt = CWaypointLocations::NearestWaypoint(vPlayerOrigin, 80.0, -1, true, false, false, NULL);
						
						if ( iNearestWpt == -1 )
						{
							int iNewWpt = CWaypoints::addWaypoint(m_pPlayer,vPlayerOrigin,0,true);

							if ( iNewWpt != -1 )
							{
								CWaypoint *pWpt = CWaypoints::getWaypoint(iNewWpt);
								CWaypoint *pJumpWpt = CWaypoints::getWaypoint(m_iLastJumpWaypointIndex);

								pJumpWpt->addPathTo(iNewWpt);
				
								pJumpWpt->addFlag(CWaypointTypes::W_FL_JUMP);
								
								trace_t *tr;
								
								Vector v_src = pWpt->getOrigin();

								CBotGlobals::quickTraceline(m_pPlayer,v_src,v_src-Vector(0,0,144));
								
								tr = CBotGlobals::getTraceResult();

								v_floor = tr->endpos;
								float len = v_src.z-tr->endpos.z;
								
								CBotGlobals::quickTraceline(m_pPlayer,v_src,v_src+Vector(0,0,144));
								
								len += (tr->endpos.z-v_src.z);
								
								if ( len > 72 )
								{
									pWpt->removeFlag(CWaypointTypes::W_FL_CROUCH);
									pWpt->move(v_floor+Vector(0,0,36));
								}
								else if ( len > 32 )
								{
									pWpt->addFlag(CWaypointTypes::W_FL_CROUCH);
									pWpt->move(v_floor+Vector(0,0,12));
								}
							}
						}
						else if ( iNearestWpt != m_iLastJumpWaypointIndex )
						{
							CWaypoint *pJumpWpt = CWaypoints::getWaypoint(m_iLastJumpWaypointIndex);

							pJumpWpt->addPathTo(iNearestWpt);
							pJumpWpt->addFlag(CWaypointTypes::W_FL_JUMP);
						}
					}

					m_iLastJumpWaypointIndex = -1;

					// wait a sec after player lands before checking jump again
					m_fCanPlaceJump = engine->Time() + 0.5;
				}				
			}

			bool bCheckDistance = (iMoveType != MOVETYPE_FLY) && (m_fCanPlaceLadder == 0); // always check distance unless ladder climbing

			// ****************************************************
			// Ladder waypoint
			// make the frist waypoint (e.g. bottom waypoint)
			// ****************************************************
			if ( (iMoveType == MOVETYPE_FLY) && !(m_iLastMoveType == MOVETYPE_FLY) )
			{
				// went ON to a ladder

				int iNearestWpt = CWaypointLocations::NearestWaypoint(vPlayerOrigin, 80.0, -1, true, false, false, NULL);

				m_iLastLadderWaypointIndex = -1;
					
				if ( iNearestWpt == -1 )
					m_iLastLadderWaypointIndex = CWaypoints::addWaypoint(m_pPlayer,vPlayerOrigin,CWaypointTypes::W_FL_LADDER,true);
				else
				{
					m_iLastLadderWaypointIndex = iNearestWpt; // can still update a current waypoint for land position

					CWaypoint *pLadderWpt = CWaypoints::getWaypoint(m_iLastLadderWaypointIndex);

					pLadderWpt->addFlag(CWaypointTypes::W_FL_LADDER); // update flags
				}
					
				m_vLastAutoWaypointPlacePos = vPlayerOrigin;

				bCheckDistance = false;

				m_fCanPlaceLadder = 0;

				// need to unset every check point when going on ladder first time
				for ( int i = 0; i < MAX_STORED_AUTOWAYPOINT; i ++ )
				{
						m_vLastAutoWaypointCheckPos[i].UnSetPoint();					
				}
			}
			else if ( !(iMoveType == MOVETYPE_FLY) && (m_iLastMoveType == MOVETYPE_FLY) )
			{
				// went OFF a ladder
				m_fCanPlaceLadder = engine->Time() + 0.2f;
			}
			
			// ****************************************************
			// If we have walked off a ladder for a small amount of time
			// Make the top/bottom ladder waypoint
			// ****************************************************
			if ( m_fCanPlaceLadder && (m_fCanPlaceLadder < engine->Time() ) )
			{
				if ( m_iLastLadderWaypointIndex != -1 )
					// place a ladder waypoint before jumping off
				{
					int iNearestWpt = CWaypointLocations::NearestWaypoint(vPlayerOrigin, 80.0, -1, true, false, false, NULL);
					
					if ( iNearestWpt == -1 )
					{
						int iNewWpt = CWaypoints::addWaypoint(m_pPlayer,vPlayerOrigin,CWaypointTypes::W_FL_LADDER,true);
						
						if ( iNewWpt != -1 )
						{
							CWaypoint *pLadderWpt = CWaypoints::getWaypoint(m_iLastLadderWaypointIndex);

							m_iJoinLadderWaypointIndex = iNewWpt;

							pLadderWpt->addPathTo(iNewWpt);
						}
					}
					else if ( iNearestWpt != m_iLastLadderWaypointIndex )
					{
						CWaypoint *pLadderWpt = CWaypoints::getWaypoint(m_iJoinLadderWaypointIndex);

						m_iJoinLadderWaypointIndex = iNearestWpt;

						pLadderWpt->addPathTo(iNearestWpt);
					}				
				}
				
				m_iLastLadderWaypointIndex = -1;
				
				bCheckDistance = false;

				m_fCanPlaceLadder = 0;
			}
			
			// ****************************************************
			// Join top ladder waypoint to a ground waypoint
			// ****************************************************
			if ( (m_iJoinLadderWaypointIndex != -1) && (iPlayerFlags & FL_ONGROUND) && (iMoveType == MOVETYPE_WALK) )
			{
				int iNearestWpt = CWaypointLocations::NearestWaypoint(vPlayerOrigin, 40.0, m_iJoinLadderWaypointIndex, true, false, false, NULL);
				
				if ( iNearestWpt == -1 )
				{
					int iNewWpt = CWaypoints::addWaypoint(m_pPlayer,vPlayerOrigin,0,true);
					
					if ( iNewWpt != -1 )
					{
						CWaypoint *pLadderWpt = CWaypoints::getWaypoint(m_iJoinLadderWaypointIndex);

						pLadderWpt->addPathTo(iNewWpt);
					}
				}
				else if ( iNearestWpt != m_iJoinLadderWaypointIndex )
				{
					CWaypoint *pLadderWpt = CWaypoints::getWaypoint(m_iJoinLadderWaypointIndex);

					pLadderWpt->addPathTo(iNearestWpt);
				}

				m_iJoinLadderWaypointIndex = -1;
			}

			m_iLastButtons = cmd.buttons;
			m_iLastMoveType = iMoveType;

			if ( m_fLastAutoWaypointCheckTime < engine->Time() )
			{
				// ****************************************
				// Corner - Check
				// ****************************************
				//
				// place a "Check - point" at player origin
				//

				CAutoWaypointCheck *vCurVector;				
				Vector vCheckOrigin;

				Vector vPlacePosition;
				int iFlags = 0;
				bool bPlace = false;
				
				int i;
				int n;

				trace_t *tr;

				int numset = 0;
				int last = 0;

				for ( n = 0; n < MAX_STORED_AUTOWAYPOINT; n ++ )
				{
					if ( m_vLastAutoWaypointCheckPos[n].IsVectorSet() )
					{
						numset++;
					}
				}

				if ( numset == MAX_STORED_AUTOWAYPOINT )
				{
					// move check points down
					for ( n = 0; n < (MAX_STORED_AUTOWAYPOINT-1); n ++ )
					{
						m_vLastAutoWaypointCheckPos[n] = m_vLastAutoWaypointCheckPos[n+1];						
					}
					
					last = MAX_STORED_AUTOWAYPOINT-1;
				}
				else
				{					
					last = numset;
				}

				iFlags = 0;

				// sort out flags for this waypoint depending on player
				if ((iPlayerFlags & FL_DUCKING) == FL_DUCKING)
				{
					iFlags |= CWaypointTypes::W_FL_CROUCH;  // crouching waypoint
				}
				
				if (iMoveType == MOVETYPE_LADDER)
					iFlags |= CWaypointTypes::W_FL_LADDER;  // waypoint on a ladder

				m_vLastAutoWaypointCheckPos[last].SetPoint(vPlayerOrigin,iFlags);
				
				if ( (m_iLastJumpWaypointIndex==-1) && bCheckDistance && ((vPlayerOrigin - m_vLastAutoWaypointPlacePos).Length() > 200) )
				{
					extern ConVar rcbot_autowaypoint_dist;
					int iNearestWpt = CWaypointLocations::NearestWaypoint(vPlayerOrigin, rcbot_autowaypoint_dist.GetFloat(), -1, true, false, false, NULL);
					
					if ( iNearestWpt == -1 )
						CWaypoints::addWaypoint(this,"","","","");
					
					// set regardless
					m_vLastAutoWaypointPlacePos = vPlayerOrigin;
				}

				// search for occluded check points from player
				for ( i = 0; i < MAX_STORED_AUTOWAYPOINT; i++ )
				{
					vCurVector = &m_vLastAutoWaypointCheckPos[i];

					if ( !vCurVector->IsVectorSet() )
						continue;

					vCheckOrigin = vCurVector->GetVector();

					CBotGlobals::quickTraceline(m_pPlayer,vPlayerOrigin,vCheckOrigin);
					tr = CBotGlobals::getTraceResult();

#ifndef __linux__
					if ( m_bDebugAutoWaypoint && !engine->IsDedicatedServer() )
					{
						debugoverlay->AddLineOverlay(vCheckOrigin+Vector(0,0,16),vCheckOrigin-Vector(0,0,16),255,255,255,0,2);
						debugoverlay->AddLineOverlay(vPlayerOrigin,vCheckOrigin,255,255,255,0,2);
					}
#endif					
					if ( tr->fraction < 1.0 )
					{
						if ( tr->m_pEnt )
						{
							Vector vel;
							extern IServerGameEnts *servergameents;
							edict_t *pEdict = servergameents->BaseEntityToEdict(tr->m_pEnt);

							if ( CClassInterface::getVelocity(pEdict,&vel) )
							{
								// on a lift/train moving "fast"
								if ( vel.Length() > 20.0 )
									continue;
							}
						}
						// find next which is visible
						for ( n = i+1; n < MAX_STORED_AUTOWAYPOINT; n++ )
						{
							vCurVector = &m_vLastAutoWaypointCheckPos[n];
							
							if ( !vCurVector->IsVectorSet() )
								continue;
							
							vCheckOrigin = vCurVector->GetVector();

							CBotGlobals::quickTraceline(m_pPlayer,vPlayerOrigin,vCheckOrigin);
			
#ifndef __linux__
							if ( m_bDebugAutoWaypoint )
								debugoverlay->AddLineOverlay(vPlayerOrigin,vCheckOrigin,255,255,255,false,2);
#endif							
							if ( tr->fraction >= 1.0 )
							{
								int iNearestWpt = CWaypointLocations::NearestWaypoint(vCheckOrigin, 100.0, -1, true, false, false, NULL);
								
								if ( iNearestWpt == -1 )
								{
									bPlace = true;		
									vPlacePosition = vCheckOrigin;
									iFlags = vCurVector->getFlags();
									
									break;
								}
								else
									continue;
							}
						}
						
					}
				}

				if ( bPlace )
				{
					int inewwpt = CWaypoints::addWaypoint(m_pPlayer,vPlacePosition,iFlags,true);
					CWaypoint *pWpt = CWaypoints::getWaypoint(inewwpt);
					Vector v_floor;

					m_vLastAutoWaypointPlacePos = vPlacePosition;
					bool bCanStand;

					trace_t *tr;
					
					Vector v_src = vPlacePosition;

					CBotGlobals::quickTraceline(m_pPlayer,v_src,v_src-Vector(0,0,144));
					
					tr = CBotGlobals::getTraceResult();

					v_floor = tr->endpos;
					float len = v_src.z-tr->endpos.z;
					
					CBotGlobals::quickTraceline(m_pPlayer,v_src,v_src+Vector(0,0,144));
					
					len += (tr->endpos.z-v_src.z);
					
					bCanStand = ( len > 72 );

					if ( (m_iLastJumpWaypointIndex != -1) && bCanStand )
					{
						pWpt->removeFlag(CWaypointTypes::W_FL_CROUCH);
						//waypoints[inewwpt].origin = v_floor+Vector(0,0,36);
					}
					//clear from i

					int pos = n;
					int n = 0;

					for ( n = 0; pos < MAX_STORED_AUTOWAYPOINT; n ++ )
					{
						m_vLastAutoWaypointCheckPos[n] = m_vLastAutoWaypointCheckPos[pos];

						pos++;
					}

					for ( n = n; n < MAX_STORED_AUTOWAYPOINT; n ++ )
					{
						m_vLastAutoWaypointCheckPos[n].UnSetPoint();					
					}
				}

				m_fLastAutoWaypointCheckTime = engine->Time() + 0.5f;
			}
		}
	}
}