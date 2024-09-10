void AAirCurrent::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Duration += DeltaSeconds;
	if (HasAuthority())
	{
		TArray<AActor* > OverlappedActors;
		CollisionComp->GetOverlappingActors(OverlappedActors);
		for (int32 i = 0; i < OverlappedActors.Num(); i++)
		{
			ATotemCharacter* TotemCharacter = Cast<ATotemCharacter>(OverlappedActors[i]);
			if (TotemCharacter && !TotemCharacter->IsPendingKill() && !TotemCharacter->Invincible())
			{
				FRotator rot = GetActorRotation();
				FVector LaunchDir = rot.Vector();
				LaunchDir.Normalize(0.01f);
				LaunchDir *= LaunchSpeed;

				//EMovementMode mode = TotemCharacter->CharacterMovement->MovementMode;
				//TotemCharacter->LaunchCharacter(LaunchDir, true, true);
				//TotemCharacter->GetCharacterMovement()->Velocity += LaunchDir;
				TotemCharacter->LaunchCharacter(LaunchDir, false, false);
				//TotemCharacter->CharacterMovement->AddForce(LaunchDir);
				//TotemCharacter->CharacterMovement->SetMovementMode(mode);
			}
			
			//add a lot of type check, hope fix the crash
			UActorComponent* actorComp = OverlappedActors[i]->GetComponentByClass(UProjectileMovementComponent::StaticClass());
			if (actorComp !=nullptr)
			{
				UProjectileMovementComponent* movementComp = Cast<UProjectileMovementComponent>(actorComp);
				if (movementComp && !movementComp->IsPendingKill())
				{
					FRotator rot = GetActorRotation();
					FVector LaunchDir = rot.Vector();
					LaunchDir.Normalize(0.01f);
					if (movementComp)
					{
						LaunchDir *= movementComp->GetMaxSpeed();
						movementComp->Velocity = LaunchDir;
					}
				}
			}
			
		}
	}	
}