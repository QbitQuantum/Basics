	virtual void ProcessEvent( EFlowEvent event,SActivationInfo *pActInfo )
	{
		switch (event)
		{
			case eFE_Activate:
			{
				// update destination only if dynamic update is enabled. otherwise destination is read on Start/Reset only
				if (m_bActive && IsPortActive(pActInfo, IN_DEST) && GetPortBool(pActInfo, IN_DYN_DEST) == true)
				{
					ReadDestinationPosFromInput( pActInfo );
					if (m_valueType==VT_TIME)
						CalcSpeedFromTimeInput( pActInfo );
				}
				if (m_bActive && IsPortActive(pActInfo, IN_VALUE))
				{
					ReadSpeedFromInput( pActInfo ); 
				}
				if (IsPortActive(pActInfo, IN_START))
				{
					Start( pActInfo );
				}
				if (IsPortActive(pActInfo, IN_STOP))
				{
					pActInfo->pGraph->SetRegularlyUpdated( pActInfo->myID, false );
					if (m_bActive)
					{
						ActivateOutput(pActInfo, OUT_DONE, true);
						m_bActive = false;
					}
					ActivateOutput(pActInfo, OUT_STOP, true);
				}

				// we dont support dynamic change of those inputs
				assert( !IsPortActive(pActInfo, IN_COORDSYS) );
				assert( !IsPortActive(pActInfo, IN_VALUETYPE) );

				break;
			}

			case eFE_Initialize:
			{
				m_bActive = false;
				m_position = ZERO;
				m_coorSys = (ECoordSys)GetPortInt( pActInfo, IN_COORDSYS );
				m_valueType = (EValueType)GetPortInt(pActInfo, IN_VALUETYPE);
				IEntity *pEnt = pActInfo->pEntity;
				if(pEnt)
					m_position = pEnt->GetWorldPos();
				ActivateOutput(pActInfo, OUT_CURRENT, m_position);  // i dont see a sense for this, but lets keep it for now
				pActInfo->pGraph->SetRegularlyUpdated( pActInfo->myID, false );
				break;
			}

			case eFE_Update:
			{
				IEntity *pEnt = pActInfo->pEntity;
			  if (!pEnt)
				{
					pActInfo->pGraph->SetRegularlyUpdated( pActInfo->myID, false );
					break;
				}

				// Use physics velocity updates, unless the entity is parented in another entity space and not rigid.
				IPhysicalEntity* pPhysEnt = pEnt->GetPhysics();
				if( pPhysEnt && (pEnt->GetParent()!=NULL || pPhysEnt->GetType() == PE_STATIC) )
				{
					pPhysEnt = NULL;
				}

				if (m_stopping)
				{
					m_stopping = false;
					pActInfo->pGraph->SetRegularlyUpdated( pActInfo->myID, false );

					if( pPhysEnt == NULL )
					{
						SetPos(pActInfo, m_destination);
					}

					m_bActive = false;
					break;
				}
				
				if (!m_bActive) break;
				float time = gEnv->pTimer->GetFrameStartTime().GetSeconds();
				float timeDifference = time - m_lastFrameTime; 
				m_lastFrameTime = time;

					// note - if there's no physics then this will be the same, but if the platform is moved through physics, then
					//        we have to get back the actual movement - this maybe framerate dependent.
				m_position = pActInfo->pEntity->GetPos();

				// let's compute the movement vector now
				Vec3 oldPosition = m_position;

				if(m_bForceFinishAsTooNear || m_position.IsEquivalent(m_destination, 0.01f))
				{
					m_position = m_destination;
					oldPosition = m_destination;
					ActivateOutput(pActInfo, OUT_DONE, true);
					ActivateOutput(pActInfo, OUT_FINISH, true);
					SetPos(pActInfo, m_position); // for finishing we have to make a manual setpos even if there is physics involved, to make sure the entity will be where it should.
					if (pPhysEnt)
					{
						pe_action_set_velocity setVel;
						setVel.v = ZERO;
						pPhysEnt->Action( &setVel );

						m_stopping = true;
					}
					else
					{
						pActInfo->pGraph->SetRegularlyUpdated( pActInfo->myID, false );
						m_bActive = false;
					}
				}
				else
				{
					Vec3 direction = m_destination - m_position;
					float distance = direction.GetLength();
					Vec3 directionAndSpeed = direction.normalized();

					// ease-area calcs
					float distanceForEaseOutCalc = distance + m_easeOutDistance * EASE_MARGIN_FACTOR;
					if (distanceForEaseOutCalc < m_easeOutDistance)	// takes care of m_easeOutDistance being 0
					{
						directionAndSpeed *= distanceForEaseOutCalc / m_easeOutDistance;
					}
					else  // init code makes sure both eases dont overlap, when the movement is time defined. when it is speed defined, only ease out is applied if they overlap. 
					{
						if (m_easeInDistance>0.f)
						{
							Vec3 vectorFromStart = m_position - m_startPos;
							float distanceFromStart = vectorFromStart.GetLength();
							float distanceForEaseInCalc = distanceFromStart + m_easeInDistance * EASE_MARGIN_FACTOR;
							if (distanceForEaseInCalc < m_easeInDistance)
							{
								directionAndSpeed *= distanceForEaseInCalc / m_easeInDistance;
							}
						}
					}

					directionAndSpeed *= (m_topSpeed * timeDifference);

					if(direction.GetLength() < directionAndSpeed.GetLength())
					{
						m_position = m_destination;
						m_bForceFinishAsTooNear = true;
					}
					else
						m_position += directionAndSpeed;
				}
				ActivateOutput(pActInfo, OUT_CURRENT, m_position);
				if (pPhysEnt == NULL)
				{
					SetPos(pActInfo, m_position);
				}
				else
				{
					pe_action_set_velocity setVel;
					float rTimeStep = timeDifference>0.000001f ? 1.f / timeDifference : 0.0f;
					setVel.v = (m_position - oldPosition) * rTimeStep;  
					pPhysEnt->Action( &setVel );
				}
				break;
			}
		};
	};