void ASWeaponInstant::SimulateInstantHit(const FVector& Origin)
{
	const FVector StartTrace = Origin;
	const FVector AimDir = GetAdjustedAim();
	const FVector EndTrace = StartTrace + (AimDir * WeaponRange);

 	const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
	if (Impact.bBlockingHit)
	{
		SpawnImpactEffects(Impact);
		SpawnTrailEffects(Impact.ImpactPoint);
	}
	else
	{
		SpawnTrailEffects(EndTrace);
	}

	// Do not spawn near-hit if we actually hit a pawn
	if (Impact.GetActor() && Impact.GetActor()->IsA(ASCharacter::StaticClass()))
	{
		return;
	}

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		// Find a locally controlled pawn that is not the instigator of the hit.
		ASCharacter* OtherPawn = Cast<ASCharacter>(*It);
		if (OtherPawn && OtherPawn != GetPawnOwner() && OtherPawn->IsLocallyControlled())
		{
			// Calculate shortest distance to point. (using the estimated eye height)
			const float DistanceToPawn = FVector::CrossProduct(AimDir, OtherPawn->GetActorLocation() - Origin).Size();

			/* Owner can be lost before client gets to simulate the hit. */
			ASCharacter* P = GetPawnOwner();
			if (P)
			{
				FVector LookAt = (OtherPawn->GetActorLocation() - GetPawnOwner()->GetActorLocation());
				LookAt.Normalize();
				float LookDot = FVector::DotProduct(AimDir, LookAt);

				if (DistanceToPawn < NearHitMaxDistance && LookDot > 0)
				{
					// TODO: Play at nearest "almost" hit location.
					const FVector SoundLocation = Origin + (AimDir * DistanceToPawn);

					// Volume is based on distance to missed shot
					float Volume = FMath::Clamp(1 - (DistanceToPawn / NearHitMaxDistance), 0.1f, 1.0f);

					UGameplayStatics::PlaySoundAtLocation(this, NearHitSound, /*SoundLocation*/ OtherPawn->GetActorLocation(), Volume);
				}
			}
		}
	}
}