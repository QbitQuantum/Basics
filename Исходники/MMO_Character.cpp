void AMMO_Character::MeleeAttackRaycasts()
{
	FVector BaseSocketLoc = Player_SkeletalMeshComponent->GetSocketLocation(FName("Sword_joint"));
	FVector TipSocketLoc = Player_SkeletalMeshComponent->GetSocketLocation(FName("Sword_Edge"));

	const int sub = 32;
	float curLength = (BaseSocketLoc - TipSocketLoc).Size() * 2;
	float prevLength = (prevBase - prevTip).Size();
	for (int i = 1; i < sub; i++)
	{
		FVector tmpBase = FMath::Lerp(BaseSocketLoc, prevBase, i / float(sub));
		FVector tmpTip = FMath::Lerp(TipSocketLoc, prevTip, i / float(sub));
		FVector tmpOff = (tmpTip - tmpBase);
		tmpOff.Normalize();
	}
	prevBase = BaseSocketLoc;
	prevTip = TipSocketLoc;

	FHitResult Hit;
	FCollisionQueryParams ColParams = FCollisionQueryParams(FName("NoName"), false, GetOwner());
	ColParams.AddIgnoredActor(GetOwner());
	ColParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(Hit, BaseSocketLoc, TipSocketLoc, ECollisionChannel::ECC_WorldDynamic, ColParams))
	{
		if (Hit.Actor != GetOwner() && AnimInstance->bCanDamageMelee)
		{
			if (Cast<AMMO_Mob_Character>(Hit.Actor.Get()))
			{
				if (!Cast<AMMO_Mob_Character>(Hit.Actor.Get())->bIsDead && !Cast<AMMO_Mob_Character>(Hit.Actor.Get())->bIsImmunized)
				{
					if (Role < ROLE_Authority)
					{
						AnimInstance->bCanDamageMelee = false;
						GetDamage(BaseAttack, AttackBonusMin, AttackBonusMax, Cast<AMMO_Mob_Character>(Hit.Actor.Get()));
					}
				}
			}
			else if (Cast<ABoss>(Hit.Actor.Get()))
			{
				if (!Cast<ABoss>(Hit.Actor.Get())->bIsDead)
				{
					if (Role < ROLE_Authority)
					{
						AnimInstance->bCanDamageMelee = false;

						GetDamage_Boss(BaseAttack, AttackBonusMin, AttackBonusMax, Cast<ABoss>(Hit.Actor.Get()));
					}
				}
			}
		}
	}
}