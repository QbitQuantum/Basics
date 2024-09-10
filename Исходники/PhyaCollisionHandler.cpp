void UPhyaCollisionHandler::HandlePhysicsCollisions_AssumesLocked(TArray<FCollisionNotifyInfo>& PendingCollisionNotifies)
{
	if(GetWorld()->HasBegunPlay())
	{
		TMap< FPhyaBodyInstancePair, TSharedPtr<FPhyaPairInfo> > ExpiredPairHash = PairHash;

		for(int32 InfoIdx=0; InfoIdx<PendingCollisionNotifies.Num(); InfoIdx++)
		{
			const FCollisionNotifyInfo& Info = PendingCollisionNotifies[InfoIdx];
			FPhyaBodyInstancePair Pair(Info.Info0.GetBodyInstance(), Info.Info1.GetBodyInstance());
			// Find pair in hash
			TSharedPtr<FPhyaPairInfo> PairInfo = PairHash.FindRef(Pair);

			// Existing pair
			if(PairInfo.IsValid())
			{
				UE_LOG(LogTemp, Log, TEXT("EXISTING"));

				ExpiredPairHash.Remove(Pair); // Not expired
			}
			// New pair
			else
			{
				UE_LOG(LogTemp, Log, TEXT("NEW"));

				PairInfo = MakeShareable( new FPhyaPairInfo );
				PairHash.Add(Pair, PairInfo);

				paImpact* Impact = paImpact::newImpact();
				if(Impact != NULL)
				{
					Impact->setBody1(Bodies[0]);

					paImpactDynamicData ImpactData;
					ImpactData.relTangentSpeedAtImpact = 0; // No skid.
					ImpactData.impactImpulse = 1.0;

					Impact->setDynamicData(&ImpactData);
				}
			}

		}

		// Expire pairs from PairHash still in ExpiredPairHash
		for( auto It = ExpiredPairHash.CreateConstIterator(); It; ++It )
		{
			UE_LOG(LogTemp, Log, TEXT("EXPIRE"));
			FPhyaBodyInstancePair Pair = It.Key();
			PairHash.Remove(Pair);
		}

		/*
		float WorldTime = GetWorld()->GetTimeSeconds();
		float TimeSinceLastTestImpact = WorldTime - LastTestImpactTime;
		if(TimeSinceLastTestImpact > 1.f)
		{
			TestImpact();
			LastTestImpactTime = WorldTime;
		}
		*/
	}
}