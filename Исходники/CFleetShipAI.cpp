void CFleetShipAI::Behavior (void)

//	Behavior

	{
	//	Reset

	ResetBehavior();

	//	Use basic items

	UseItemsBehavior();

	//	Behave according to our state

	switch (m_State)
		{
		case stateNone:
			BehaviorStart();
			break;

		case stateAttackAtWill:
			{
			//	If we don't have a target, find one

			if (m_pTarget == NULL && m_pShip->IsDestinyTime(13))
				m_pTarget = m_pShip->GetNearestEnemy(ATTACK_AT_WILL_RANGE, true);

			//	If we have a target, attack

			if (m_pTarget)
				{
				ImplementAttackTarget(m_pTarget);
				ImplementFireOnTargetsOfOpportunity(m_pTarget);
				}

			//	Otherwise, stay in formation

			else
				{
				ImplementKeepFormation();
				ImplementFireOnTargetsOfOpportunity();
				ImplementFireOnNearestTarget();
				}

			break;
			}

		case stateAttackInFormation:
			{
			bool bInFormation;
			ImplementKeepFormation(&bInFormation);

			//	Fire the primary weapon (most of the time)

			if (bInFormation && mathRandom(1, 3) > 1)
				ImplementFireWeapon();

			//	Decrement counter

			if (m_iCounter > 0)
				{
				if (--m_iCounter == 0)
					{
					SetState(stateKeepFormation);
					m_iCounter = 0;
					}
				}

			break;
			}

		case stateAttackOnPatrol:
			ASSERT(m_pTarget);
			ImplementAttackTarget(m_pTarget);
			ImplementFireOnTargetsOfOpportunity(m_pTarget);

			//	Check to see if we've wandered outside our patrol zone

			if (m_pShip->IsDestinyTime(20))
				{
				CSpaceObject *pCenter = GetCurrentOrderTarget();
				Metric rMaxRange2 = PATROL_ORBIT_DIST + PATROL_SENSOR_RANGE;
				rMaxRange2 = rMaxRange2 * rMaxRange2;
				Metric rMinRange2 = std::max(0.0, PATROL_ORBIT_DIST - PATROL_SENSOR_RANGE);
				rMinRange2 = rMinRange2 * rMinRange2;

				int iTick = m_pShip->GetSystem()->GetTick();
				CVector vRange = pCenter->GetPos() - m_pShip->GetPos();
				Metric rDistance2 = vRange.Dot(vRange);

				//	If we're outside of our patrol range then stop the attack

				if (rDistance2 > rMaxRange2 || rDistance2 < rMinRange2)
					SetState(stateNone);
				}
			break;

		case stateAttackTarget:
			{
			ASSERT(m_pTarget);
			if (m_pTarget->CanMove())
				ImplementAttackTarget(m_pTarget);
			else
				{
				//	Attack the target as best we can

				CVector vTarget = m_pTarget->GetPos() - m_pShip->GetPos();
				Metric rTargetDist2 = vTarget.Dot(vTarget);
				ImplementFireWeaponOnTarget(-1, -1, m_pTarget, vTarget, rTargetDist2);

				//	Maneuver to a proper position near the target

				Metric rRange;
				int iCounterAdj;
				if (m_pAISettings->iCombatStyle == aicombatStandOff)
					{
					rRange = m_rBestWeaponRange / 2.0;
					iCounterAdj = 2;
					}
				else
					{
					rRange = m_rBestWeaponRange / 6.0;
					iCounterAdj = 1;
					}

				if (m_iCounter == 0)
					{
					m_vVector = ComputeAttackPos(m_pTarget, rRange, &m_iAngle);
					m_iCounter = mathRandom(130, 160) * iCounterAdj;
					}
				else
					m_iCounter--;

				ImplementFormationManeuver(m_vVector, NullVector, m_iAngle);
				}

			ImplementFireOnTargetsOfOpportunity(m_pTarget);
			break;
			}

		case stateKeepFormation:
			ImplementKeepFormation();
			ImplementFireOnTargetsOfOpportunity();
			ImplementFireOnNearestTarget();
			break;

		case stateOnCourseForDocking:
			ASSERT(m_pDest);
			ImplementDocking(m_pDest);
			ImplementFireOnTargetsOfOpportunity();
			ImplementFireOnNearestTarget();
			break;

		case stateOnCourseForStargate:
			ASSERT(m_pDest);
			ImplementGating(m_pDest);
			ImplementFireOnTargetsOfOpportunity();
			ImplementFireOnNearestTarget();
			break;

		case stateOnPatrolOrbit:
			ASSERT(m_pDest);
			ImplementOrbit(m_pDest, PATROL_ORBIT_DIST);
			ImplementAttackNearestTarget(m_rMaxWeaponRange, &m_pTarget, m_pDest);
			ImplementFireOnTargetsOfOpportunity(NULL, m_pDest);

			//	Check to see if any enemy ships appear

			if (m_pShip->IsDestinyTime(30))
				{
				CSpaceObject *pPrincipal = GetCurrentOrderTarget();
				CSpaceObject *pTarget = CalcEnemyShipInRange(pPrincipal, PATROL_SENSOR_RANGE, m_pDest);
				if (pTarget)
					{
					SetState(stateAttackOnPatrol);
					m_pTarget = pTarget;
					ASSERT(m_pTarget->DebugIsValid() && m_pTarget->NotifyOthersWhenDestroyed());
					}
				}
			break;
		}
	}