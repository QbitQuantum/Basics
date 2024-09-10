void cheat_handle_quickwarp(struct vehicle_info *vehicle_info, struct actor_info *actor_info)
{
	if (KEYCOMBO_PRESSED(set.key_quickwarp))
	{
		CCam *pCam = pGame->GetCamera()->GetCam(pGame->GetCamera()->GetActiveCam());
		CVector camsrc(*pCam->GetSource()), src, target, tppos;
		CColPoint *pCollision = nullptr;
		CEntitySAInterface *pEntity = nullptr;

		if (pCam->GetMode() == MODE_AIMWEAPON || pCam->GetMode() == MODE_AIMWEAPON_ATTACHED || pCam->GetMode() == MODE_AIMWEAPON_FROMCAR)
		{
			// calculate target position by aim vector
			pGame->GetCamera()->Find3rdPersonCamTargetVector(700.0f, &camsrc, &src, &target);
		}
		else
		{
			// else by camera vector
			target = camsrc + *pCam->GetFront() * 700.0f;
		}

		// ignore self vehicle
		if (vehicle_info != nullptr)
		{
			*(::vehicle_info **)VAR_IgnoredEntity = vehicle_info;
		}

		if (GTAfunc_ProcessLineOfSight(&camsrc, &target, &pCollision, &pEntity, true, true, false, true, true, false, false, false))
		{
			tppos = *pCollision->GetPosition();
			tppos -= (*pCollision->GetNormal()) * 0.5f;
			
			if (pCollision->GetNormal()->fZ >= 0.5f || pPedSelf->GetAreaCode() != 0)
			{
				tppos.fZ += 1.0f;
				tppos.fZ = pGameInterface->GetWorld()->FindGroundZFor3DPosition(&tppos);
			}
			else
			{
				tppos.fZ = pGameInterface->GetWorld()->FindGroundZForPosition(tppos.fX, tppos.fY);
			}

			if (vehicle_info != nullptr)
			{
				// check for collision
				CVehicle *vehSelf = pPedSelf->GetVehicle();
				if (vehSelf)
				{
					pCollision->Destroy();
					// check for collision
					CVector vecVehicleGravity;
					vehSelf->GetGravity(&vecVehicleGravity);
					CVector vecVehicleAbove = (-vecVehicleGravity * 5.0f) + tppos;
					CVector vecVehicleBelow = (vecVehicleGravity * 5.0f) + tppos;
					bool bCollision = GTAfunc_ProcessLineOfSight(&vecVehicleAbove, &vecVehicleBelow, &pCollision, &pEntity,
																 true, false, false, true, true, false, false, false); // not checking for vehicle collisions
					if (bCollision && pCollision)
					{
						// set vehicle to same Up position has surface normal
						CMatrix matVehicleSelf;
						vehSelf->GetMatrix(&matVehicleSelf);
						CVector vecCollisionNormal = *pCollision->GetNormal();

						// get "down" from vehicle model
						CVector rotationAxis = matVehicleSelf.vUp;

						// normalize our vectors
						vecCollisionNormal.Normalize();
						rotationAxis.Normalize();

						// axis and rotation for gravity
						float	theta = acos(rotationAxis.DotProduct(&vecCollisionNormal));
						if (!near_zero(theta))
						{
							rotationAxis.CrossProduct(&vecCollisionNormal);
							rotationAxis.Normalize();
							rotationAxis.ZeroNearZero();
							matVehicleSelf = matVehicleSelf.Rotate(&rotationAxis, -theta);
						}

						// set the new matrix
						vehSelf->SetMatrix(&matVehicleSelf);

						// set pos floats for actual teleporting
						tppos.fX = pCollision->GetPosition()->fX;
						tppos.fY = pCollision->GetPosition()->fY;
						tppos.fZ = pCollision->GetPosition()->fZ + 1.0f; // should be enough to stay above the ground properly
					}
					else
					{
						tppos.fZ += 0.5f;
					}
					cheat_vehicle_teleport(vehicle_info, &tppos.fX, gta_interior_id_get(), true);
				}
			}
			else if (actor_info != nullptr)
			{
				tppos.fZ += 1.0f;
				cheat_actor_teleport(actor_info, &tppos.fX, gta_interior_id_get());
			}
			GTAfunc_TogglePlayerControllable(0);
			GTAfunc_LockActor(0);
		}
		if (pCollision != nullptr)
		{
			pCollision->Destroy();
		}
	}
}