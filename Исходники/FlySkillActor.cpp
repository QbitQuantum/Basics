// Called every frame
void AFlySkillActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (!IsReadyToStart)
	{
		return;
	}
	if (AttackCollision.Num() > 0)
	{
		Injury();
	}
	float move = DeltaTime * MoveSpeed;
	FVector ourpos = GetActorLocation();
	FVector dstpos;
	if (UseTargetLocation)
	{
		dstpos = TargetLocation;
	}
	else
	{
		dstpos = TargetActor->GetActorLocation();;
	}
	float dis = FVector::Dist(ourpos, dstpos);
	if (move >= dis)
	{
		SetActorLocation(dstpos);
	}
	else
	{
		FVector dir = dstpos - ourpos;
		dir.Normalize();
		dir *= move;
		SetActorLocation(ourpos + dir);
	}
	if (dis < 1 && !PrepareDestory)
	{
		BulletParticle->SetActive(false);
		PrepareDestory = true;
		DestoryCount = 0;
	}
	if (PrepareDestory)
	{
		DestoryCount += DeltaTime;
		if (DestoryCount >= DestroyDelay)
		{
			this->Destroy();
		}
	}
}