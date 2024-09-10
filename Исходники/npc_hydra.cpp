void CNPC_Hydra::RunTask( const Task_t *pTask )
{
	switch( pTask->iTask )
	{
	case TASK_HYDRA_DEPLOY:
		{
			m_flHeadGoalInfluence = 1.0;
			float dist = (EyePosition() - m_vecHeadGoal).Length();

			if (dist < m_idealSegmentLength)
			{
				TaskComplete();
			}

			AimHeadInTravelDirection( 0.2 );
		}
		break;

	case TASK_HYDRA_PREP_STAB:
		{
			int i;

			if (m_body.Count() < 2)
			{
				TaskFail( "hydra is too short to begin stab" );
				return;
			}

			CBaseEntity *pTarget = GetTarget();
			if (pTarget == NULL)
			{
				TaskFail( FAIL_NO_TARGET );
			}

			if (pTarget->IsPlayer())
			{
				m_vecTarget = pTarget->EyePosition( );
			}
			else
			{
				m_vecTarget = pTarget->BodyTarget( EyePosition( ) );
			}

			float distToTarget = (m_vecTarget - m_vecHeadGoal).Length();
			float distToBase = (m_vecHeadGoal - GetAbsOrigin()).Length();
			m_idealLength = distToTarget + distToBase * 0.5;

			if (m_idealLength > HYDRA_MAX_LENGTH)
				m_idealLength = HYDRA_MAX_LENGTH;

			if (distToTarget < 100.0)
			{
				m_vecTargetDir = (m_vecTarget - m_vecHeadGoal);
				VectorNormalize( m_vecTargetDir );
				m_vecHeadGoal = m_vecHeadGoal - m_vecTargetDir * (100 - distToTarget) * 0.5;
			}
			else if (distToTarget > 200.0)
			{
				m_vecTargetDir = (m_vecTarget - m_vecHeadGoal);
				VectorNormalize( m_vecTargetDir );
				m_vecHeadGoal = m_vecHeadGoal - m_vecTargetDir * (200.0 - distToTarget) * 0.5;
			}

			// face enemy
			m_vecTargetDir = (m_vecTarget - m_body[m_body.Count()-1].vecPos);
			VectorNormalize( m_vecTargetDir );
			m_vecHeadDir = m_vecHeadDir * 0.6 + m_vecTargetDir * 0.4;
			VectorNormalize( m_vecHeadDir.GetForModify() );

			// build tension towards strike time
			float influence = 1.0 - (m_flTaskEndTime - gpGlobals->curtime) / pTask->flTaskData;
			if (influence > 1)
				influence = 1.0;

			influence = influence * influence * influence;

			m_flHeadGoalInfluence = influence;

			// keep head segment straight
			i = m_body.Count() - 2;
			m_body[i].vecGoalPos = m_vecHeadGoal - m_vecHeadDir * m_body[i].flActualLength;
			m_body[i].flGoalInfluence = influence;

			// curve neck into spiral
			float distBackFromHead = m_body[i].flActualLength;
			Vector right, up;
			VectorVectors( m_vecHeadDir, right, up );

			for (i = i - 1; i > 1 && distBackFromHead < distToTarget; i--)
			{
				distBackFromHead += m_body[i].flActualLength;

				float r = (distBackFromHead / 200) * 3.1415 * 2;

				// spiral
				Vector p0 = m_vecHeadGoal 
							- m_vecHeadDir * distBackFromHead * 0.5 
							+ cos( r ) * m_body[i].flActualLength * right 
							+ sin( r ) * m_body[i].flActualLength * up;

				// base
				r = (distBackFromHead / m_idealLength) * 3.1415 * 0.2;
				r = sin( r );
				p0 = p0 * (1 - r) + r * GetAbsOrigin();

				m_body[i].vecGoalPos = p0;

				m_body[i].flGoalInfluence = influence * (1.0 - (distBackFromHead / distToTarget));

				/*
				if ( (pEnemy->EyePosition( ) - m_body[i].vecPos).Length() < distBackFromHead)
				{
					if ( gpGlobals->curtime - m_flLastAttackTime > 4.0)
					{
						TaskComplete();
					}
					return;
				}
				*/
			}

			// look to see if any of the goal positions are stuck
			for (i = i; i < m_body.Count() - 1; i++)
			{
				if (m_body[i].bStuck)
				{
					Vector delta = DotProduct( m_body[i].vecGoalPos - m_body[i].vecPos, m_vecHeadDir) * m_vecHeadDir;
					m_vecHeadGoal -= delta * m_body[i].flGoalInfluence;
					break;
				}
			}

			if ( gpGlobals->curtime >= m_flTaskEndTime )
			{
				if (distToTarget < 500)
				{
					TaskComplete( );
					return;
				}
				else
				{
					TaskFail( "target is too far away" );
					return;
				}
			}
		}
		return;

	case TASK_HYDRA_STAB:
		{
			int i;

			if (m_body.Count() < 2)
			{
				TaskFail( "hydra is too short to begin stab" );
				return;
			}

			if (m_flTaskEndTime <= gpGlobals->curtime)
			{
				TaskComplete( );
				return;
			}

			m_flHeadGoalInfluence = 1.0;

			// face enemy
			//m_vecHeadDir = (pEnemy->EyePosition( ) - m_body[m_body.Count()-1].vecPos);
			//VectorNormalize( m_vecHeadDir.GetForModify() );

			// keep head segment straight
			i = m_body.Count() - 2;
			m_body[i].vecGoalPos = m_vecHeadGoal + m_vecHeadDir * m_body[i].flActualLength;
			m_body[i].flGoalInfluence = 1.0;

			Vector vecToTarget = (m_vecTarget - EyePosition( ));

			// check to see if we went past target
			if (DotProduct( vecToTarget, m_vecHeadDir ) < 0.0)
			{
				TaskComplete( );
				return;
			}

			float distToTarget = vecToTarget.Length();
			float distToBase = (EyePosition( ) - GetAbsOrigin()).Length();
			m_idealLength = distToTarget + distToBase;

			/*
			if (distToTarget < 20)
			{
				m_vecHeadGoal = m_vecTarget;
				SetLastAttackTime( gpGlobals->curtime );
				TaskComplete();
				return;
			}
			else
			*/
			{
				// hit enemy
				m_vecHeadGoal = m_vecTarget + m_vecHeadDir * 300;
			}

			if (m_idealLength > HYDRA_MAX_LENGTH)
				m_idealLength = HYDRA_MAX_LENGTH;

			// curve neck into spiral
			float distBackFromHead = m_body[i].flActualLength;
			Vector right, up;
			VectorVectors( m_vecHeadDir, right, up );

#if 1
			for (i = i - 1; i > 1 && distBackFromHead < distToTarget; i--)
			{
				Vector p0 = m_vecHeadGoal - m_vecHeadDir * distBackFromHead * 1.0; 

				m_body[i].vecGoalPos = p0;

				if ((m_vecTarget - m_body[i].vecPos).Length() > distToTarget + distBackFromHead)
				{
					m_body[i].flGoalInfluence = 1.0 - (distBackFromHead / distToTarget);
				}
				else
				{
					m_body[i].vecGoalPos = EyePosition( ) - m_vecHeadDir * distBackFromHead;
					m_body[i].flGoalInfluence = 1.0 - (distBackFromHead / distToTarget);
				}

				distBackFromHead += m_body[i].flActualLength;
			}
#endif
		}
		return;

	case TASK_HYDRA_PULLBACK:
		{
			if (m_body.Count() < 2)
			{
				TaskFail( "hydra is too short to begin stab" );
				return;
			}
			CBaseEntity *pEnemy = (CBaseEntity *)UTIL_GetLocalPlayer();
			if (GetEnemy() != NULL)
			{
				pEnemy = GetEnemy();
			}

			AimHeadInTravelDirection( 0.2 );

			// float dist = (EyePosition() - m_vecHeadGoal).Length();

			if (m_flCurrentLength < m_idealLength + m_idealSegmentLength)
			{
				TaskComplete();
			}
		}
		break;

	default:
		BaseClass::RunTask( pTask );
		break;
	}

}