	void BMaxObject::LoadPhysics()
	{
		if (m_dwPhysicsMethod > 0 && IsPhysicsEnabled() && (GetStaticActorCount() == 0))
		{
			if (m_pAnimatedMesh && m_pAnimatedMesh->IsLoaded())
			{
				CParaXModel* ppMesh = m_pAnimatedMesh->GetModel();
				if (ppMesh == 0 || ppMesh->GetHeader().maxExtent.x <= 0.f)
				{
					EnablePhysics(false); // disable physics forever, if failed loading physics data
					return;
				}
				// get world transform matrix
				Matrix4 mxWorld;
				GetWorldTransform(mxWorld);
				IParaPhysicsActor* pActor = CGlobals::GetPhysicsWorld()->CreateStaticMesh(m_pAnimatedMesh.get(), mxWorld, m_nPhysicsGroup, &m_staticActors, this);
				if (m_staticActors.empty())
				{
					// disable physics forever, if no physics actors are loaded. 
					EnablePhysics(false);
				}
			}
		}
	}