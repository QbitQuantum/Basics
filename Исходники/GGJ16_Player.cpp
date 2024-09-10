float AGGJ16_Player::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (!bDamaged)
	{
		health -= DamageAmount;
	}

	if (health <= 0)
	{
		playDeathAnim = true;
	}
	else
	{
		bDamaged = true;
	}

	if (DamageCauser)
	{
		FVector curForwardVector = DamageCauser->GetActorLocation() - this->GetActorLocation();
		curForwardVector.ProjectOnTo(FVector(1, 1, 0));
		curForwardVector.Normalize();
		LaunchCharacter(curForwardVector * KnockBackAlpha, true, true);
	}

	return 0.f;
	//do the pretty things
};