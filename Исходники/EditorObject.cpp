/**
 * Parse and import text as property values for the object specified.  This function should never be called directly - use ImportObjectProperties instead.
 * 
 * @param	ObjectStruct				the struct for the data we're importing
 * @param	DestData					the location to import the property values to
 * @param	SourceText					pointer to a buffer containing the values that should be parsed and imported
 * @param	SubobjectRoot					when dealing with nested subobjects, corresponds to the top-most outer that
 *										is not a subobject/template
 * @param	SubobjectOuter				the outer to use for creating subobjects/components. NULL when importing structdefaultproperties
 * @param	Warn						output device to use for log messages
 * @param	Depth						current nesting level
 * @param	InstanceGraph				contains the mappings of instanced objects and components to their templates
 *
 * @return	NULL if the default values couldn't be imported
 */
static const TCHAR* ImportProperties(
	uint8*						DestData,
	const TCHAR*				SourceText,
	UStruct*					ObjectStruct,
	UObject*					SubobjectRoot,
	UObject*					SubobjectOuter,
	FFeedbackContext*			Warn,
	int32						Depth,
	FObjectInstancingGraph&		InstanceGraph,
	const TMap<FName, AActor*>* ActorRemapper
	)
{
	check(!GIsUCCMakeStandaloneHeaderGenerator);
	check(ObjectStruct!=NULL);
	check(DestData!=NULL);

	if ( SourceText == NULL )
		return NULL;

	// Cannot create subobjects when importing struct defaults, or if SubobjectOuter (used as the Outer for any subobject declarations encountered) is NULL
	bool bSubObjectsAllowed = !ObjectStruct->IsA(UScriptStruct::StaticClass()) && SubobjectOuter != NULL;

	// true when DestData corresponds to a subobject in a class default object
	bool bSubObject = false;

	UClass* ComponentOwnerClass = NULL;

	if ( bSubObjectsAllowed )
	{
		bSubObject = SubobjectRoot != NULL && SubobjectRoot->HasAnyFlags(RF_ClassDefaultObject);
		if ( SubobjectRoot == NULL )
		{
			SubobjectRoot = SubobjectOuter;
		}

		ComponentOwnerClass = SubobjectOuter != NULL
			? SubobjectOuter->IsA(UClass::StaticClass())
				? CastChecked<UClass>(SubobjectOuter)
				: SubobjectOuter->GetClass()
			: NULL;
	}
	

	// The PortFlags to use for all ImportText calls
	uint32 PortFlags = PPF_Delimited | PPF_CheckReferences;
	if (GIsImportingT3D)
	{
		PortFlags |= PPF_AttemptNonQualifiedSearch;
	}

	FString StrLine;

	TArray<FDefinedProperty> DefinedProperties;

	// Parse all objects stored in the actor.
	// Build list of all text properties.
	bool ImportedBrush = 0;
	int32 LinesConsumed = 0;
	while (FParse::LineExtended(&SourceText, StrLine, LinesConsumed, true))
	{
		// remove extra whitespace and optional semicolon from the end of the line
		{
			int32 Length = StrLine.Len();
			while ( Length > 0 &&
					(StrLine[Length - 1] == TCHAR(';') || StrLine[Length - 1] == TCHAR(' ') || StrLine[Length - 1] == 9) )
			{
				Length--;
			}
			if (Length != StrLine.Len())
			{
				StrLine = StrLine.Left(Length);
			}
		}

		if ( ContextSupplier != NULL )
		{
			ContextSupplier->CurrentLine += LinesConsumed;
		}
		if (StrLine.Len() == 0)
		{
			continue;
		}

		const TCHAR* Str = *StrLine;

		int32 NewLineNumber;
		if( FParse::Value( Str, TEXT("linenumber="), NewLineNumber ) )
		{
			if ( ContextSupplier != NULL )
			{
				ContextSupplier->CurrentLine = NewLineNumber;
			}
		}
		else if( GetBEGIN(&Str,TEXT("Brush")) && ObjectStruct->IsChildOf(ABrush::StaticClass()) )
		{
			// If SubobjectOuter is NULL, we are importing defaults for a UScriptStruct's defaultproperties block
			if ( !bSubObjectsAllowed )
			{
				Warn->Logf(ELogVerbosity::Error, TEXT("BEGIN BRUSH: Subobjects are not allowed in this context"));
				return NULL;
			}

			// Parse brush on this line.
			TCHAR BrushName[NAME_SIZE];
			if( FParse::Value( Str, TEXT("Name="), BrushName, NAME_SIZE ) )
			{
				// If an initialized brush with this name already exists in the level, rename the existing one.
				// It is deemed to be initialized if it has a non-zero poly count.
				// If it is uninitialized, the existing object will have been created by a forward reference in the import text,
				// and it will now be redefined.  This relies on the behavior that NewObject<> will return an existing pointer
				// if an object with the same name and outer is passed.
				UModel* ExistingBrush = FindObject<UModel>( SubobjectRoot, BrushName );
				if (ExistingBrush && ExistingBrush->Polys && ExistingBrush->Polys->Element.Num() > 0)
				{
					ExistingBrush->Rename();
				}

				// Create model.
				UModelFactory* ModelFactory = NewObject<UModelFactory>();
				ModelFactory->FactoryCreateText( UModel::StaticClass(), SubobjectRoot, FName(BrushName, FNAME_Add, true), RF_NoFlags, NULL, TEXT("t3d"), SourceText, SourceText+FCString::Strlen(SourceText), Warn );
				ImportedBrush = 1;
			}
		}
		else if (GetBEGIN(&Str, TEXT("Foliage")))
		{
			UFoliageType* SourceFoliageType;
			FName ComponentName;
			if (SubobjectRoot &&
				ParseObject<UFoliageType>(Str, TEXT("FoliageType="), SourceFoliageType, ANY_PACKAGE) &&
				FParse::Value(Str, TEXT("Component="), ComponentName) )
			{
				UPrimitiveComponent* ActorComponent = FindObjectFast<UPrimitiveComponent>(SubobjectRoot, ComponentName);

				if (ActorComponent && ActorComponent->GetComponentLevel())
				{
					AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActorForLevel(ActorComponent->GetComponentLevel(), true);

					FFoliageMeshInfo* MeshInfo = nullptr;
					UFoliageType* FoliageType = IFA->AddFoliageType(SourceFoliageType, &MeshInfo);

					const TCHAR* StrPtr;
					FString TextLine;
					while (MeshInfo && FParse::Line(&SourceText, TextLine))
					{
						StrPtr = *TextLine;
						if (GetEND(&StrPtr, TEXT("Foliage")))
						{
							break;
						}

						// Parse the instance properties
						FFoliageInstance Instance;
						FString Temp;
						if (FParse::Value(StrPtr, TEXT("Location="), Temp, false))
						{
							GetFVECTOR(*Temp, Instance.Location);
						}
						if (FParse::Value(StrPtr, TEXT("Rotation="), Temp, false))
						{
							GetFROTATOR(*Temp, Instance.Rotation, 1);
						}
						if (FParse::Value(StrPtr, TEXT("PreAlignRotation="), Temp, false))
						{
							GetFROTATOR(*Temp, Instance.PreAlignRotation, 1);
						}
						if (FParse::Value(StrPtr, TEXT("DrawScale3D="), Temp, false))
						{
							GetFVECTOR(*Temp, Instance.DrawScale3D);
						}
						FParse::Value(StrPtr, TEXT("Flags="), Instance.Flags);

						// Add the instance
						MeshInfo->AddInstance(IFA, FoliageType, Instance, ActorComponent);
					}
				}
			}
		}
		else if( GetBEGIN(&Str,TEXT("Object")))
		{
			// If SubobjectOuter is NULL, we are importing defaults for a UScriptStruct's defaultproperties block
			if ( !bSubObjectsAllowed )
			{
				Warn->Logf(ELogVerbosity::Error, TEXT("BEGIN OBJECT: Subobjects are not allowed in this context"));
				return NULL;
			}

			// Parse subobject default properties.
			// Note: default properties subobjects have compiled class as their Outer (used for localization).
			UClass*	TemplateClass = NULL;
			bool bInvalidClass = false;
			ParseObject<UClass>(Str, TEXT("Class="), TemplateClass, ANY_PACKAGE, &bInvalidClass);
			
			if (bInvalidClass)
			{
				Warn->Logf(ELogVerbosity::Error,TEXT("BEGIN OBJECT: Invalid class specified: %s"), *StrLine);
				return NULL;
			}

			// parse the name of the template
			FName	TemplateName = NAME_None;
			FParse::Value(Str,TEXT("Name="),TemplateName);
			if(TemplateName == NAME_None)
			{
				Warn->Logf(ELogVerbosity::Error,TEXT("BEGIN OBJECT: Must specify valid name for subobject/component: %s"), *StrLine);
				return NULL;
			}

			// points to the parent class's template subobject/component, if we are overriding a subobject/component declared in our parent class
			UObject* BaseTemplate = NULL;
			bool bRedefiningSubobject = false;
			if( TemplateClass )
			{
			}
			else
			{
				// next, verify that a template actually exists in the parent class
				UClass* ParentClass = ComponentOwnerClass->GetSuperClass();
				check(ParentClass);

				UObject* ParentCDO = ParentClass->GetDefaultObject();
				check(ParentCDO);

				BaseTemplate = StaticFindObjectFast(UObject::StaticClass(), SubobjectOuter, TemplateName);
				bRedefiningSubobject = (BaseTemplate != NULL);

				if (BaseTemplate == NULL)
				{
					BaseTemplate = StaticFindObjectFast(UObject::StaticClass(), ParentCDO, TemplateName);
				}
				
				if ( BaseTemplate == NULL )
				{
					// wasn't found
					Warn->Logf(ELogVerbosity::Error, TEXT("BEGIN OBJECT: No base template named %s found in parent class %s: %s"), *TemplateName.ToString(), *ParentClass->GetName(), *StrLine);
					return NULL;
				}

				TemplateClass = BaseTemplate->GetClass();
			}

			// because the outer won't be a default object

			checkSlow(TemplateClass != NULL);
			if (bRedefiningSubobject)
			{
				// since we're redefining an object in the same text block, only need to import properties again
				SourceText = ImportObjectProperties( (uint8*)BaseTemplate, SourceText, TemplateClass, SubobjectRoot, BaseTemplate,
													Warn, Depth + 1, ContextSupplier ? ContextSupplier->CurrentLine : 0, &InstanceGraph, ActorRemapper );
			}
			else 
			{
				UObject* Archetype = NULL;
				UObject* ComponentTemplate = NULL;

				// Since we are changing the class we can't use the Archetype,
				// however that is fine since we will have been editing the CDO anyways
				if (!FBlueprintEditorUtils::IsAnonymousBlueprintClass(SubobjectOuter->GetClass()))
				{
					// if an archetype was specified in the Begin Object block, use that as the template for the ConstructObject call.
					FString ArchetypeName;
					if (FParse::Value(Str, TEXT("Archetype="), ArchetypeName))
					{
						// if given a name, break it up along the ' so separate the class from the name
						FString ObjectClass;
						FString ObjectPath;
						if ( FPackageName::ParseExportTextPath(ArchetypeName, &ObjectClass, &ObjectPath) )
						{
							// find the class
							UClass* ArchetypeClass = (UClass*)StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *ObjectClass);
							if (ArchetypeClass)
							{
								// if we had the class, find the archetype
								Archetype = StaticFindObject(ArchetypeClass, ANY_PACKAGE, *ObjectPath);
							}
						}
					}
				}

				if (SubobjectOuter->HasAnyFlags(RF_ClassDefaultObject))
				{
					if (!Archetype) // if an archetype was specified explicitly, we will stick with that
					{
						Archetype = ComponentOwnerClass->GetDefaultSubobjectByName(TemplateName);
						if(Archetype)
						{
							if ( BaseTemplate == NULL )
							{
								// BaseTemplate should only be NULL if the Begin Object line specified a class
								Warn->Logf(ELogVerbosity::Error, TEXT("BEGIN OBJECT: The component name %s is already used (if you want to override the component, don't specify a class): %s"), *TemplateName.ToString(), *StrLine);
								return NULL;
							}

							// the component currently in the component template map and the base template should be the same
							checkf(Archetype==BaseTemplate,TEXT("OverrideComponent: '%s'   BaseTemplate: '%s'"), *Archetype->GetFullName(), *BaseTemplate->GetFullName());
						}
					}
				}
				else // handle the non-template case (subobjects and non-template components)
				{
					// don't allow Actor-derived subobjects
					if ( TemplateClass->IsChildOf(AActor::StaticClass()) )
					{
						Warn->Logf(ELogVerbosity::Error,TEXT("Cannot create subobjects from Actor-derived classes: %s"), *StrLine);
						return NULL;
					}

					ComponentTemplate = FindObject<UObject>(SubobjectOuter, *TemplateName.ToString());
					if (ComponentTemplate != NULL)
					{
						// if we're overriding a subobject declared in a parent class, we should already have an object with that name that
						// was instanced when ComponentOwnerClass's CDO was initialized; if so, it's archetype should be the BaseTemplate.  If it
						// isn't, then there are two unrelated subobject definitions using the same name.
						if ( ComponentTemplate->GetArchetype() != BaseTemplate )
						{
						}
						else if ( BaseTemplate == NULL )
						{
							// BaseTemplate should only be NULL if the Begin Object line specified a class
							Warn->Logf(ELogVerbosity::Error, TEXT("BEGIN OBJECT: A subobject named %s is already declared in a parent class.  If you intended to override that subobject, don't specify a class in the derived subobject definition: %s"), *TemplateName.ToString(), *StrLine);
							return NULL;
						}
					}

				}

				// Propagate object flags to the sub object.
				EObjectFlags NewFlags = SubobjectOuter->GetMaskedFlags( RF_PropagateToSubObjects );

				if (!Archetype) // no override and we didn't find one from the class table, so go with the base
				{
					Archetype = BaseTemplate;
				}

				UObject* OldComponent = NULL;
				if (ComponentTemplate)
				{
					bool bIsOkToReuse = ComponentTemplate->GetClass() == TemplateClass
						&& ComponentTemplate->GetOuter() == SubobjectOuter
						&& ComponentTemplate->GetFName() == TemplateName 
						&& (ComponentTemplate->GetArchetype() == Archetype || !Archetype);

					if (!bIsOkToReuse)
					{
						UE_LOG(LogEditorObject, Log, TEXT("Could not reuse component instance %s, name clash?"), *ComponentTemplate->GetFullName());
						ComponentTemplate->Rename(); // just abandon the existing component, we are going to create
						OldComponent = ComponentTemplate;
						ComponentTemplate = NULL;
					}
				}


				if (!ComponentTemplate)
				{
					ComponentTemplate = NewObject<UObject>(
						SubobjectOuter,
						TemplateClass,
						TemplateName,
						NewFlags,
						Archetype,
						!!SubobjectOuter,
						&InstanceGraph
						);
				}
				else
				{
					// We do not want to set RF_Transactional for construction script created components, so we have to monkey with things here
					if (NewFlags & RF_Transactional)
					{
						UActorComponent* Component = Cast<UActorComponent>(ComponentTemplate);
						if (Component && Component->IsCreatedByConstructionScript())
						{
							NewFlags &= ~RF_Transactional;
						}
					}

					// Make sure desired flags are set - existing object could be pending kill
					ComponentTemplate->ClearFlags(RF_AllFlags);
					ComponentTemplate->SetFlags(NewFlags);
				}

				// replace all properties in this subobject outer' class that point to the original subobject with the new subobject
				TMap<UObject*, UObject*> ReplacementMap;
				if (Archetype)
				{
					checkSlow(ComponentTemplate->GetArchetype() == Archetype);
					ReplacementMap.Add(Archetype, ComponentTemplate);
					InstanceGraph.AddNewInstance(ComponentTemplate);
				}
				if (OldComponent)
				{
					ReplacementMap.Add(OldComponent, ComponentTemplate);
				}
				FArchiveReplaceObjectRef<UObject> ReplaceAr(SubobjectOuter, ReplacementMap, false, false, true);

				// import the properties for the subobject
				SourceText = ImportObjectProperties(
					(uint8*)ComponentTemplate, 
					SourceText, 
					TemplateClass, 
					SubobjectRoot, 
					ComponentTemplate, 
					Warn, 
					Depth+1,
					ContextSupplier ? ContextSupplier->CurrentLine : 0,
					&InstanceGraph,
					ActorRemapper
					);
			}
		}
		else if( FParse::Command(&Str,TEXT("CustomProperties")))
		{
			check(SubobjectOuter);

			SubobjectOuter->ImportCustomProperties(Str, Warn);
		}
		else if( GetEND(&Str,TEXT("Actor")) || GetEND(&Str,TEXT("DefaultProperties")) || GetEND(&Str,TEXT("structdefaultproperties")) || (GetEND(&Str,TEXT("Object")) && Depth) )
		{
			// End of properties.
			break;
		}
		else if( GetREMOVE(&Str,TEXT("Component")) )
		{
			checkf(false, TEXT("Remove component is illegal in pasted text"));
		}
		else
		{
			// Property.
			UProperty::ImportSingleProperty(Str, DestData, ObjectStruct, SubobjectOuter, PortFlags, Warn, DefinedProperties);
		}
	}

	if (ActorRemapper)
	{
		for (const auto& DefinedProperty : DefinedProperties)
		{
			RemapProperty(DefinedProperty.Property, DefinedProperty.Index, *ActorRemapper, DestData);
		}
	}

	// Prepare brush.
	if( ImportedBrush && ObjectStruct->IsChildOf<ABrush>() && !ObjectStruct->IsChildOf<AVolume>() )
	{
		check(GIsEditor);
		ABrush* Actor = (ABrush*)DestData;
		check(Actor->GetBrushComponent());
		if( Actor->GetBrushComponent()->Mobility == EComponentMobility::Static )
		{
			// Prepare static brush.
			Actor->SetNotForClientOrServer();
		}
		else
		{
			// Prepare moving brush.
			FBSPOps::csgPrepMovingBrush( Actor );
		}
	}

	return SourceText;
}