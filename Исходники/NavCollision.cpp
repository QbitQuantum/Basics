FByteBulkData* UNavCollision::GetCookedData(FName Format)
{
	if (IsTemplate())
	{
		return NULL;
	}
	
	bool bContainedData = CookedFormatData.Contains(Format);
	FByteBulkData* Result = &CookedFormatData.GetFormat(Format);

	if (!bContainedData)
	{
		if (FPlatformProperties::RequiresCookedData())
		{
			UE_LOG(LogNavigation, Fatal, TEXT("Attempt to build nav collision data for %s when we are unable to. This platform requires cooked packages."), *GetPathName());
		}
		
		TArray<uint8> OutData;
		FDerivedDataNavCollisionCooker* DerivedNavCollisionData = new FDerivedDataNavCollisionCooker(Format, this);
		if (DerivedNavCollisionData->CanBuild() 
			&& GetDerivedDataCacheRef().GetSynchronous(DerivedNavCollisionData, OutData))
		{
			if (OutData.Num())
			{
				Result->Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(Result->Realloc(OutData.Num()), OutData.GetData(), OutData.Num());
				Result->Unlock();
			}
		}
	}

	check(Result);
	return Result->GetBulkDataSize() > 0 ? Result : NULL; // we don't return empty bulk data...but we save it to avoid thrashing the DDC
}