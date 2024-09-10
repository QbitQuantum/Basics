	/**
	 * Minimal initialization constructor.
	 * @param InOwner - The UTextureCube which this FTextureCubeResource represents.
	 */
	FTextureCubeResource(UTextureCube* InOwner)
	:	Owner(InOwner)
	,	TextureSize(0)
	{
		//Initialize the MipData array
		for ( int32 FaceIndex=0;FaceIndex<6; FaceIndex++)
		{
			for( int32 MipIndex=0; MipIndex<ARRAY_COUNT(MipData[FaceIndex]); MipIndex++ )
			{
				MipData[FaceIndex][MipIndex] = NULL;
			}
		}

		check(Owner->GetNumMips() > 0);

		TIndirectArray<FTexture2DMipMap>& Mips = InOwner->PlatformData->Mips;
		for( int32 MipIndex=0; MipIndex<Mips.Num(); MipIndex++ )
		{
			FTexture2DMipMap& Mip = Mips[MipIndex];
			if( Mip.BulkData.GetBulkDataSize() <= 0 )
			{
				UE_LOG(LogTexture, Error, TEXT("Corrupt texture [%s]! Missing bulk data for MipIndex=%d"),*InOwner->GetFullName(),MipIndex );
			}
			else			
			{
				TextureSize += Mip.BulkData.GetBulkDataSize();
				uint32 MipSize = Mip.BulkData.GetBulkDataSize() / 6;

				uint8* In = (uint8*)Mip.BulkData.Lock(LOCK_READ_ONLY);

				for(uint32 Face = 0; Face < 6; ++Face)
				{
					MipData[Face][MipIndex] = FMemory::Malloc(MipSize);
					FMemory::Memcpy(MipData[Face][MipIndex], In + MipSize * Face, MipSize);
				}

				Mip.BulkData.Unlock();
			}
		}
		STAT( LODGroupStatName = TextureGroupStatFNames[InOwner->LODGroup] );
	}