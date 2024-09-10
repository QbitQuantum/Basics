	static void CleanAndSanitizeStruct(UUserDefinedStruct* StructToClean)
	{
		check(StructToClean);

		if (auto EditorData = Cast<UUserDefinedStructEditorData>(StructToClean->EditorData))
		{
			EditorData->CleanDefaultInstance();
		}

		const FString TransientString = FString::Printf(TEXT("TRASHSTRUCT_%s"), *StructToClean->GetName());
		const FName TransientName = MakeUniqueObjectName(GetTransientPackage(), UUserDefinedStruct::StaticClass(), FName(*TransientString));
		UUserDefinedStruct* TransientStruct = NewObject<UUserDefinedStruct>(GetTransientPackage(), TransientName, RF_Public | RF_Transient);

		TArray<UObject*> SubObjects;
		GetObjectsWithOuter(StructToClean, SubObjects, true);
		SubObjects.Remove(StructToClean->EditorData);
		for( auto SubObjIt = SubObjects.CreateIterator(); SubObjIt; ++SubObjIt )
		{
			UObject* CurrSubObj = *SubObjIt;
			CurrSubObj->Rename(NULL, TransientStruct, REN_DontCreateRedirectors);
			if( UProperty* Prop = Cast<UProperty>(CurrSubObj) )
			{
				FKismetCompilerUtilities::InvalidatePropertyExport(Prop);
			}
			else
			{
				FLinkerLoad::InvalidateExport(CurrSubObj);
			}
		}

		StructToClean->SetSuperStruct(NULL);
		StructToClean->Children = NULL;
		StructToClean->Script.Empty();
		StructToClean->MinAlignment = 0;
		StructToClean->RefLink = NULL;
		StructToClean->PropertyLink = NULL;
		StructToClean->DestructorLink = NULL;
		StructToClean->ScriptObjectReferences.Empty();
		StructToClean->PropertyLink = NULL;
		StructToClean->ErrorMessage.Empty();
	}