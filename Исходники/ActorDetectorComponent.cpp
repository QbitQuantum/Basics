void UActorDetectorComponent::RunDetection()
{
	TArray<AActor*> OverlappingActors;
	GetOwner()->GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.Num() > 0)
	{
		for (size_t i = 0; i < OverlappingActors.Num(); i++)
		{
			if (OverlappingActors[i]->ActorHasTag(TagToDetect))
			{
				// Get directions
				FVector OwnerDirection = GetOwner()->GetActorForwardVector();
				FVector ActorDirection = OverlappingActors[i]->GetActorLocation() - GetOwner()->GetActorLocation();

				// Normalize vectors
				OwnerDirection.Normalize();
				ActorDirection.Normalize();

				// Calculate angle
				float AngleFromForward = FMath::RadiansToDegrees(acosf(FVector::DotProduct(OwnerDirection, ActorDirection)));
				if (AngleFromForward < MaxAngleDetection)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Lanzo Broadcast"));
					ActorDetected.Broadcast(OverlappingActors[i]);
				}
				//UE_LOG(LogTemp, Warning, TEXT("Tiene tag Name: %s y angulo %f, max %f"), *(OverlappingActors[i]->GetName()), AngleFromForward, MaxAngleDetection);
			}
		}
	}
}