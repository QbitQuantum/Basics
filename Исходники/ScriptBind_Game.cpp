//////////////////////////////////////////////////////////////////////////
// IsMountedWeaponUsableWithTarget
// A piece of game-code moved from CryAction when scriptbind_AI moved to the AI system
//////////////////////////////////////////////////////////////////////////
int CScriptBind_Game::IsMountedWeaponUsableWithTarget(IFunctionHandler *pH)
{
	int paramCount = pH->GetParamCount();
	if(paramCount<2)
	{
		GameWarning("%s: too few parameters.", __FUNCTION__);
		return pH->EndFunction();
	}

	GET_ENTITY(1);

	if(!pEntity)
	{
		GameWarning("%s: wrong entity id in parameter 1.", __FUNCTION__);
		return pH->EndFunction();
	}

	IAIObject* pAI = pEntity->GetAI();
	if (!pAI)
	{
		GameWarning("%s: Entity '%s' does not have AI.",__FUNCTION__,  pEntity->GetName());
		return pH->EndFunction();
	}

	EntityId itemEntityId;
	ScriptHandle hdl2;

	if(!pH->GetParam(2,hdl2))
	{
		GameWarning("%s: wrong parameter 2 format.", __FUNCTION__);
		return pH->EndFunction();
	}

	itemEntityId = (EntityId)hdl2.n;

	if (!itemEntityId)
	{
		GameWarning("%s: wrong entity id in parameter 2.", __FUNCTION__);
		return pH->EndFunction();
	}
	
	IGameFramework *pGameFramework = gEnv->pGame->GetIGameFramework();
	IItem* pItem = pGameFramework->GetIItemSystem()->GetItem(itemEntityId);
	if (!pItem)
	{
		//gEnv->pAISystem->Warning("<CScriptBind> ", "entity in parameter 2 is not an item/weapon");
		GameWarning("%s: entity in parameter 2 is not an item/weapon.", __FUNCTION__);
		return pH->EndFunction();
	}

	float minDist = 7;
	bool bSkipTargetCheck = false;
	Vec3 targetPos(ZERO);

	if(paramCount > 2)
	{
		for(int i=3;i <= paramCount ; i++)
		{
			if(pH->GetParamType(i) == svtBool)
				pH->GetParam(i,bSkipTargetCheck);
			else if(pH->GetParamType(i) == svtNumber)
				pH->GetParam(i,minDist);
			else if(pH->GetParamType(i) == svtObject)
				pH->GetParam(i,targetPos);
		}
	}

	IAIActor* pAIActor = CastToIAIActorSafe(pAI);
	if (!pAIActor)
	{
		GameWarning("%s: entity '%s' in parameter 1 is not an AI actor.", __FUNCTION__, pEntity->GetName());
		return pH->EndFunction();
	}


	IEntity* pItemEntity = pItem->GetEntity();
	if(!pItemEntity)
		return pH->EndFunction();


	if(!pItem->GetOwnerId())
	{
		// weapon is not used, check if it is on a vehicle
		IEntity* pParentEntity = pItemEntity->GetParent();
		if(pParentEntity)
		{
			IAIObject* pParentAI = pParentEntity->GetAI();
			if(pParentAI && pParentAI->GetAIType()==AIOBJECT_VEHICLE)
			{
				// (MATT) Feature was cut and code was tricky, hence ignore weapons in vehicles  {2008/02/15:11:08:51}
				return pH->EndFunction();
			}
		}
	}
	else if( pItem->GetOwnerId()!= pEntity->GetId()) // item is used by someone else?
		return pH->EndFunction(false);

	// check target
	if(bSkipTargetCheck)
		return pH->EndFunction(true);

	IAIObject* pTarget = pAIActor->GetAttentionTarget();
	if(targetPos.IsZero())
	{
		if(!pTarget)
			return pH->EndFunction();
		targetPos = pTarget->GetPos();
	}

	Vec3 targetDir(targetPos - pItemEntity->GetWorldPos());
	Vec3 targetDirXY(targetDir.x, targetDir.y, 0);

	float length2D = targetDirXY.GetLength();
	if(length2D < minDist || length2D<=0)
		return pH->EndFunction();

	targetDirXY /= length2D;//normalize

	IWeapon* pWeapon = pItem->GetIWeapon(); 
	bool vehicleGun = pWeapon && pWeapon->GetHostId();

	if (!vehicleGun)
	{
		Vec3 mountedAngleLimits(pItem->GetMountedAngleLimits());

		float yawRange = DEG2RAD(mountedAngleLimits.z);
		if(yawRange > 0 && yawRange < gf_PI)
		{
			float deltaYaw = pItem->GetMountedDir().Dot(targetDirXY);
			if(deltaYaw < cosf(yawRange))
				return pH->EndFunction(false);
		}

		float minPitch = DEG2RAD(mountedAngleLimits.x);
		float maxPitch = DEG2RAD(mountedAngleLimits.y);

		//maxPitch = (maxPitch - minPitch)/2;
		//minPitch = -maxPitch;

		float pitch = atanf(targetDir.z / length2D);

		if ( pitch < minPitch || pitch > maxPitch )
			return pH->EndFunction(false);
	}

	if(pTarget)
	{
		IEntity* pTargetEntity = pTarget->GetEntity();
		if(pTargetEntity)
		{
			// check target distance and where he's going
			IPhysicalEntity *phys = pTargetEntity->GetPhysics();
			if(phys)
			{
				pe_status_dynamics	dyn;
				phys->GetStatus(&dyn);
				Vec3 velocity ( dyn.v);
				velocity.z = 0;

				float speed = velocity.GetLength2D();
				if(speed>0)
				{
					//velocity /= speed;
					if(length2D< minDist * 0.75f && velocity.Dot(targetDirXY)<=0)
						return pH->EndFunction(false);
				}
			}
		}
	}
	return pH->EndFunction(true);

}