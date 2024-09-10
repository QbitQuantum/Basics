FMatrix USkeletalMeshComponent::GetTransformMatrix() const
{
	FTransform RootTransform = GetBoneTransform(0);
	FVector Translation;
	FQuat Rotation;
	
	// if in editor, it should always use localToWorld
	// if root motion is ignored, use root transform 
	if( GetWorld()->IsGameWorld() || !SkeletalMesh )
	{
		// add root translation info
		Translation = RootTransform.GetLocation();
	}
	else
	{
		Translation = ComponentToWorld.TransformPosition(SkeletalMesh->RefSkeleton.GetRefBonePose()[0].GetTranslation());
	}

	// if root rotation is ignored, use root transform rotation
	Rotation = RootTransform.GetRotation();

	// now I need to get scale
	// only LocalToWorld will have scale
	FVector ScaleVector = ComponentToWorld.GetScale3D();

	Rotation.Normalize();
	return FScaleMatrix(ScaleVector)*FQuatRotationTranslationMatrix(Rotation, Translation);
}