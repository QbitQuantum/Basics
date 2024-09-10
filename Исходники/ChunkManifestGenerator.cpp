bool FChunkManifestGenerator::LoadAssetRegistry(const FString& SandboxPath, const TSet<FName>* PackagesToKeep)
{
	UE_LOG(LogChunkManifestGenerator, Display, TEXT("Loading asset registry."));

	// Load generated registry for each platform
	check(Platforms.Num() == 1);

	for (auto Platform : Platforms)
	{
		/*FString PlatformSandboxPath = SandboxPath.Replace(TEXT("[Platform]"), *Platform->PlatformName());
		FArchive* AssetRegistryReader = IFileManager::Get().CreateFileReader(*PlatformSandboxPath);*/

		FString PlatformSandboxPath = SandboxPath.Replace(TEXT("[Platform]"), *Platform->PlatformName());
		FArrayReader FileContents;
		if (FFileHelper::LoadFileToArray(FileContents, *PlatformSandboxPath) == false)
		{
			continue;
		}
		FArchive* AssetRegistryReader = &FileContents;

		TMap<FName, FAssetData*> SavedAssetRegistryData;
		TArray<FDependsNode*> DependencyData;
		if (AssetRegistryReader)
		{
			AssetRegistry.LoadRegistryData(*AssetRegistryReader, SavedAssetRegistryData, DependencyData);
		}
		for (auto& LoadedAssetData : AssetRegistryData)
		{
			if (PackagesToKeep &&
				PackagesToKeep->Contains(LoadedAssetData.PackageName) == false)
			{
				continue;
			}

			FAssetData* FoundAssetData = SavedAssetRegistryData.FindRef(LoadedAssetData.ObjectPath);
			if ( FoundAssetData )
			{
				LoadedAssetData.ChunkIDs.Append(FoundAssetData->ChunkIDs);
				
				SavedAssetRegistryData.Remove(LoadedAssetData.ObjectPath);
				delete FoundAssetData;
			}
		}

		for (const auto& SavedAsset : SavedAssetRegistryData)
		{
			if (PackagesToKeep && PackagesToKeep->Contains(SavedAsset.Value->PackageName))
			{ 
				AssetRegistryData.Add(*SavedAsset.Value);
			}
			
			delete SavedAsset.Value;
		}
		SavedAssetRegistryData.Empty();
	}
	return true;
}