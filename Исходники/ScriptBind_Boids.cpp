int CScriptBind_Boids::CreateFlock( IFunctionHandler *pH, SmartScriptTable entity,int nType,SmartScriptTable paramTable )
{
	IEntity *pEntity = GetEntity(entity);
	if (!pEntity)
	{
		GameWarning( "Boids.CreateFlock called with an invalid entity" );
		return pH->EndFunction();
	}

	pEntity->SetFlags( pEntity->GetFlags() | ENTITY_FLAG_CLIENT_ONLY );

	CFlock *pFlock = 0;
	switch (nType) {
	case EFLOCK_BIRDS:
		pFlock = new CBirdsFlock(pEntity);
		break;
	case EFLOCK_CHICKENS:
		pFlock = new CChickenFlock(pEntity);
		break;
	case EFLOCK_FISH:
		pFlock = new CFishFlock(pEntity);
		break;
	case EFLOCK_FROGS:
		pFlock = new CFrogFlock(pEntity);
		break;
	case EFLOCK_TURTLES:
		pFlock = new CTurtleFlock(pEntity);
		break;
	case EFLOCK_BUGS:
		pFlock = new CBugsFlock(pEntity);
		break;
	}
	if (pFlock==NULL)
	{
		GameWarning( "Boids.CreateFlock wrong flock type %d specified",nType );
		return pH->EndFunction();
	}

	//////////////////////////////////////////////////////////////////////////
	// Creates a boids proxy for this entity, and attach flock to it.
	CBoidsProxy *pBoidsProxy = new CBoidsProxy(pEntity);
	pEntity->SetProxy( ENTITY_PROXY_BOIDS,pBoidsProxy );

	SBoidContext bc;
	pFlock->GetBoidSettings( bc );

	SBoidsCreateContext ctx;
	if (ReadParamsTable( paramTable,bc,ctx ))
	{
		bc.entity = pEntity;
		pFlock->SetBoidSettings( bc );
		pFlock->CreateBoids( ctx );
	}

	// Assign flock to boids proxy and update some settings.
	pBoidsProxy->SetFlock(pFlock);

	return pH->EndFunction();
}