USCS_Node* USimpleConstructionScript::CreateNode(UClass* NewComponentClass, FName NewComponentVariableName)
{
	UBlueprint* Blueprint = GetBlueprint();
	check(Blueprint);
	check(NewComponentClass->IsChildOf(UActorComponent::StaticClass()));
	ensure(Cast<UBlueprintGeneratedClass>(Blueprint->GeneratedClass));

	// note that naming logic is duplicated in CreateNodeAndRenameComponent:
	NewComponentVariableName = GenerateNewComponentName(NewComponentClass, NewComponentVariableName);

	// A bit of a hack, but by doing this we ensure that the original object isn't outered to the BPGC. That way if we undo this action later, it'll rename the template away from the BPGC.
	// This is necessary because of our template object naming scheme that's in place to ensure deterministic cooking. We have to keep the SCS node and template object names in sync as a result,
	// and leaving the template outered to the BPGC can lead to template object name collisions when attempting to rename the remaining SCS nodes. See USCS_Node::NameWasModified() for more details.
	UActorComponent* NewComponentTemplate = NewObject<UActorComponent>(GetTransientPackage(), NewComponentClass, NAME_None, RF_ArchetypeObject | RF_Transactional | RF_Public);

	// Record initial object state in case we're in a transaction context.
	NewComponentTemplate->Modify();

	// Now set the actual name and outer to the BPGC.
	NewComponentTemplate->Rename(*(NewComponentVariableName.ToString() + UActorComponent::ComponentTemplateNameSuffix), Blueprint->GeneratedClass, REN_DoNotDirty|REN_DontCreateRedirectors|REN_ForceNoResetLoaders);

	return CreateNodeImpl(NewComponentTemplate, NewComponentVariableName);
}