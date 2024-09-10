void FComponentEditorUtils::AdjustComponentDelta(USceneComponent* Component, FVector& Drag, FRotator& Rotation)
{
	USceneComponent* ParentSceneComp = Component->GetAttachParent();
	if (ParentSceneComp)
	{
		const FTransform ParentToWorldSpace = ParentSceneComp->GetSocketTransform(Component->AttachSocketName);

		if (!Component->bAbsoluteLocation)
		{
			//transform the drag vector in relative to the parent transform
			Drag = ParentToWorldSpace.InverseTransformVectorNoScale(Drag);
			//Now that we have a global drag we can apply the parent scale
			Drag = Drag * ParentToWorldSpace.Inverse().GetScale3D();
		}

		if (!Component->bAbsoluteRotation)
		{
			Rotation = ( ParentToWorldSpace.Inverse().GetRotation() * Rotation.Quaternion() * ParentToWorldSpace.GetRotation() ).Rotator();
		}
	}
}