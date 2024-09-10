//------------------------------------------------------------------------
void CItem::UpdateMounted(float frameTime)
{
	IRenderAuxGeom* pAuxGeom = gEnv->pRenderer->GetIRenderAuxGeom();

	if (!m_ownerId || !m_stats.mounted)
		return;

	CActor *pActor = GetOwnerActor();
	if (!pActor)
		return;

	CheckViewChange();

  if (true)
  {  
	  if (IsClient())
	  {
		  ICharacterInstance *pCharacter = GetEntity()->GetCharacter(eIGS_FirstPerson);

		  if (pCharacter && !m_idleAnimation[eIGS_FirstPerson].empty() && pCharacter->GetISkeletonAnim()->GetNumAnimsInFIFO(0)<1)
			  PlayAction(m_idleAnimation[eIGS_FirstPerson], 0, true);
	  }

		// need to explicitly update characters at this point
		// cause the entity system update occered earlier, with the last position
		for (int i=0; i<eIGS_Last; i++)
		{
			if (GetEntity()->GetSlotFlags(i)&ENTITY_SLOT_RENDER)
			{
				ICharacterInstance *pCharacter = GetEntity()->GetCharacter(i);
				if (pCharacter)
				{
					Matrix34 mloc = GetEntity()->GetSlotLocalTM(i,false);
					Matrix34 m34 = GetEntity()->GetWorldTM()*mloc;
					QuatT renderLocation = QuatT(m34);
					pCharacter->GetISkeletonPose()->SetForceSkeletonUpdate(9);
					pCharacter->SkeletonPreProcess(renderLocation, renderLocation, GetISystem()->GetViewCamera(),0x55 );
					pCharacter->SetPostProcessParameter(renderLocation, renderLocation, 0, 0.0f, 0x55 );		
				}
			}
		}

	//	f32 fColor[4] = {1,1,0,1};
	//	f32 g_YLine=60.0f;
	//	gEnv->pRenderer->Draw2dLabel( 1,g_YLine, 1.3f, fColor, false, "Mounted Gun Code" ); 

		//adjust the orientation of the gun based on the aim-direction


		SMovementState info;
		IMovementController* pMC = pActor->GetMovementController();		
		pMC->GetMovementState(info);
		Vec3 dir = info.aimDirection.GetNormalized();
		Matrix34 tm = Matrix33::CreateRotationVDir(dir);
		Vec3 vGunXAxis=tm.GetColumn0();

		if (pActor->GetLinkedVehicle()==0)
		{
			if (pMC)
			{						
				if(!pActor->IsPlayer())
				{
					// prevent snapping direction
					Vec3 currentDir = GetEntity()->GetWorldRotation().GetColumn1();
					float dot = currentDir.Dot(dir);
					dot = CLAMP(dot,-1,1);
					float reqAngle = cry_acosf(dot);
					const float maxRotSpeed = 2.0f;
					float maxAngle = frameTime * maxRotSpeed;
					if(fabs(reqAngle) > maxAngle)
					{
						Vec3 axis = currentDir.Cross(dir);
						if(axis.GetLengthSquared()>0.001f) // current dir and new dir are enough different
							dir = currentDir.GetRotated(axis.GetNormalized(),sgn(reqAngle)*maxAngle);
					}
				}				
				//adjust the orientation of the gun based on the aim-direction
				tm = Matrix33::CreateRotationVDir(dir);
				Vec3 vWPos=GetEntity()->GetWorldPos();
				tm.SetTranslation(vWPos);
				GetEntity()->SetWorldTM(tm);  //set the new orientation of the mounted gun

				vGunXAxis=tm.GetColumn0();
				Vec3 vInitialAimDirection = m_stats.mount_dir;
				Matrix33 vInitialPlayerOrientation = Matrix33::CreateRotationVDir(vInitialAimDirection);
				assert( vInitialAimDirection.IsUnit() );

	  		Vec3 newp;

				if (pActor->IsThirdPerson())
				{
					//third person
					f32 dist = m_mountparams.body_distance*1.3f;
					Vec3 oldp = pActor->GetEntity()->GetWorldPos();
					newp = GetEntity()->GetWorldPos()-vInitialAimDirection*dist; //mounted gun
					newp.z = oldp.z;
				}
				else
				{
					//first person
					f32 fMoveBack = (1.0f+(dir.z*dir.z*dir.z*dir.z*4.0f))*0.75f;
					f32	dist = m_mountparams.eye_distance*fMoveBack;
					Vec3 oldp = pActor->GetEntity()->GetWorldPos();
					newp = GetEntity()->GetWorldPos()-dir*dist; //mounted gun
					//newp.z -= 0.75f;
					newp.z = oldp.z;
				}


				Matrix34 actortm(pActor->GetEntity()->GetWorldTM());

				//if (pActor->IsThirdPerson())
				actortm=vInitialPlayerOrientation;

				actortm.SetTranslation(newp);
				pActor->GetEntity()->SetWorldTM(actortm, ENTITY_XFORM_USER);
				pActor->GetAnimationGraphState()->SetInput("Action","gunnerMounted");
				
				//f32 g_YLine=80.0f;
				//gEnv->pRenderer->Draw2dLabel( 1,g_YLine, 1.3f, fColor, false, "Mounted Gun Active for FP and AI" ); 

				if (ICharacterInstance *pCharacter = pActor->GetEntity()->GetCharacter(0))
				{
					ISkeletonAnim *pSkeletonAnim = pCharacter->GetISkeletonAnim();
					assert(pSkeletonAnim);

					uint32 numAnimsLayer = pSkeletonAnim->GetNumAnimsInFIFO(0);
					for(uint32 i=0; i<numAnimsLayer; i++)
					{
						CAnimation &animation = pSkeletonAnim->GetAnimFromFIFO(0, i);
						if (animation.m_AnimParams.m_nFlags & CA_MANUAL_UPDATE)
						{
							f32 aimrad = Ang3::CreateRadZ(Vec2(vInitialAimDirection),Vec2(dir));
							animation.m_fAnimTime = clamp_tpl(aimrad/gf_PI,-1.0f,+1.0f)*0.5f+0.5f;
							//if (pActor->IsThirdPerson()==0)
								//animation.m_fAnimTime=0.6f; //Ivo & Benito: high advanced future code. don't ask what it is 
							                                //Benito - Not needed any more ;)

							//f32 g_YLine=100.0f;
							//gEnv->pRenderer->Draw2dLabel( 1,g_YLine, 1.3f, fColor, false, "AnimTime: %f    MyAimAngle: %f deg:%   distance:%f", animation.m_fAnimTime, aimrad, RAD2DEG(aimrad),m_mountparams.body_distance ); 
						}
					}

				}

				m_stats.mount_last_aimdir = dir;
				
			}
		}
    
    if (ICharacterInstance* pCharInstance = pActor->GetEntity()->GetCharacter(0))
		{
      if (ISkeletonAnim* pSkeletonAnim = pCharInstance->GetISkeletonAnim())
      {   
        OldBlendSpace ap;				
        if (GetAimBlending(ap))
        {
					pSkeletonAnim->SetBlendSpaceOverride(eMotionParamID_TurnSpeed, 0.5f + 0.5f * ap.m_turn, true);
        }        
      }        
    } 

    UpdateIKMounted(pActor, vGunXAxis*0.1f);
   
		RequireUpdate(eIUS_General);
  }
}