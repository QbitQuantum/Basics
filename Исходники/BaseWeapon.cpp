void ABaseWeapon::Instant_Fire()
{
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream(RandomSeed);
	const float CurrentSpread = WeaponConfig.WeaponSpread;
	const float SpreadCone = FMath::DegreesToRadians(WeaponConfig.WeaponSpread * 0.5);
	const FVector AimDir = MyPawn->GetActorForwardVector();
	const FVector StartTrace = MyPawn->GetActorLocation();
	const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, SpreadCone, SpreadCone);
	FVector EndTrace;

	if (Target)
	{
		FVector TargetDir = (MyPawn->GetActorLocation() - Target->GetActorLocation());
		TargetDir.Normalize();
		FVector ShootDir2 = WeaponRandomStream.VRandCone(-TargetDir, SpreadCone, SpreadCone);
		EndTrace = StartTrace + ShootDir2 * WeaponConfig.WeaponRange;
	}
	else
	{
		EndTrace = StartTrace + ShootDir * WeaponConfig.WeaponRange;
	}

	const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
	SpawnParticle(EndTrace);
	HitActor = Cast<AActor>(Impact.GetActor());

	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 1.0f);

	if (HitActor)
	{
		Server_DealDamage(Impact, ShootDir, WeaponConfig);
	}
}