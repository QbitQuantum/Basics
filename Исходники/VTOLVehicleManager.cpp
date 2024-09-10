void CVTOLVehicleManager::Update(float frameTime)
{
	// Update logic goes here
	if(CGameRules* pGameRules = g_pGame->GetGameRules())
	{
		CGameRules::TPlayers players;
		pGameRules->GetPlayers(players);

		for (TVTOLList::iterator iter=m_vtolList.begin(), end=m_vtolList.end(); iter!=end; ++iter)
		{
			SVTOLInfo& info = iter->second;
			IVehicle* pVehicle = m_pVehicleSystem->GetVehicle( info.entityId );
			if(pVehicle)
			{
				info.stateTime += frameTime;

				// Find difference in rotation
				Quat newRotation = pVehicle->GetEntity()->GetWorldRotation();
				newRotation.Normalize();
				Quat rotationDifference = newRotation*info.location.q.GetInverted();
				rotationDifference.Normalize();

				// Store new rotation + position
				info.location.q = newRotation;
				info.location.t = pVehicle->GetEntity()->GetWorldPos();

				if(info.state==EVS_Normal)
				{
					pVehicle->NeedsUpdate(IVehicle::eVUF_AwakePhysics);

					if(CVehicleMovementMPVTOL* pMovement = static_cast<CVehicleMovementMPVTOL*>(pVehicle->GetMovement()))
					{
						const uint8 pathComplete = pMovement->GetPathComplete();
						if(pathComplete==1)
						{
							if(CMPPathFollowingManager* pMPPathFollowingManager = g_pGame->GetGameRules()->GetMPPathFollowingManager())
							{
								pMPPathFollowingManager->NotifyListenersOfPathCompletion(info.entityId);
							}
							pMovement->SetPathCompleteNotified();
						}
					}
				}

				// Check status
				if(info.state==EVS_Normal && pVehicle->GetDamageRatio() >= 1.f)
				{
					if(gEnv->bServer)
					{
						DestructionDamageRatioReached(pVehicle, info, frameTime);
					}
				}
				else if(info.state == EVS_Invisible)
				{
					if(info.stateTime > g_pGameCVars->g_VTOLRespawnTime)
					{
						RespawnVTOL(pVehicle, info);
					}
				}

				//Process players
				TPlayerList& currentPlayerList = info.playersInside;
				TPlayerList oldPlayerList = currentPlayerList;
				currentPlayerList.clear();

				CGameRules::TPlayers::iterator iterPlayer = players.begin();
				const CGameRules::TPlayers::const_iterator endPlayer = players.end();
				while(iterPlayer != endPlayer)
				{
					// Adding safeguard to protect against cases where user alt-f4 quits program. 
					UpdateEntityInVTOL(info, *iterPlayer); 
					++iterPlayer;
				}
				
				//Find out who has been inside since the last update, who has just entered, and who has left
				TPlayerStatusList playerStatusList;
				int currentId;
				for(unsigned int prev = 0; prev < currentPlayerList.size(); ++prev)
				{
					currentId = currentPlayerList[prev];
					bool found = false;
					TPlayerList::iterator oldIter = oldPlayerList.begin();
					TPlayerList::iterator oldEnd = oldPlayerList.end();
					while(oldIter != oldEnd)
					{
						if(currentId == *oldIter) //In both lists so still inside
						{
							found = true;
							playerStatusList.push_back( TPlayerStatus(currentId, E_PEVS_StillInside) );
							oldPlayerList.erase(oldIter);
							break;
						}
						++oldIter;
					}
					if(!found) //Only in current list so entered
					{
						playerStatusList.push_back( TPlayerStatus(currentId, E_PEVS_Entered) );
					}
				}
				//Those remaining in old list have exited
				for(unsigned int old = 0; old < oldPlayerList.size(); ++old) 
				{
					playerStatusList.push_back( TPlayerStatus(oldPlayerList[old], E_PEVS_Exited) );
				}

				//Act based on current state
				TPlayerStatusList::iterator statusIter = playerStatusList.begin();
				TPlayerStatusList::iterator statusEnd = playerStatusList.end();
				while(statusIter != statusEnd)
				{
					switch(statusIter->second)
					{
					case E_PEVS_Entered:
						{
							OnPlayerEntered(statusIter->first);
						}
						break;
					case E_PEVS_Exited:
						{
							OnPlayerExited(statusIter->first);
						}
						break;
					}
					++statusIter;
				}

				UpdateRotationOfInternalPlayers(info, playerStatusList, rotationDifference);
			}
		}
	}
}