bool CMFXParticleEffect::AttachToCharacter( IEntity& targetEntity, const SMFXParticleEntry& particleParams, const SMFXRunTimeEffectParams& params, const Vec3& dir, float scale )
{
	if (params.partID >= 0)
	{
		//Assume character is loaded in first slot 
		//We could iterate through all available slots, but first one should be good enough
		ICharacterInstance* pCharacterInstace = targetEntity.GetCharacter(0);
		ISkeletonPose* pSkeletonPose = pCharacterInstace ? pCharacterInstace->GetISkeletonPose() : NULL;
		if (pSkeletonPose)
		{
			IDefaultSkeleton& rIDefaultSkeleton	= pCharacterInstace->GetIDefaultSkeleton();
			//It hit the character, but probably in a physicalized attached part, like armor plates, etc
			if (params.partID >= rIDefaultSkeleton.GetJointCount())
			{
				return false;
			}

			//It hit some valid joint, create an attachment
			const char* boneName = rIDefaultSkeleton.GetJointNameByID(params.partID);
			TAttachmentName attachmentName;
			GetNextCharacterAttachmentName(attachmentName);

			IAttachmentManager* pAttachmentManager = pCharacterInstace->GetIAttachmentManager();
			CRY_ASSERT(pAttachmentManager);
			
			//Remove the attachment first (in case was created before)
			pAttachmentManager->RemoveAttachmentByName(attachmentName.c_str());

			//Create attachment on nearest hit bone
			IAttachment* pAttachment = pAttachmentManager->CreateAttachment(attachmentName.c_str(), CA_BONE, boneName, false);
			if (pAttachment)
			{
				//Apply relative offsets
				const QuatT boneLocation = pSkeletonPose->GetAbsJointByID(params.partID);
				Matrix34 inverseJointTM = targetEntity.GetWorldTM() * Matrix34(boneLocation);
				inverseJointTM.Invert();
				Vec3 attachmentOffsetPosition = inverseJointTM * params.pos;
				Quat attachmentOffsetRotation = Quat(inverseJointTM) * targetEntity.GetRotation();

				CRY_ASSERT(attachmentOffsetPosition.IsValid());
				//CRY_ASSERT(attachmentOffsetRotation.IsUnit());

				pAttachment->SetAttRelativeDefault(QuatT(attachmentOffsetRotation, attachmentOffsetPosition));

				//Finally attach the effect
				CEffectAttachment* pEffectAttachment = new CEffectAttachment(particleParams.name.c_str(), Vec3(0,0,0), dir, scale);
				pAttachment->AddBinding(pEffectAttachment);
				
				return true;
			}
		}
	}

	return false;
}