UActorComponent* USCS_Node::ExecuteNodeOnActor(AActor* Actor, USceneComponent* ParentComponent, const FTransform* RootTransform, bool bIsDefaultTransform)
{
	check(Actor != nullptr);
	check((ParentComponent != nullptr && !ParentComponent->IsPendingKill()) || (RootTransform != nullptr)); // must specify either a parent component or a world transform

	auto ActualBPGC = Cast<UBlueprintGeneratedClass>(Actor->GetClass());
	UActorComponent* ActualComponentTemplate = GetActualComponentTemplate(ActualBPGC);

	// Create a new component instance based on the template
	UActorComponent* NewActorComp = Actor->CreateComponentFromTemplate(ActualComponentTemplate, VariableName.ToString());
	if(NewActorComp != nullptr)
	{
		NewActorComp->CreationMethod = EComponentCreationMethod::SimpleConstructionScript;
		// SCS created components are net addressable
		NewActorComp->SetNetAddressable();

		// Special handling for scene components
		USceneComponent* NewSceneComp = Cast<USceneComponent>(NewActorComp);
		if (NewSceneComp != nullptr)
		{
			// If NULL is passed in, we are the root, so set transform and assign as RootComponent on Actor
			if (ParentComponent == nullptr || (ParentComponent && ParentComponent->IsPendingKill()))
			{
				FTransform WorldTransform = *RootTransform;
				if(bIsDefaultTransform)
				{
					// Note: We use the scale vector from the component template when spawning (to match what happens with a native root)
					WorldTransform.SetScale3D(NewSceneComp->RelativeScale3D);
				}
				NewSceneComp->SetWorldTransform(WorldTransform);
				Actor->SetRootComponent(NewSceneComp);
			}
			// Otherwise, attach to parent component passed in
			else
			{
				NewSceneComp->AttachTo(ParentComponent, AttachToName);
			}
		}

		// Call function to notify component it has been created
		NewActorComp->OnComponentCreated();

		if (NewActorComp->GetIsReplicated())
		{
			// Make sure this component is added to owning actor's replicated list.
			NewActorComp->SetIsReplicated(true);
		}

		// If we want to save this to a property, do it here
		FName VarName = GetVariableName();
		if (VarName != NAME_None)
		{
			UClass* ActorClass = Actor->GetClass();
			if (UObjectPropertyBase* Prop = FindField<UObjectPropertyBase>(ActorClass, VarName))
			{
				Prop->SetObjectPropertyValue_InContainer(Actor, NewActorComp);
			}
			else
			{
				UE_LOG(LogBlueprint, Log, TEXT("ExecuteNodeOnActor: Couldn't find property '%s' on '%s"), *VarName.ToString(), *Actor->GetName());
#if WITH_EDITOR
				// If we're constructing editable components in the SCS editor, set the component instance corresponding to this node for editing purposes
				USimpleConstructionScript* SCS = GetSCS();
				if(SCS != nullptr && (SCS->IsConstructingEditorComponents() || SCS->GetComponentEditorActorInstance() == Actor))
				{
					EditorComponentInstance = NewSceneComp;
				}
#endif
			}
		}

		// Determine the parent component for our children (it's still our parent if we're a non-scene component)
		USceneComponent* ParentSceneComponentOfChildren = (NewSceneComp != nullptr) ? NewSceneComp : ParentComponent;

		// If we made a component, go ahead and process our children
		for (int32 NodeIdx = 0; NodeIdx < ChildNodes.Num(); NodeIdx++)
		{
			USCS_Node* Node = ChildNodes[NodeIdx];
			check(Node != nullptr);
			Node->ExecuteNodeOnActor(Actor, ParentSceneComponentOfChildren, nullptr, false);
		}
	}

	return NewActorComp;
}