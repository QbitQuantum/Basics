UActorComponent* AActor::CreateComponentFromTemplate(UActorComponent* Template, const FString& InName)
{
	UActorComponent* NewActorComp = NULL;
	if(Template != NULL)
	{
		// If there is a Component with this name already (almost certainly because it is an Instance component), we need to rename it out of the way
		if (!InName.IsEmpty())
		{
			UObject* ConflictingObject = FindObjectFast<UObject>(this, *InName);
			if (ConflictingObject && ConflictingObject->IsA<UActorComponent>() && CastChecked<UActorComponent>(ConflictingObject)->CreationMethod == EComponentCreationMethod::Instance)
			{		
				// Try and pick a good name
				FString ConflictingObjectName = ConflictingObject->GetName();
				int32 CharIndex = ConflictingObjectName.Len()-1;
				while (FChar::IsDigit(ConflictingObjectName[CharIndex]))
				{
					--CharIndex;
				}
				int32 Counter = 0;
				if (CharIndex < ConflictingObjectName.Len()-1)
				{
					Counter = FCString::Atoi(*ConflictingObjectName.RightChop(CharIndex+1));
					ConflictingObjectName = ConflictingObjectName.Left(CharIndex+1);
				}
				FString NewObjectName;
				do
				{
					NewObjectName = ConflictingObjectName + FString::FromInt(++Counter);
					
				} while (FindObjectFast<UObject>(this, *NewObjectName) != nullptr);

				ConflictingObject->Rename(*NewObjectName, this);
			}
		}

		// Note we aren't copying the the RF_ArchetypeObject flag. Also note the result is non-transactional by default.
		NewActorComp = (UActorComponent*)StaticDuplicateObject(Template, this, *InName, RF_AllFlags & ~(RF_ArchetypeObject|RF_Transactional|RF_WasLoaded|RF_Public|RF_InheritableComponentTemplate) );

		NewActorComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;

		// Need to do this so component gets saved - Components array is not serialized
		BlueprintCreatedComponents.Add(NewActorComp);
	}
	return NewActorComp;
}