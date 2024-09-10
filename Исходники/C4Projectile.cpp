//-----------------------------------------------
//This function is only executed on the server
void CC4Projectile::Stick(EventPhysCollision *pCollision)
{
	assert(pCollision);
	int trgId = 1;
	IPhysicalEntity *pTarget = pCollision->pEntity[trgId];

	if(pTarget == GetEntity()->GetPhysics())
	{
		trgId = 0;
		pTarget = pCollision->pEntity[trgId];
	}

	//Do not stick to breakable glass
	if(ISurfaceType *pSurfaceType = gEnv->p3DEngine->GetMaterialManager()->GetSurfaceType(pCollision->idmat[trgId]))
	{
		if(pSurfaceType->GetBreakability()==1)
		{
			m_notStick = true;
			return;
		}
	}

	IEntity *pTargetEntity = pTarget ? gEnv->pEntitySystem->GetEntityFromPhysics(pTarget) : 0;

	if(pTarget && (!pTargetEntity || (pTargetEntity->GetId() != m_ownerId)))
	{
		//Special cases
		if(pTargetEntity)
		{
			//Stick to actors using a character attachment
			CActor *pActor = static_cast<CActor *>(gEnv->pGame->GetIGameFramework()->GetIActorSystem()->GetActor(pTargetEntity->GetId()));

			//Not in MP
			if(pActor && gEnv->bMultiplayer)
			{
				m_notStick = true;
				return;
			}

			if(pActor && pActor->GetHealth()>0)
			{
				if(pActor->GetActorSpecies()!=eGCT_HUMAN)
				{
					m_notStick = true;
					return;
				}

				if(StickToCharacter(true,pTargetEntity))
				{
					GetGameObject()->SetAspectProfile(eEA_Physics, ePT_None);
					m_stuck = true;
				}

				m_notStick = true;
				return;
			}

			//Do not stick to small objects...
			if(!pActor)
			{
				pe_params_part pPart;
				pPart.ipart = 0;

				if(pTarget->GetParams(&pPart) && pPart.pPhysGeom && pPart.pPhysGeom->V<0.15f)
				{
					m_notStick = true;
					return;
				}
			}

		}
		else if(pTarget->GetType()==PE_LIVING)
		{
			m_notStick = true;
			return;
		}

		if(!pTargetEntity)
			StickToStaticObject(pCollision,pTarget);
		else
		{
			//Do not attach to items
			if(g_pGame->GetIGameFramework()->GetIItemSystem()->GetItem(pTargetEntity->GetId()))
			{
				m_notStick = true;
				return;
			}

			Matrix34 mat = pTargetEntity->GetWorldTM();
			mat.Invert();
			Vec3 pos = mat.TransformPoint(pCollision->pt);
			mat.SetIdentity();
			mat.SetRotation33(Matrix33::CreateOrientation(-pCollision->n,GetEntity()->GetWorldTM().TransformVector(Vec3(0,0,1)),gf_PI));
			mat.SetTranslation(pos);

			//Dephysicalize and stick
			GetGameObject()->SetAspectProfile(eEA_Physics, ePT_None);

			StickToEntity(pTargetEntity,mat);

			if(gEnv->bMultiplayer)
			{
				Quat rot(Matrix33::CreateOrientation(-pCollision->n,GetEntity()->GetWorldTM().TransformVector(Vec3(0,0,1)),gf_PI*0.5f));
				GetGameObject()->InvokeRMI(CC4Projectile::ClStickToEntity(),ProjectileStickToEntity(pTargetEntity->GetId(),pos,rot),eRMI_ToAllClients);
			}
		}

		m_stuck = true;
	}
}