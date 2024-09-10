void UDebugSkelMeshComponent::ConsumeRootMotion(const FVector& FloorMin, const FVector& FloorMax)
{
	//Extract root motion regardless of where we use it so that we don't hit
	//problems with it building up in the instance

	FRootMotionMovementParams ExtractedRootMotion;

	if (UAnimInstance* AnimInst = GetAnimInstance())
	{
		ExtractedRootMotion = AnimInst->ConsumeExtractedRootMotion(1.f);
	}

	if (bPreviewRootMotion)
	{
		if (ExtractedRootMotion.bHasRootMotion)
		{
			AddLocalTransform(ExtractedRootMotion.RootMotionTransform);

			//Handle moving component so that it stays within the editor floor
			FTransform CurrentTransform = GetRelativeTransform();
			FVector Trans = CurrentTransform.GetTranslation();
			Trans.X = WrapInRange(Trans.X, FloorMin.X, FloorMax.X);
			Trans.Y = WrapInRange(Trans.Y, FloorMin.Y, FloorMax.Y);
			CurrentTransform.SetTranslation(Trans);
			SetRelativeTransform(CurrentTransform);
		}
	}
	else
	{
		if (TurnTableMode == EPersonaTurnTableMode::Stopped)
		{
			SetWorldTransform(FTransform());
		}
		else
		{
			SetRelativeLocation(FVector::ZeroVector);
		}
	}
}