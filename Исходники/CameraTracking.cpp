void CCameraTracking::UpdateAutoFollow(const SViewParams &viewParams, const CPlayer &hero)
{
	if(g_pGameCVars->cl_cam_auto_follow_rate > 0.0f) //auto-tracking
	{
		//if there is an obstacle nearby, don't try to rotate into it
		float lastObstacleDist = (m_vLastObstaclePos - viewParams.position).len();

		if(lastObstacleDist < g_fAutoTrackObstacleDistance)
			return;

		if(hero.GetActorStats()->speedFlat < g_pGameCVars->cl_cam_auto_follow_movement_speed)
		{
			//only rotate when player moves
			m_fAutoRotateSpeed = 0.0f;
			return;
		}

		//get camera direction
		Vec3 camDir = -m_pCamRayScan->GetRayDir(eRAY_CENTER);
		camDir.z = 0.0f;
		camDir.Normalize();
		//get Player direction
		Vec3 heroDirection = (hero.GetAnimatedCharacter()->GetAnimLocation().q * FORWARD_DIRECTION);

		//compute angle between directions
		float dt = camDir.Dot(heroDirection);
		dt = clamp(dt, -1.0f, 1.0f);
		float angle = cry_acosf(dt);

		//check angle being bigger than threshold
		if(angle > g_pGameCVars->cl_cam_auto_follow_threshold)
		{
			float moveSpeed = max(0.002f, gf_PI*m_fFrameTime*g_pGameCVars->cl_cam_auto_follow_rate);
			m_fAutoRotateSpeed = InterpolateTo(max(0.002f, m_fAutoRotateSpeed), moveSpeed, 0.2f);

			//compute rotation direction by taking height part of cross-prod
			float dirVal = camDir.x * heroDirection.y - camDir.y * heroDirection.x;

			CCameraInputHelper *const pCamHelper = hero.GetCameraInputHelper();
			CRY_ASSERT(pCamHelper);

			if(dirVal > 0) //rotate right
				pCamHelper->SetTrackingDelta(-m_fAutoRotateSpeed, 0.0f);
			else //rotate left
				pCamHelper->SetTrackingDelta(m_fAutoRotateSpeed, 0.0f);
		}
		else
			m_fAutoRotateSpeed = 0.0f;
	}
}