void AActor::EditorApplyRotation(const FRotator& DeltaRotation, bool bAltDown, bool bShiftDown, bool bCtrlDown)
{
	if( RootComponent != NULL )
	{
		const FRotator Rot = RootComponent->GetAttachParent() != NULL ? GetActorRotation() : RootComponent->RelativeRotation;

		FRotator ActorRotWind, ActorRotRem;
		Rot.GetWindingAndRemainder(ActorRotWind, ActorRotRem);

		const FQuat ActorQ = ActorRotRem.Quaternion();
		const FQuat DeltaQ = DeltaRotation.Quaternion();
		const FQuat ResultQ = DeltaQ * ActorQ;
		const FRotator NewActorRotRem = FRotator( ResultQ );
		FRotator DeltaRot = NewActorRotRem - ActorRotRem;
		DeltaRot.Normalize();

		if( RootComponent->GetAttachParent() != NULL )
		{
			RootComponent->SetWorldRotation( Rot + DeltaRot );
		}
		else
		{
			// No attachment.  Directly set relative rotation (to support winding)
			RootComponent->SetRelativeRotation( Rot + DeltaRot );
		}
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("WARNING: EditorApplyRotation %s has no root component"), *GetName() );
	}
}