void CZoanthropeAI::Behavior (void)

//	Behavior

	{
	//	Reset

	ResetBehavior();

	//	Behave according to our state

	switch (m_State)
		{
		case stateNone:
			BehaviorStart();
			break;

		case stateAttackingOnPatrol:
			{
			ASSERT(m_pTarget);
			ImplementCombatManeuvers(m_pTarget);
			m_AICtx.ImplementFireOnTargetsOfOpportunity(m_pShip, m_pTarget);

			//	See if we're out of our zone

			Metric rRange = LIGHT_SECOND * GetCurrentOrderData();
			if (CheckOutOfZone(GetCurrentOrderTarget(),
					rRange - PATROL_SENSOR_RANGE,
					rRange + PATROL_SENSOR_RANGE,
					30))
				SetState(stateNone);
			break;
			}

		case stateAttackingThreat:
			{
			ASSERT(m_pTarget);
			ImplementCombatManeuvers(m_pTarget);
			m_AICtx.ImplementFireOnTargetsOfOpportunity(m_pShip, m_pTarget);

			//	Every once in a while check to see if we've wandered too far from
			//	our base.

			if (CheckOutOfRange(GetCurrentOrderTarget(), PATROL_SENSOR_RANGE, 20))
				SetState(stateNone);
			break;
			}

		case stateOnCourseForStargate:
			{
			m_AICtx.ImplementGating(m_pShip, m_pBase);
			m_AICtx.ImplementAttackNearestTarget(m_pShip, ATTACK_RANGE, &m_pTarget);
			m_AICtx.ImplementFireOnTargetsOfOpportunity(m_pShip);
			break;
			}

		case stateOnEscortCourse:
			{
			ASSERT(m_pBase);

			CVector vFlockPos;
			CVector vFlockVel;
			int iFlockFacing;
			if (m_AICtx.CalcFlockingFormation(m_pShip, m_pBase, MAX_FLOCK_DIST, SEPARATION_RANGE, &vFlockPos, &vFlockVel, &iFlockFacing))
				{
				m_AICtx.ImplementFormationManeuver(m_pShip, vFlockPos, vFlockVel, m_pShip->AlignToRotationAngle(iFlockFacing));
				}
			else
				{
				CVector vTarget = m_pBase->GetPos() - m_pShip->GetPos();
				Metric rTargetDist2 = vTarget.Dot(vTarget);

				m_AICtx.ImplementCloseOnTarget(m_pShip, m_pBase, vTarget, rTargetDist2);
				m_AICtx.ImplementAttackNearestTarget(m_pShip, m_AICtx.GetMaxWeaponRange(), &m_pTarget);
				m_AICtx.ImplementFireOnTargetsOfOpportunity(m_pShip);
				}

			//	See if there is anything to attack

			CSpaceObject *pTarget;
			if (CheckForEnemiesInRange(m_pShip, PATROL_SENSOR_RANGE, 30, &pTarget))
				SetState(stateAttackingThreat, m_pBase, pTarget);

			break;
			}

		case stateOnPatrolOrbit:
			{
			ASSERT(m_pBase);

			CVector vFlockPos;
			CVector vFlockVel;
			int iFlockFacing;
			if (m_AICtx.CalcFlockingFormation(m_pShip, NULL, MAX_FLOCK_DIST, SEPARATION_RANGE, &vFlockPos, &vFlockVel, &iFlockFacing))
				{
				m_AICtx.ImplementFormationManeuver(m_pShip, vFlockPos, vFlockVel, m_pShip->AlignToRotationAngle(iFlockFacing));
				}
			else
				{
				m_AICtx.ImplementOrbit(m_pShip, m_pBase, LIGHT_SECOND * GetCurrentOrderData());
				m_AICtx.ImplementAttackNearestTarget(m_pShip, m_AICtx.GetMaxWeaponRange(), &m_pTarget);
				m_AICtx.ImplementFireOnTargetsOfOpportunity(m_pShip);
				}

			//	See if there is anything to attack

			CSpaceObject *pTarget;
			if (CheckForEnemiesInRange(m_pShip, PATROL_SENSOR_RANGE, 30, &pTarget))
				SetState(stateAttackingOnPatrol, m_pBase, pTarget);
			break;
			}

		case stateReturningFromThreat:
			{
			ASSERT(m_pBase);
			m_AICtx.ImplementDocking(m_pShip, m_pBase);
			m_AICtx.ImplementAttackNearestTarget(m_pShip, m_AICtx.GetMaxWeaponRange(), &m_pTarget);
			m_AICtx.ImplementFireOnTargetsOfOpportunity(m_pShip);

			//	See if there is anything to attack

			CSpaceObject *pTarget;
			if (CheckForEnemiesInRange(m_pBase, PATROL_SENSOR_RANGE, 30, &pTarget))
				SetState(stateAttackingThreat, m_pBase, pTarget);
			break;
			}

		case stateWaiting:
			m_AICtx.ImplementStop(m_pShip);

			if (m_pTarget)
				m_AICtx.ImplementAttackTarget(m_pShip, m_pTarget, true);

			m_AICtx.ImplementAttackNearestTarget(m_pShip, m_AICtx.GetMaxWeaponRange(), &m_pTarget);
			m_AICtx.ImplementFireOnTargetsOfOpportunity(m_pShip);
			break;

		case stateWaitingForThreat:
			{
			ASSERT(m_pBase);
			CSpaceObject *pTarget;
			if (CheckForEnemiesInRange(m_pBase, PATROL_SENSOR_RANGE, 30, &pTarget))
				SetState(stateAttackingThreat, m_pBase, pTarget);
			break;
			}
		}
	}