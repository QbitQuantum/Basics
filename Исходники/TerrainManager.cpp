bool UTerrainManager::LoadBiome(EBiomeEnum biome)
{
	FString biomeName;
	switch (biome)
	{
	case EBiomeEnum::VE_Rock:
		biomeName = TEXT("Rock");
		break;
	case EBiomeEnum::VE_Lava:
		biomeName = TEXT("Lava");
		break;
	case EBiomeEnum::VE_Ice:
		biomeName = TEXT("Ice");
		break;
	}
	FString lrrpath = FPaths::Combine(TEXT("LegoRR0"), TEXT("World"), TEXT("WorldTextures"), *(biomeName + TEXT("Split")));
	if (BiomeMaterials.Num() == 0)
		BiomeMaterials.SetNumZeroed(78, true);
	for (int i = 0; i < 78; ++i)
	{
		FString texturePath = FPaths::Combine(TEXT("E:"), TEXT("LegoRR"), *lrrpath, *FString::Printf(TEXT("%s%02d.BMP"), *biomeName.ToUpper(), i));
		UTexture2D* biomeTexture = pTextureManager->GetTexture(*texturePath);
		if (biomeTexture) {
			if (BiomeMaterials[i] == nullptr) {
				BiomeMaterials[i] = UMaterialInstanceDynamic::Create(BiomeMaterialBase, this);
			}
			BiomeMaterials[i]->SetTextureParameterValue(TEXT("DiffuseTexture"), biomeTexture);
		}
	}

	return true;
}