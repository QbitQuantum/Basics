	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
	{
		if (!pActInfo->pEntity)
			return;

		if (event == eFE_Activate && IsPortActive(pActInfo, IN_ACTIVATE))
		{
			pe_action_impulse action;

			int ipart = GetPortInt( pActInfo, IN_PARTINDEX );
			if (ipart>0)
				action.ipart = ipart-1;

			IEntity* pEntity = pActInfo->pEntity;
			ECoordSys coordSys = (ECoordSys)GetPortInt( pActInfo, IN_COORDSYS );

			if (coordSys==CS_PARENT && !pEntity->GetParent())
				coordSys = CS_WORLD;

			// When a "zero point" is set in the node, the value is left undefined and physics assume it is the CM of the object.
			// but when the entity has a parent (is linked), then we have to use a real world coordinate for the point, because we have to apply the impulse to the highest entity 
			// on the hierarchy and physics will use the position of that entity instead of the position of the entity assigned to the node
			bool bHaveToUseTransformedZeroPoint = false;
			Vec3 transformedZeroPoint;
			Matrix34 transMat;

		  switch (coordSys)
			{
				case CS_WORLD:
				default:
				{
					transMat.SetIdentity();
					bHaveToUseTransformedZeroPoint = pEntity->GetParent()!=NULL;
					transformedZeroPoint = pEntity->GetWorldPos();
					break;
				}

				case CS_PARENT:
				{
					transMat = pEntity->GetParent()->GetWorldTM();
					bHaveToUseTransformedZeroPoint = pEntity->GetParent()->GetParent()!=NULL;
					transformedZeroPoint = pEntity->GetParent()->GetWorldPos();
					break;
				}

				case CS_LOCAL:
				{
					transMat = pEntity->GetWorldTM();
					bHaveToUseTransformedZeroPoint = pEntity->GetParent()!=NULL;
					transformedZeroPoint = pEntity->GetWorldPos();
					break;
				}
			}

			action.impulse = GetPortVec3( pActInfo, IN_IMPULSE );
			action.impulse = transMat.TransformVector( action.impulse );

			Vec3 angImpulse = GetPortVec3( pActInfo, IN_ANGIMPULSE );
			if (!angImpulse.IsZero())
				action.angImpulse = transMat.TransformVector( angImpulse );

			Vec3 pointApplication = GetPortVec3( pActInfo, IN_POINT );
			if (!pointApplication.IsZero())
				action.point = transMat.TransformPoint( pointApplication );
			else
			{
				if (bHaveToUseTransformedZeroPoint)
					action.point = transformedZeroPoint;
			}


			// the impulse has to be applied to the highest entity in the hierarchy. This comes from how physics manage linked entities.
			IEntity* pEntityImpulse = pEntity;
			while (pEntityImpulse->GetParent())
			{
				pEntityImpulse = pEntityImpulse->GetParent();
			}

			IPhysicalEntity * pPhysEntity = pEntityImpulse->GetPhysics();
			if (pPhysEntity)
				pPhysEntity->Action( &action );
		}
	}