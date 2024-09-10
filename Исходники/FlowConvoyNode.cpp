int CFlowConvoyNode::OnPhysicsPostStep(const EventPhys * pEvent)
{
	FUNCTION_PROFILER(GetISystem(), PROFILE_GAME);

  if(m_bFirstUpdate)
    return 0; //after QuickLoad OnPhysicsPostStep called before ProcessEvent

	const EventPhysPostStep *pPhysPostStepEvent = (const EventPhysPostStep *)pEvent;

	IPhysicalEntity *pEventPhysEnt = pPhysPostStepEvent->pEntity;

	Vec3 posBack, posFront, posCenter;

	for (size_t i = 0; i < m_coaches.size(); ++i)
	{
		IPhysicalEntity *pPhysEnt = m_coaches[i].m_pEntity->GetPhysics();

		if (pEventPhysEnt == pPhysEnt)
		{
			if (m_ShiftTime > 0.0f)
			{
				m_speed = m_speed * (1.0f - breakValue * pPhysPostStepEvent->dt / m_MaxShiftTime);
				m_ShiftTime -= pPhysPostStepEvent->dt;
			}
			else
			{
				m_speed = m_speed + min(1.0f, (pPhysPostStepEvent->dt / 5.0f)) * (m_desiredSpeed - m_speed);
			}
		

			float speed = (m_splitCoachIndex > 0 && (int)i >= m_splitCoachIndex) ? m_splitSpeed : m_speed;
			float distance = (m_coaches[i].m_distanceOnPath += pPhysPostStepEvent->dt * speed);
			
			if(m_splitCoachIndex>0)
			{//train splitted
				if(i==m_splitCoachIndex-1) // update m_distanceOnPath for serialization
					m_distanceOnPath=distance-m_coaches[i].m_coachOffset;
				else if(i==m_coaches.size()-1) // update m_splitDistanceOnPath for serialization
					m_splitDistanceOnPath=distance-m_coaches[i].m_coachOffset;
			}
			else
			{//train in one piece
				if(i==m_coaches.size()-1)// update m_distanceOnPath for serialization
					m_distanceOnPath=distance-m_coaches[i].m_coachOffset;
			}

			posBack  = m_path.GetPointAlongPath(distance - m_coaches[i].m_wheelDistance, m_coaches[i].m_backWheelIterator[0]);
			posFront = m_path.GetPointAlongPath(distance + m_coaches[i].m_wheelDistance, m_coaches[i].m_frontWheelIterator[0]);
			posCenter = (posBack+posFront)*0.5f;


			Vec3 posDiff = posFront - posBack;
			float magnitude = posDiff.GetLength();

			if (magnitude > FLT_EPSILON)
			{
				posDiff *= 1.0f / magnitude;

				pe_params_pos ppos;
				ppos.pos = posCenter;
				ppos.q = Quat::CreateRotationVDir(posDiff);
				if (m_bXAxisFwd)
					ppos.q *= Quat::CreateRotationZ(gf_PI*-0.5f);
				pPhysEnt->SetParams(&ppos, 0 /* bThreadSafe=0 */); // as we are calling from the physics thread

				Vec3 futurePositionBack, futurePositionFront;
				futurePositionBack  = m_path.GetPointAlongPath(distance + PATH_DERIVATION_TIME * speed - m_coaches[i].m_wheelDistance, m_coaches[i].m_backWheelIterator[1]);
				futurePositionFront = m_path.GetPointAlongPath(distance + PATH_DERIVATION_TIME * speed + m_coaches[i].m_wheelDistance, m_coaches[i].m_frontWheelIterator[1]);

				Vec3 futurePosDiff = futurePositionFront - futurePositionBack;
				magnitude = futurePosDiff.GetLength();

				if (magnitude > FLT_EPSILON)
				{
					futurePosDiff *= 1.0f / magnitude;

					pe_action_set_velocity setVel;
					setVel.v = ((futurePositionBack+ futurePositionFront)*0.5f - posCenter) * (1.0f/PATH_DERIVATION_TIME);

					//Vec3 dir=(posFront-posBack).GetNormalized();
					//Vec3 future_dir=(futurePositionFront-futurePositionBack).GetNormalized();
					Vec3 w=posDiff.Cross(futurePosDiff);
					float angle=cry_asinf(w.GetLength());
					setVel.w=(angle/PATH_DERIVATION_TIME)*w.GetNormalized();
					pPhysEnt->Action(&setVel, 0 /* bThreadSafe=0 */); // as we are calling from the physics thread
					break;
				}
			}
		}
	}

	// Done processing once we reach end of path
	if (m_atEndOfPath)
		m_processNode = false;

	return 0;
}