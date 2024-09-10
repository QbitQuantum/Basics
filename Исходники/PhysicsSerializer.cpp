FByteBulkData* UPhysicsSerializer::GetBinaryData(FName Format, const TArray<FBodyInstance*>& Bodies, const TArray<class UBodySetup*>& BodySetups, const TArray<class UPhysicalMaterial*>& PhysicalMaterials)
{
	if (!FParse::Param(FCommandLine::Get(), TEXT("PhysxSerialization")))
	{
		return nullptr;
	}

#if PLATFORM_MAC
	return nullptr;	//This is not supported right now
#endif

	QUICK_SCOPE_CYCLE_COUNTER(STAT_GetBinaryData);
	const bool bContainedData = BinaryFormatData.Contains(Format);
	FByteBulkData* Result = &BinaryFormatData.GetFormat(Format);
	if (!FParse::Param(FCommandLine::Get(), TEXT("NoPhysxAlignment")))
	{
		Result->SetBulkDataAlignment(PHYSX_SERIALIZATION_ALIGNMENT);
	}
	
	if (!bContainedData)
	{
#if WITH_EDITOR
#if WITH_PHYSX
		TArray<uint8> OutData;
		FDerivedDataPhysXBinarySerializer* DerivedPhysXSerializer = new FDerivedDataPhysXBinarySerializer(Format, Bodies, BodySetups, PhysicalMaterials, FGuid::NewGuid()); //TODO: Maybe it's worth adding this to the DDC. For now there's a lot of complexity with the guid invalidation so I've left it out.
		if (DerivedPhysXSerializer->CanBuild())
		{

			DerivedPhysXSerializer->Build(OutData);
#endif
			if (OutData.Num())
			{
				Result->Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(Result->Realloc(OutData.Num()), OutData.GetData(), OutData.Num());
				Result->Unlock();
			}
		}
		else
#endif
		{
			UE_LOG(LogPhysics, Warning, TEXT("Attempt to use binary physics data but we are unable to."));
		}
	}

	return Result->GetBulkDataSize() > 0 ? Result : nullptr;
}