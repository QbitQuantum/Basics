void AStealthArea::CalculateVisibility(AGameCharacter* calculatingUnit, TArray<AGameCharacter*>& sightList, TArray<AGameCharacter*>& availableUnits)
{
	if (!IsValid(calculatingUnit))
		return;

	//first get visible units on the outside based on increased radial area
	TArray<AActor*> ignoreList;
	for (AGameCharacter* gc : availableUnits)
		ignoreList.AddUnique(gc);

	for (AGameCharacter* gc : availableUnits)
	{
		if (occupyingUnits.Contains(gc)) //don't account for units in this area yet
			continue;

		if (gc->GetTeamIndex() == calculatingUnit->GetTeamIndex())
		{
			sightList.AddUnique(gc);
			continue;
		}

		FVector start = GetActorLocation();
		FVector end = gc->GetActorLocation();

		if ((start - end).SizeSquared2D() <= FMath::Square(calculatingUnit->sightRadius * 1.15f))
		{
			FHitResult hit;
			FCollisionQueryParams collisionParams;

			TArray<AActor*> ignoredActors = ignoreList;
			ignoredActors.Remove(gc);

			collisionParams.AddIgnoredActors(ignoredActors);
			collisionParams.AddIgnoredActor(this);

			GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, collisionParams);

			if (hit.GetActor() == gc)
			{
				if (!IsValid(gc->currentStealthArea))
					sightList.AddUnique(gc);
			}
		}
	}

	//finally add all of the units that are currently in the area
	for (AGameCharacter* gc : occupyingUnits)
	{
		if (IsValid(gc))
			sightList.AddUnique(gc);
		else
			sightList.Remove(gc);
	}
}