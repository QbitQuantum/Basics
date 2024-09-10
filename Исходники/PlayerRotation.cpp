void CPlayerRotation::ClampAngles()
{
	{
		//cap up/down looking
		float minAngle,maxAngle;
		GetStanceAngleLimits(minAngle,maxAngle);

		float currentViewPitch=GetLocalPitch();
		float newPitch = currentViewPitch + m_deltaAngles.x;

		if(newPitch < minAngle)
			newPitch = minAngle;
		else if(newPitch > maxAngle)
			newPitch = maxAngle;

		m_deltaAngles.x = newPitch - currentViewPitch;

	}

	{
		//further limit the view if necessary
		float limitV = m_params.vLimitRangeV;
		float limitH = m_params.vLimitRangeH;
		Vec3  limitDir = m_params.vLimitDir;
		float limitVUp = m_params.vLimitRangeVUp;
		float limitVDown = m_params.vLimitRangeVDown;

		if(m_player.m_stats.isFrozen.Value())
		{
			float clampMin = g_pGameCVars->cl_frozenAngleMin;
			float clampMax = g_pGameCVars->cl_frozenAngleMax;
			float frozenLimit = DEG2RAD(clampMin + (clampMax-clampMin)*(1.f-m_player.GetFrozenAmount(true)));

			if(limitV == 0 || limitV>frozenLimit)
				limitV = frozenLimit;

			if(limitH == 0 || limitH>frozenLimit)
				limitH = frozenLimit;

			if(g_pGameCVars->cl_debugFreezeShake)
			{
				static float color[] = {1,1,1,1};
				gEnv->pRenderer->Draw2dLabel(100,200,1.5,color,false,"limit: %f", RAD2DEG(frozenLimit));
			}
		}

		if(m_player.m_stats.isOnLadder)
		{
			limitDir = -m_player.m_stats.ladderOrientation;
			limitH = DEG2RAD(40.0f);
		}

		if((limitH+limitV+limitVUp+limitVDown) && limitDir.len2()>0.1f)
		{
			//A matrix is built around the view limit, and then the player view angles are checked with it.
			//Later, if necessary the upVector could be made customizable.
			Vec3 forward(limitDir);
			Vec3 up(m_baseQuat.GetColumn2());
			Vec3 right(-(up % forward));
			right.Normalize();

			Matrix33 limitMtx;
			limitMtx.SetFromVectors(right,forward,right%forward);
			//gEnv->pRenderer->GetIRenderAuxGeom()->DrawLine(m_player.GetEntity()->GetWorldPos(), ColorB(0,0,255,255), m_player.GetEntity()->GetWorldPos() + limitMtx.GetColumn(0), ColorB(0,0,255,255));
			//gEnv->pRenderer->GetIRenderAuxGeom()->DrawLine(m_player.GetEntity()->GetWorldPos(), ColorB(0,255,0,255), m_player.GetEntity()->GetWorldPos() + limitMtx.GetColumn(1), ColorB(0,255,0,255));
			//gEnv->pRenderer->GetIRenderAuxGeom()->DrawLine(m_player.GetEntity()->GetWorldPos(), ColorB(255,0,0,255), m_player.GetEntity()->GetWorldPos() + limitMtx.GetColumn(2), ColorB(255,0,0,255));
			limitMtx.Invert();

			Vec3 localDir(limitMtx * m_viewQuat.GetColumn1());
//			Vec3 localDir(limitMtx * m_player.GetEntity()->GetWorldRotation().GetColumn1());

			Ang3 limit;

			if(limitV)
			{
				limit.x = asinf(localDir.z) + m_deltaAngles.x;

				float deltaX(limitV - fabs(limit.x));

				if(deltaX < 0.0f)
					m_deltaAngles.x += deltaX*(limit.x>0.0f?1.0f:-1.0f);
			}

			if(limitVUp || limitVDown)
			{
				limit.x = asinf(localDir.z) + m_deltaAngles.x;

				if(limit.x>=limitVUp && limitVUp!=0)
				{
					float deltaXUp(limitVUp - limit.x);
					m_deltaAngles.x += deltaXUp;
				}

				if(limit.x<=limitVDown && limitVDown!=0)
				{
					float deltaXDown(limitVDown - limit.x);
					m_deltaAngles.x += deltaXDown;
				}
			}

			if(limitH)
			{
				limit.z = cry_atan2f(-localDir.x,localDir.y) + m_deltaAngles.z;

				float deltaZ(limitH - fabs(limit.z));

				if(deltaZ < 0.0f)
					m_deltaAngles.z += deltaZ*(limit.z>0.0f?1.0f:-1.0f);
			}
		}
	}
}