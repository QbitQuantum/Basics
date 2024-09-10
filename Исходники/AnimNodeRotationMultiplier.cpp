FQuat FAnimNode_RotationMultiplier::MultiplyQuatBasedOnSourceIndex(const FTransform& RefPoseTransform, const FTransform& LocalBoneTransform, const EBoneAxis Axis, float InMultiplier, const FQuat& ReferenceQuat)
{
	// Find delta angle for source bone.
	FQuat DeltaQuat = ExtractAngle(RefPoseTransform, LocalBoneTransform, Axis);

	// Turn to Axis and Angle
	FVector RotationAxis;
	float	RotationAngle;
	DeltaQuat.ToAxisAndAngle(RotationAxis, RotationAngle);

	const FVector DefaultAxis = GetAxisVector(Axis);

	// See if we need to invert angle - shortest path
	if( (RotationAxis | DefaultAxis) < 0.f )
	{
		RotationAxis = -RotationAxis;
		RotationAngle = -RotationAngle;
	}

	// Make sure it is the shortest angle.
	RotationAngle = FMath::UnwindRadians(RotationAngle);

	// New bone rotation
	FQuat OutQuat = ReferenceQuat * FQuat(RotationAxis, RotationAngle* InMultiplier);
	// Normalize resulting quaternion.
	OutQuat.Normalize();

#if 0 //DEBUG_TWISTBONECONTROLLER
	UE_LOG(LogSkeletalControl, Log, TEXT("\t RefQuat: %s, Rot: %s"), *ReferenceQuat.ToString(), *ReferenceQuat.Rotator().ToString() );
	UE_LOG(LogSkeletalControl, Log, TEXT("\t NewQuat: %s, Rot: %s"), *OutQuat.ToString(), *OutQuat.Rotator().ToString() );
	UE_LOG(LogSkeletalControl, Log, TEXT("\t RollAxis: %s, RollAngle: %f"), *RotationAxis.ToString(), RotationAngle );
#endif

	return OutQuat;
}