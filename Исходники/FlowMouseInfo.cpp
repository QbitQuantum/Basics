	// Since the modelviewmatrix is updated in the update, and flowgraph is updated in the preupdate, we need this postupdate
	virtual void OnPostUpdate(float fDeltaTime)
	{
		int invMouseY = gEnv->pRenderer->GetHeight() - m_mouseY;

		Vec3 vPos0(0,0,0);
		gEnv->pRenderer->UnProjectFromScreen((float)m_mouseX, (float)invMouseY, 0, &vPos0.x, &vPos0.y, &vPos0.z);

		Vec3 vPos1(0,0,0);
		gEnv->pRenderer->UnProjectFromScreen((float)m_mouseX, (float)invMouseY, 1, &vPos1.x, &vPos1.y, &vPos1.z);

		Vec3 vDir = vPos1 - vPos0;
		vDir.Normalize();
		
		ray_hit hit;
		const unsigned int flags = rwi_stop_at_pierceable|rwi_colltype_any;

		IPhysicalEntity** pSkipEnts = NULL;
		int numSkipped = 0;

		int containerId = GetPortInt(&m_actInfo, EIP_EntitiesToIgnore);
		if(containerId != 0)
		{
			IFlowSystemContainerPtr container = gEnv->pFlowSystem->GetContainer(containerId);
			numSkipped = container->GetItemCount();
			pSkipEnts = new IPhysicalEntity*[numSkipped];
			for (int i = 0; i < numSkipped; i++)
			{
				EntityId id;
				container->GetItem(i).GetValueWithConversion(id);
				pSkipEnts[i] = gEnv->pEntitySystem->GetEntity(id)->GetPhysics();
			}
		}

		if (gEnv->pPhysicalWorld && gEnv->pPhysicalWorld->RayWorldIntersection(vPos0, vDir *  gEnv->p3DEngine->GetMaxViewDistance(), m_rayTypeFilter, flags, &hit, 1, pSkipEnts, numSkipped))
		{
			ActivateOutput(&m_actInfo, EOP_HitPos, hit.pt);
			ActivateOutput(&m_actInfo, EOP_HitNormal, hit.n);

			if(hit.pCollider)
			{
				if(IEntity *pEntity = gEnv->pEntitySystem->GetEntityFromPhysics(hit.pCollider))
				{
					ActivateOutput(&m_actInfo, EOP_EntityId, pEntity->GetId());
				}
			}
		}

		if(pSkipEnts)
			delete [] pSkipEnts;
	}