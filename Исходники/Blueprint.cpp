bool UBlueprint::ChangeOwnerOfTemplates()
{
	UBlueprintGeneratedClass* BPGClass = Cast<UBlueprintGeneratedClass>(*GeneratedClass);
	bool bIsStillStale = false;
	if (BPGClass)
	{
		check(!bIsRegeneratingOnLoad);

		// >>> Backwards Compatibility:  VER_UE4_EDITORONLY_BLUEPRINTS
		bool bMigratedOwner = false;
		for( auto CompIt = ComponentTemplates.CreateIterator(); CompIt; ++CompIt )
		{
			UActorComponent* Component = (*CompIt);
			check(Component);
			if(Component->GetOuter() == this)
			{
				const bool bRenamed = Component->Rename(*Component->GetName(), BPGClass, REN_ForceNoResetLoaders|REN_DoNotDirty);
				ensure(bRenamed);
				bIsStillStale |= !bRenamed;
				bMigratedOwner = true;
			}
		}

		for( auto CompIt = Timelines.CreateIterator(); CompIt; ++CompIt )
		{
			UTimelineTemplate* Template = (*CompIt);
			check(Template);
			if(Template->GetOuter() == this)
			{
				const FString OldTemplateName = Template->GetName();
				ensure(!OldTemplateName.EndsWith(TEXT("_Template")));
				const bool bRenamed = Template->Rename(*UTimelineTemplate::TimelineVariableNameToTemplateName(Template->GetFName()), BPGClass, REN_ForceNoResetLoaders|REN_DoNotDirty);
				ensure(bRenamed);
				bIsStillStale |= !bRenamed;
				ensure(OldTemplateName == UTimelineTemplate::TimelineTemplateNameToVariableName(Template->GetFName()));
				bMigratedOwner = true;
			}
		}

		if(USimpleConstructionScript* SCS = SimpleConstructionScript)
		{
			if(SCS->GetOuter() == this)
			{
				const bool bRenamed = SCS->Rename(NULL, BPGClass, REN_ForceNoResetLoaders|REN_DoNotDirty);
				ensure(bRenamed);
				bIsStillStale |= !bRenamed;
				bMigratedOwner = true;
			}
		}

		if (bMigratedOwner)
		{
			BPGClass->ComponentTemplates = ComponentTemplates;
			BPGClass->Timelines = Timelines;
			BPGClass->SimpleConstructionScript = SimpleConstructionScript;
		}
		// <<< End Backwards Compatibility
	}
	else
	{
		UE_LOG(LogBlueprint, Log, TEXT("ChangeOwnerOfTemplates: No BlueprintGeneratedClass in %s"), *GetName());
	}
	return !bIsStillStale;
}