void CVehicleWeaponControlled::Update(SEntityUpdateContext& ctx, int update)
{
	IVehicle *pVehicle = m_vehicleId ? gEnv->pGame->GetIGameFramework()->GetIVehicleSystem()->GetVehicle(m_vehicleId) : NULL; 
  if (!m_vehicleId && GetEntity()->GetParent())
  {
    IEntity *entity = GetEntity();
    
    if (entity)
    {
      IEntity *parent = entity->GetParent();
      if (parent)
      {
				m_vehicleId = parent->GetId();
        pVehicle = gEnv->pGame->GetIGameFramework()->GetIVehicleSystem()->GetVehicle(parent->GetId());
      }
    }
  }



  if (pVehicle)
  {
		IVehiclePart *pPart = pVehicle->GetWeaponParentPart(GetEntityId());
		if(pPart)
		{
			if(IVehiclePart *pParentPart = pPart->GetParent())
			{
				CRY_ASSERT(pVehicle->GetEntity());

				if(ICharacterInstance *characterInst = pVehicle->GetEntity()->GetCharacter(pParentPart->GetSlot()))
				{
					if(ISkeletonPose* pose = characterInst->GetISkeletonPose())
					{
						IDefaultSkeleton& rIDefaultSkeleton = characterInst->GetIDefaultSkeleton();
						int16 joint = rIDefaultSkeleton.GetJointIDByName(pPart->GetName());
						const QuatT &jQuat = pose->GetAbsJointByID(joint);

						Matrix34 localT(jQuat);
						localT.SetTranslation(jQuat.t/* - Vec3(0.0f, 0.75f, 0.0f)*/);

						Matrix34 vehicleWorldTm = pVehicle->GetEntity()->GetWorldTM();
						Matrix34 mat = vehicleWorldTm * localT;
						Vec3 vehicleSide2 = pPart->GetParent()->GetLocalTM(true, true).GetTranslation();

						CPlayer *pl = this->GetOwnerPlayer();

						Matrix33 mat2;
						if (!m_destination.IsEquivalent(ZERO))
						{
							Vec3 diff = GetDestination() - mat.GetTranslation(); //pPart->GetWorldTM().GetTranslation();
							diff.Normalize();

							Matrix33 loc(mat);
							loc.Invert();

							Vec3 diffLocal = loc.TransformVector(diff);

							Matrix33 desMat;
							desMat.SetRotationVDir(diffLocal, 0.0f);

							Vec3 test = GetEntity()->GetLocalTM().GetColumn0();

							Ang3 testTM(desMat);

							float za = testTM.x - m_Angles.x;
							za = (za < 0.0f) ? -gf_PI : gf_PI;
							za *= 0.05f * ctx.fFrameTime;

							m_Angles.x += za;
							Limit(m_Angles.x, -gf_PI * 0.33f, gf_PI * 0.33f);

							if (testTM.z > m_Angles.z + 0.05f)
							{
								m_Angles.z += gf_PI * factor1 * ctx.fFrameTime;        
							}
							else if (testTM.z < m_Angles.z - 0.05f)
							{
								m_Angles.z -= gf_PI * factor1 * ctx.fFrameTime;        
							}
							else
							{
								m_Angles.z = testTM.z;
							}

							Limit(m_Angles.z, -gf_PI * 0.33f, gf_PI * 0.33f);
							mat2.SetRotationXYZ(m_Angles);
						}
						else
						{
							if (!m_FireBlocked)
							{
								m_Angles.x = m_Angles.x - ctx.fFrameTime * factor2 * m_Angles.x;
								m_Angles.z = m_Angles.z - ctx.fFrameTime * factor2 * m_Angles.z;
							}
							mat2.SetRotationXYZ(m_Angles);
						}

						mat = mat * mat2; 


						GetEntity()->SetWorldTM(mat);


						if (pl)
						{
							Matrix34 worldGunMat = vehicleWorldTm * localT;

							if (!pl->IsDead())
							{

								Vec3 trans = worldGunMat.GetTranslation() - worldGunMat.GetColumn2() * 0.7f;
								worldGunMat.SetTranslation(trans);

								pl->GetEntity()->SetWorldTM(worldGunMat);


								float dot = mat.GetColumn1().dot(worldGunMat.GetColumn0());
								Update3PAnim(pl, 0.5f - dot * 0.5f, ctx.fFrameTime, mat);
							}
							else
							{

								ICharacterInstance* pCharacter = pl->GetEntity()->GetCharacter(0);
								int boneId = pCharacter ? pCharacter->GetIDefaultSkeleton().GetJointIDByName("Spine03") : 7;

								pl->LinkToMountedWeapon(0);
								if (IVehicleSeat* seat = pVehicle->GetSeatForPassenger(pl->GetEntityId()))
								{
									seat->Exit(false, true);
								}

								Matrix33 rot(worldGunMat);
								Vec3 offset(0.0f, 0.0f, 0.70f);
								Vec3 transformedOff = rot.TransformVector(offset);
								Vec3 trans = worldGunMat.GetTranslation();
								trans -= transformedOff;
								worldGunMat.SetTranslation(trans);
								pl->GetEntity()->SetWorldTM(worldGunMat);
								pl->GetEntity()->SetPos(worldGunMat.GetTranslation()); //worldGunMat.GetTranslation());
								pl->RagDollize(true);

								if (boneId > -1)
								{
									IPhysicalEntity *physEnt = pl->GetEntity()->GetPhysics();
									if (physEnt)
									{
										pe_simulation_params simulationParams;
										physEnt->GetParams(&simulationParams);

										pe_params_pos pos;
										pos.pos = GetEntity()->GetPos();
										physEnt->SetParams(&pos);

										pe_action_impulse impulse;
										impulse.ipart = boneId;
										impulse.angImpulse = Vec3(0.0f, 0.0f, 1.0f);
										impulse.impulse = worldGunMat.GetColumn1() * -1.5f * simulationParams.mass;
										physEnt->Action(&impulse);
									}
								}

								StopUse(GetOwnerId());

								SetOwnerId(0);
								StopFire();

								m_FireBlocked = true;
							} // IsDead
						} // pl
					} // pose
				} // characterInst
			} // pParentPart
		} // pPart
	} // pVehicle

  Base::Update(ctx, update);
  RequireUpdate(eIUS_General);
}