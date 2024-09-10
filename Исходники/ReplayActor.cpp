//------------------------------------------------------------------------
void CReplayActor::ProcessEvent(SEntityEvent &event)
{
	switch (event.event)
	{
	case ENTITY_EVENT_PREPHYSICSUPDATE:
		{
			const int currentFrameId = gEnv->pRenderer->GetFrameID();
			if(currentFrameId==m_lastFrameUpdated)
				return;
			m_lastFrameUpdated = currentFrameId;

			if (m_pActionController)
			{
				float frameTime = gEnv->pTimer->GetFrameTime();
				m_pActionController->Update(frameTime);
			}

			ICharacterInstance* pShadowCharacter = GetShadowCharacter();
			if (pShadowCharacter)
			{
				QuatTS pose = (QuatTS)GetEntity()->GetWorldTM();
				SAnimationProcessParams params;
				params.locationAnimation = pose;
				params.bOnRender = 1;
				params.zoomAdjustedDistanceFromCamera = (GetISystem()->GetViewCamera().GetPosition()-pose.t).GetLength();
				pShadowCharacter->StartAnimationProcessing(params);
				//--- Ensure that we disable the automatic update if we're doing it explicitly
				pShadowCharacter->SetFlags( pShadowCharacter->GetFlags()&(~CS_FLAG_UPDATE) );
			}

			ICharacterInstance *pCharacter = GetEntity()->GetCharacter(0);
			ISkeletonPose *pSkelPose = pCharacter ? pCharacter->GetISkeletonPose() : NULL;

			if(pSkelPose)
			{
				ICharacterModelSkeleton* pICharacterModelSkeleton = pCharacter->GetICharacterModel()->GetICharacterModelSkeleton();

				// GetJointIDByName() returns -1 if it fails; m_headBoneID is initialised to -2
				// since -1 is failure and 0+ are valid bone indices.
				if (m_headBoneID == -2)
				{
					// TODO: Should move this to an initialisation function
					m_headBoneID = pICharacterModelSkeleton->GetJointIDByName("Bip01 Head");
					m_cameraBoneID = pICharacterModelSkeleton->GetJointIDByName("Bip01 Camera");
				}

				if (m_headBoneID > -1)
				{
					m_headPos = pSkelPose->GetAbsJointByID(m_headBoneID);
				}
				if (m_cameraBoneID > -1)
				{
					m_cameraPos = pSkelPose->GetAbsJointByID(m_cameraBoneID);
				}
			}
		}
		break;
	case ENTITY_EVENT_DONE:
	case ENTITY_EVENT_RETURNING_TO_POOL:
		{
			SAFE_RELEASE(m_pActionController);
			SAFE_DELETE(m_pAnimContext);
			m_itemList.OnActionControllerDeleted();
		}
		break;
	}
}