// Called every frame
void AMovingPlatform::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (bIsActive)
	{
		if (GetActorLocation().Equals(Target1, 2.0f)) CurrentTarget = Target2;
		else if (GetActorLocation().Equals(Target2, 2.0f)) CurrentTarget = Target1;
		FVector Direction = CurrentTarget - GetActorLocation();
		Direction.Normalize();
		Direction *= PlatformSpeed * DeltaTime;
		AddActorWorldTransform(FTransform(Direction));
	}
}