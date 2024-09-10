FQuat UAnimGraphNode_SkeletalControlBase::ConvertCSRotationToBoneSpace(const USkeletalMeshComponent* SkelComp, FRotator& InCSRotator, FA2CSPose& MeshBases, const FName& BoneName, const EBoneControlSpace Space)
{
	FQuat OutQuat = FQuat::Identity;

	if (MeshBases.IsValid())
	{
		int32 MeshBoneIndex = SkelComp->GetBoneIndex(BoneName);

		FVector RotAxis;
		float RotAngle;
		InCSRotator.Quaternion().ToAxisAndAngle(RotAxis, RotAngle);

		switch (Space)
		{
			// World Space, no change in preview window
		case BCS_WorldSpace:
		case BCS_ComponentSpace:
			// Component Space, no change.
			OutQuat = InCSRotator.Quaternion();
			break;

		case BCS_ParentBoneSpace:
		{
			const int32 ParentIndex = MeshBases.GetParentBoneIndex(MeshBoneIndex);
			if (ParentIndex != INDEX_NONE)
			{
				FTransform ParentTM = MeshBases.GetComponentSpaceTransform(ParentIndex);
				ParentTM = ParentTM.Inverse();
				//Calculate the new delta rotation
				FVector4 BoneSpaceAxis = ParentTM.TransformVector(RotAxis);
				FQuat DeltaQuat(BoneSpaceAxis, RotAngle);
				DeltaQuat.Normalize();
				OutQuat = DeltaQuat;
			}
		}
			break;

		case BCS_BoneSpace:
		{
			FTransform BoneTM = MeshBases.GetComponentSpaceTransform(MeshBoneIndex);
			BoneTM = BoneTM.Inverse();
			FVector4 BoneSpaceAxis = BoneTM.TransformVector(RotAxis);
			//Calculate the new delta rotation
			FQuat DeltaQuat(BoneSpaceAxis, RotAngle);
			DeltaQuat.Normalize();
			OutQuat = DeltaQuat;
		}
			break;
		}
	}

	return OutQuat;
}