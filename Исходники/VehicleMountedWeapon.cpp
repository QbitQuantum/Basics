//------------------------------------------------------------------------
void CVehicleMountedWeapon::CorrectRipperEntityPosition(float timeStep)
{
	IVehicle *pVehicle = gEnv->pGame->GetIGameFramework()->GetIVehicleSystem()->GetVehicle(m_vehicleId);
	if(pVehicle)
	{
		const IEntity* pVehicleEnt = pVehicle->GetEntity();

		Vec3 posDiff(ZERO);
		IActor* pOwner = GetOwnerActor();
		if (pOwner && pOwner->IsPlayer())
		{
			CPlayer* pPlayer	 = static_cast<CPlayer*>(pOwner); 
			const Matrix34& wMat = pVehicleEnt->GetWorldTM(); 
			Vec3 vehiclePos		 = wMat.GetTranslation();
			Vec3 currWSpaceRipUserOffset = wMat.TransformPoint(m_localRipUserOffset);

			posDiff = currWSpaceRipUserOffset - m_previousWSpaceOffsetPosition;

			// Don't want to overwrite anyone else changes with an absolute 'set'
			pOwner->GetEntity()->SetPos(pOwner->GetEntity()->GetWorldPos() + posDiff); 

			m_previousWSpaceOffsetPosition = currWSpaceRipUserOffset;

			//Update view limit direction based on change in vehicle rotation
			if(pPlayer->IsClient())
			{
				SViewLimitParams &viewLimits = pPlayer->GetActorParams().viewLimits;
				if(viewLimits.GetViewLimitRangeH()) //Don't do this unless we are currently horizontally constrained
				{
					Quat vehicleRotation(wMat);
					Quat rotationChange = vehicleRotation * m_previousVehicleRotation.GetInverted();

					Vec3 viewLimitDir = rotationChange * viewLimits.GetViewLimitDir();
					viewLimitDir.z = 0.f;
					viewLimitDir.Normalize();

					viewLimits.SetViewLimit(viewLimitDir, 0.01f, 0.01f, 0.f, 0.f, SViewLimitParams::eVLS_Item);

					m_previousVehicleRotation = vehicleRotation;
				}

				//Reset the pitch/roll view angles over time
				Quat viewDirFinal = pPlayer->GetViewQuatFinal();
				Ang3 viewAngles(viewDirFinal);
				float xAdjustment = (float)__fsel(viewAngles.x, max(-viewAngles.x, -0.5f * timeStep), min(-viewAngles.x, 0.5f * timeStep));
				float yAdjustment = (float)__fsel(viewAngles.y, max(-viewAngles.y, -0.5f * timeStep), min(-viewAngles.y, 0.5f * timeStep));

				if(xAdjustment || yAdjustment)
				{
					pPlayer->AddViewAngles(Ang3(xAdjustment, yAdjustment, 0.f));
				}
			}
		}
	}
}