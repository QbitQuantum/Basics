//----------------------------------------------------
void CRocketLauncher::UpdateTPLaser(float frameTime)
{
	m_lastUpdate -= frameTime;

	bool allowUpdate = true;
	if(m_lastUpdate<=0.0f)
		m_lastUpdate = m_Timeout;
	else
		allowUpdate = false;

	const CCamera& camera = gEnv->pRenderer->GetCamera();

	//If character not visible, laser is not correctly updated
	if(CActor* pOwner = GetOwnerActor())
	{
		ICharacterInstance* pCharacter = pOwner->GetEntity()->GetCharacter(0);
		if(pCharacter && !pCharacter->IsCharacterVisible())
			return;
	}

	Vec3   offset(-0.06f,0.28f,0.115f); //To match scope position in TP LAW model
	Vec3   pos = GetEntity()->GetWorldTM().TransformPoint(offset);
	Vec3   dir = GetEntity()->GetWorldRotation().GetColumn1();

	Vec3 hitPos(0,0,0);
	float laserLength = 0.0f;

	if(allowUpdate)
	{
		IPhysicalEntity* pSkipEntity = NULL;
		if(GetOwner())
			pSkipEntity = GetOwner()->GetPhysics();

		const float range = m_LaserRangeTP;

		// Use the same flags as the AI system uses for visibility.
		const int objects = ent_terrain|ent_static|ent_rigid|ent_sleeping_rigid|ent_independent; //ent_living;
		const int flags = (geom_colltype_ray << rwi_colltype_bit) | rwi_colltype_any | (10 & rwi_pierceability_mask) | (geom_colltype14 << rwi_colltype_bit);

		ray_hit hit;
		if (gEnv->pPhysicalWorld->RayWorldIntersection(pos, dir*range, objects, flags,
			&hit, 1, &pSkipEntity, pSkipEntity ? 1 : 0))
		{
			laserLength = hit.dist;
			m_lastLaserHitPt = hit.pt;
			m_lastLaserHitSolid = true;
		}
		else
		{
			m_lastLaserHitSolid = false;
			m_lastLaserHitPt = pos + dir * range;
			laserLength = range + 0.1f;
		}

		// Hit near plane
		if (dir.Dot(camera.GetViewdir()) < 0.0f)
		{
			Plane nearPlane;
			nearPlane.SetPlane(camera.GetViewdir(), camera.GetPosition());
			nearPlane.d -= camera.GetNearPlane()+0.15f;
			Ray ray(pos, dir);
			Vec3 out;
			m_lastLaserHitViewPlane = false;
			if (Intersect::Ray_Plane(ray, nearPlane, out))
			{
				float dist = Distance::Point_Point(pos, out);
				if (dist < laserLength)
				{
					laserLength = dist;
					m_lastLaserHitPt = out;
					m_lastLaserHitSolid = true;
					m_lastLaserHitViewPlane = true;
				}
			}
		}

		hitPos = m_lastLaserHitPt;
	}
	else
	{
		laserLength = Distance::Point_Point(m_lastLaserHitPt, pos);
		hitPos = pos + dir * laserLength;
	}

	if (m_smoothLaserLength < 0.0f)
		m_smoothLaserLength = laserLength;
	else
	{
		if (laserLength < m_smoothLaserLength)
			m_smoothLaserLength = laserLength;
		else
			m_smoothLaserLength += (laserLength - m_smoothLaserLength) * min(1.0f, 10.0f * frameTime);
	}

	const float assetLength = 2.0f;
	m_smoothLaserLength = CLAMP(m_smoothLaserLength,0.01f,m_LaserRangeTP);
	float scale = m_smoothLaserLength / assetLength; 

	// Scale the laser based on the distance.
	Matrix34 scl;
	scl.SetIdentity();
	scl.SetScale(Vec3(1,scale,1));
	scl.SetTranslation(offset);
	GetEntity()->SetSlotLocalTM( eIGS_Aux1, scl);

	if (m_dotEffectSlot >= 0)
	{
		if (m_lastLaserHitSolid)
		{
			Matrix34 dotMatrix = Matrix34::CreateTranslationMat(Vec3(0,m_smoothLaserLength,0));
			dotMatrix.AddTranslation(offset);
			if(m_lastLaserHitViewPlane)
				dotMatrix.Scale(Vec3(0.2f,0.2f,0.2f));
			GetEntity()->SetSlotLocalTM(m_dotEffectSlot,dotMatrix);
		}
		else
		{
			Matrix34 scaleMatrix;
			scaleMatrix.SetIdentity();
			scaleMatrix.SetScale(Vec3(0.001f,0.001f,0.001f));
			GetEntity()->SetSlotLocalTM(m_dotEffectSlot, scaleMatrix);
		}
	}
}