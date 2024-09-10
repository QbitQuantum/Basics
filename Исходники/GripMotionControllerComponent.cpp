bool UGripMotionControllerComponent::GripComponent(
	UPrimitiveComponent* ComponentToGrip, 
	const FTransform &WorldOffset, 
	bool bWorldOffsetIsRelative, 
	FName OptionalSnapToSocketName, 
	TEnumAsByte<EGripCollisionType> GripCollisionType, 
	bool bAllowSetMobility, 
	float GripStiffness, 
	float GripDamping, 
	bool bTurnOffLateUpdateWhenColliding
	)
{
	if (!bIsServer || !ComponentToGrip)
	{
		UE_LOG(LogTemp, Warning, TEXT("VRGripMotionController grab function was passed an invalid or already gripped component"));
		return false;
	}

	// Has to be movable to work
	if (ComponentToGrip->Mobility != EComponentMobility::Movable)
	{
		if (bAllowSetMobility)
			ComponentToGrip->SetMobility(EComponentMobility::Movable);
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("VRGripMotionController tried to grip a component set to static mobility and bAllowSetMobility is false"));
			return false; // It is not movable, can't grip it
		}
	}

	ComponentToGrip->IgnoreActorWhenMoving(this->GetOwner(), true);
	// So that events caused by sweep and the like will trigger correctly

	ComponentToGrip->AddTickPrerequisiteComponent(this);

	FBPActorGripInformation newActorGrip;
	newActorGrip.GripCollisionType = GripCollisionType;
	newActorGrip.Component = ComponentToGrip;
	
	if(ComponentToGrip->GetOwner())
		newActorGrip.bOriginalReplicatesMovement = ComponentToGrip->GetOwner()->bReplicateMovement;

	newActorGrip.Stiffness = GripStiffness;
	newActorGrip.Damping = GripDamping;
	newActorGrip.bTurnOffLateUpdateWhenColliding = bTurnOffLateUpdateWhenColliding;

	if (OptionalSnapToSocketName.IsValid() && ComponentToGrip->DoesSocketExist(OptionalSnapToSocketName))
	{
		// I inverse it so that laying out the sockets makes sense
		FTransform sockTrans = ComponentToGrip->GetSocketTransform(OptionalSnapToSocketName, ERelativeTransformSpace::RTS_Component);
		newActorGrip.RelativeTransform = sockTrans.Inverse();
		newActorGrip.RelativeTransform.SetScale3D(ComponentToGrip->GetComponentScale());
	}
	else if (bWorldOffsetIsRelative)
		newActorGrip.RelativeTransform = WorldOffset;
	else
		newActorGrip.RelativeTransform = WorldOffset.GetRelativeTransform(this->GetComponentTransform());

	NotifyGrip(newActorGrip);
	GrippedActors.Add(newActorGrip);

	return true;
}