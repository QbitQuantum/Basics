	/**
	 * Recursively transverses the reference tree
	 */
	void OutputReferencedAssets(FOutputDeviceFile& FileAr, int32 CurrentDepth, FString ParentId, UObject* BaseObject, TArray<UObject*>* AssetList)
	{
		check(AssetList);

		const FString ScriptItemString = NSLOCTEXT("UnrealEd", "Script", "Script").ToString();
		const FString DefaultsItemString = NSLOCTEXT("UnrealEd", "Defaults", "Defaults").ToString();
		for (int32 AssetIndex = 0; AssetIndex < AssetList->Num(); AssetIndex++)
		{
			UObject* ReferencedObject = (*AssetList)[AssetIndex];
			check(ReferencedObject);

			// get the list of assets this object is referencing
			TArray<UObject*>* ReferencedAssets = ReferenceGraph.Find(ReferencedObject);
			
			// add a new tree item for this referenced asset
			FString ItemString;
			if (ReferencedObject == BaseObject->GetClass())
			{
				ItemString = *ScriptItemString;
				if (ReferencedAssets == NULL || ReferencedAssets->Num() == 0)
				{
					// special case for the "Script" node - don't add it if it doesn't have any children
					continue;
				}
			}
			else if (ReferencedObject == BaseObject->GetArchetype())
			{
				ItemString = *DefaultsItemString;
				if (ReferencedAssets == NULL || ReferencedAssets->Num() == 0)
				{
					// special case for the "Defaults" node - don't add it if it doesn't have any children
					continue;
				}
			}
			else
			{
				if (CurrentDepth > 0)
				{
					ItemString = ReferencedObject->GetPathName();
				}
				else
				{
					ItemString = GetObjectNameFromCache(ReferencedObject);
				}
			}

			FString AssetId = FString::Printf(TEXT("%s.%d"), *ParentId, AssetIndex);
			
			if (CurrentDepth > 0)
			{
				FString TabStr;
				for (int32 i = 0; i < CurrentDepth; ++i)
				{
					TabStr += TEXT("\t");
				}

				FileAr.Logf(TEXT("%s(%s) %s"), *TabStr, *AssetId, *ItemString);
			}
			else
			{
				OutputDetailsItem(FileAr, AssetId, ReferencedObject, ItemString);
			}

			if (ReferencedAssets != NULL)
			{
				// If this object is referencing other objects, output those objects
				OutputReferencedAssets(FileAr, (CurrentDepth == 0)? 0: CurrentDepth + 1, AssetId, ReferencedObject, ReferencedAssets);
			}
		}
	}