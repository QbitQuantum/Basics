void UEnemyRoadSplineComponent::MoveCharacterlongSplineTrack(ACharacter* Actor)
{
	if (RoadSpline)
	{
		FVector DirectionToRun = RoadSpline->CalDirectionToRun(Actor, this);
		DirectionToRun.Normalize();
		DirectionToRun.Z = 0;

		Actor->AddMovementInput(DirectionToRun, 10);
		SetActorRotationMulticast(DirectionToRun.Rotation());
	}
}