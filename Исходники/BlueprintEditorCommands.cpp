void FBlueprintSpawnNodeCommands::RegisterCommands()
{
	const FString ConfigSection = TEXT("BlueprintSpawnNodes");
	const FString SettingName = TEXT("Node");
	TArray< FString > NodeSpawns;
	GConfig->GetArray(*ConfigSection, *SettingName, NodeSpawns, GEditorPerProjectIni);

	for(int32 x = 0; x < NodeSpawns.Num(); ++x)
	{
		FString ClassName;
		if(!FParse::Value(*NodeSpawns[x], TEXT("Class="), ClassName))
		{
			// Could not find a class name, cannot continue with this line
			continue;
		}

		FString CommandLabel;
		UClass* FoundClass = FindObject<UClass>(ANY_PACKAGE, *ClassName, true);
		TSharedPtr< FNodeSpawnInfo > InfoPtr;

		if(FoundClass && FoundClass->IsChildOf(UEdGraphNode::StaticClass()))
		{
			// The class name matches that of a UEdGraphNode, so setup a spawn info that can generate UEdGraphNode graph actions
			UEdGraphNode* GraphNode = Cast<UEdGraphNode>(FoundClass->GetDefaultObject());

			CommandLabel = GraphNode->GetNodeTitle(ENodeTitleType::ListView).ToString();

			if(CommandLabel.Len() == 0)
			{
				CommandLabel = FoundClass->GetName();
			}

			InfoPtr = MakeShareable( new FEdGraphNodeSpawnInfo( FoundClass ) );
		}
		else if(UFunction* FoundFunction = FindObject<UFunction>(ANY_PACKAGE, *ClassName, true))
		{
			// The class name matches that of a function, so setup a spawn info that can generate function graph actions
			InfoPtr = MakeShareable( new FFunctionNodeSpawnInfo((UFunction*)FoundFunction));

			CommandLabel = FoundFunction->GetName();
		}
		else
		{
			// Check for a macro graph that matches the passed in class name
			for (TObjectIterator<UBlueprint> BlueprintIt; BlueprintIt; ++BlueprintIt)
			{
				UBlueprint* MacroBP = *BlueprintIt;
				if(MacroBP->BlueprintType == BPTYPE_MacroLibrary)
				{
					// getting 'top-level' of the macros
					for (TArray<UEdGraph*>::TIterator GraphIt(MacroBP->MacroGraphs); GraphIt; ++GraphIt)
					{
						UEdGraph* MacroGraph = *GraphIt;
						// The class name matches that of a macro, so setup a spawn info that can generate macro graph actions
						if(MacroGraph->GetName() == ClassName)
						{
							CommandLabel = MacroGraph->GetName();

							InfoPtr = MakeShareable( new FMacroNodeSpawnInfo(MacroGraph));
						}

					}
				}
			}
		}

		// If spawn info was created, setup a UI Command for keybinding.
		if(InfoPtr.IsValid())
		{
			TSharedPtr< FUICommandInfo > CommandInfo;

			FKey Key;
			bool bShift = false;
			bool bCtrl = false;
			bool bAlt = false;
			bool bCmd = false;
			
			// Parse the keybinding information
			FString KeyString;
			if( FParse::Value(*NodeSpawns[x], TEXT("Key="), KeyString) )
			{
				Key = *KeyString;
			}

			if( Key.IsValid() )
			{
				FParse::Bool(*NodeSpawns[x], TEXT("Shift="), bShift);
				FParse::Bool(*NodeSpawns[x], TEXT("Alt="), bAlt);
				FParse::Bool(*NodeSpawns[x], TEXT("Ctrl="), bCtrl);
				FParse::Bool(*NodeSpawns[x], TEXT("Cmd="), bCmd);
			}

			FInputChord Chord(Key, EModifierKey::FromBools(bCtrl, bAlt, bShift, bCmd));

			FText CommandLabelText = FText::FromString( CommandLabel );
			FText Description = FText::Format( NSLOCTEXT("BlueprintEditor", "NodeSpawnDescription", "Hold down the bound keys and left click in the graph panel to spawn a {0} node."), CommandLabelText );

			FUICommandInfo::MakeCommandInfo( this->AsShared(), CommandInfo, FName(*NodeSpawns[x]), CommandLabelText, Description, FSlateIcon(FEditorStyle::GetStyleSetName(), *FString::Printf(TEXT("%s.%s"), *this->GetContextName().ToString(), *NodeSpawns[x])), EUserInterfaceActionType::Button, Chord );

			InfoPtr->CommandInfo = CommandInfo;

			NodeCommands.Add(InfoPtr);
		}
	}

	TSharedPtr<FNodeSpawnInfo> AddActorRefAction = MakeShareable(new FActorRefSpawnInfo);
	UI_COMMAND(AddActorRefAction->CommandInfo, "Add Selected Actor Reference(s)", "Spawns node(s) which reference the currently selected actor(s) in the level.", EUserInterfaceActionType::Button, FInputChord(EKeys::R));
	NodeCommands.Add(AddActorRefAction);
}