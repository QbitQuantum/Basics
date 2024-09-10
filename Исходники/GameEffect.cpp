//--------------------------------------------------------------------------------------------------
// Name: SpawnParticlesOnSkeleton
// Desc: Spawn particles on Skeleton
//--------------------------------------------------------------------------------------------------
void CGameEffect::SpawnParticlesOnSkeleton(IEntity* pEntity, IParticleEmitter* pParticleEmitter, uint32 numParticles,float maxHeightScale) const
{
	if((pEntity) && (numParticles>0) && (pParticleEmitter) && (maxHeightScale>0.0f))
	{
		ICharacterInstance* pCharacter = pEntity->GetCharacter(0);
		if(pCharacter)
		{
			IDefaultSkeleton& rIDefaultSkeleton = pCharacter->GetIDefaultSkeleton();
			ISkeletonPose* pPose = pCharacter->GetISkeletonPose();
			if(pPose)
			{
				Vec3 animPos;
				Quat animRot;

				IActor* pActor = gEnv->pGame->GetIGameFramework()->GetIActorSystem()->GetActor(pEntity->GetId());
				if(pActor) // First try to get animation data
				{
					QuatT animLoc = pActor->GetAnimatedCharacter()->GetAnimLocation();
					animPos = animLoc.t;
					animRot = animLoc.q;
				}
				else // If no actor, then use entity data
				{
					animPos = pEntity->GetWorldPos();
					animRot = pEntity->GetWorldRotation();
				}

				animRot.Invert();

				AABB bbox;
				pEntity->GetLocalBounds(bbox);
				float bbHeight = bbox.max.z - bbox.min.z;
				// Avoid division by 0
				if(bbHeight == 0)
				{
					bbHeight = 0.0001f;
				}

				const uint32 numJoints = rIDefaultSkeleton.GetJointCount();

				for (uint32 i = 0; i < numParticles; ++i)
				{
					int id = cry_random(0U, numJoints - 1);
					int parentId = rIDefaultSkeleton.GetJointParentIDByID(id);

					if(parentId>0)
					{
						QuatT boneQuat = pPose->GetAbsJointByID(id);
						QuatT parentBoneQuat= pPose->GetAbsJointByID(parentId);
						float lerpScale = cry_random(0.0f, 1.0f);

						QuatTS loc(IDENTITY);
						loc.t = LERP(boneQuat.t,parentBoneQuat.t,lerpScale);

						float heightScale = ((loc.t.z - bbox.min.z) / bbHeight);
						if(heightScale < maxHeightScale)
						{
							loc.t = loc.t * animRot;
							loc.t = loc.t + animPos;

							pParticleEmitter->EmitParticle(NULL, NULL, &loc);
						}
					}
				}
			}
		}
	}
}//-------------------------------------------------------------------------------------------------