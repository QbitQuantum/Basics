bool FSCSEditorViewportClient::InputWidgetDelta( FViewport* Viewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale )
{
	bool bHandled = false;
	if(bIsManipulating && CurrentAxis != EAxisList::None)
	{
		bHandled = true;
		AActor* PreviewActor = GetPreviewActor();
		if(PreviewActor)
		{
			TArray<FSCSEditorTreeNodePtrType> SelectedNodes = BlueprintEditorPtr.Pin()->GetSelectedSCSEditorTreeNodes();
			if(SelectedNodes.Num() > 0)
			{
				FVector ModifiedScale = Scale;
				if( GEditor->UsePercentageBasedScaling() )
				{
					ModifiedScale = Scale * ((GEditor->GetScaleGridSize() / 100.0f) / GEditor->GetGridSize());
				}

				TSet<USceneComponent*> UpdatedComponents;

				for(auto It(SelectedNodes.CreateIterator());It;++It)
				{
					FSCSEditorTreeNodePtrType SelectedNodePtr = *It;
					// Don't allow editing of a root node, inherited SCS node or child node that also has a movable (non-root) parent node selected
					const bool bCanEdit =  !SelectedNodePtr->IsRoot() && !SelectedNodePtr->IsInherited()
						&& !IsMovableParentNodeSelected(SelectedNodePtr, SelectedNodes);

					if(bCanEdit)
					{
						USceneComponent* SceneComp = Cast<USceneComponent>(SelectedNodePtr->FindComponentInstanceInActor(PreviewActor, true));
						USceneComponent* SelectedTemplate = Cast<USceneComponent>(SelectedNodePtr->GetComponentTemplate());
						if(SceneComp != NULL && SelectedTemplate != NULL)
						{
							// Cache the current default values for propagation
							FVector OldRelativeLocation = SelectedTemplate->RelativeLocation;
							FRotator OldRelativeRotation = SelectedTemplate->RelativeRotation;
							FVector OldRelativeScale3D = SelectedTemplate->RelativeScale3D;

							USceneComponent* ParentSceneComp = SceneComp->GetAttachParent();
							if( ParentSceneComp )
							{
								const FTransform ParentToWorldSpace = ParentSceneComp->GetSocketTransform(SceneComp->AttachSocketName);

								if(!SceneComp->bAbsoluteLocation)
								{
									Drag = ParentToWorldSpace.Inverse().TransformVector(Drag);
								}
								
								if(!SceneComp->bAbsoluteRotation)
								{
									Rot = (ParentToWorldSpace.Inverse().GetRotation() * Rot.Quaternion() * ParentToWorldSpace.GetRotation()).Rotator();
								}
							}

							FComponentEditorUtils::FTransformData OldDefaultTransform(*SelectedTemplate);

							TSharedPtr<ISCSEditorCustomization> Customization = BlueprintEditorPtr.Pin()->CustomizeSCSEditor(SceneComp);
							if(Customization.IsValid() && Customization->HandleViewportDrag(SceneComp, SelectedTemplate, Drag, Rot, ModifiedScale, GetWidgetLocation()))
							{
								UpdatedComponents.Add(SceneComp);
								UpdatedComponents.Add(SelectedTemplate);
							}
							else
							{
								// Apply delta to the preview actor's scene component
								GEditor->ApplyDeltaToComponent(
										SceneComp,
										true,
										&Drag,
										&Rot,
										&ModifiedScale,
										SceneComp->RelativeLocation );
								UpdatedComponents.Add(SceneComp);

							// Apply delta to the template component object
								GEditor->ApplyDeltaToComponent(
										SelectedTemplate,
										true,
										&Drag,
										&Rot,
										&ModifiedScale,
										SelectedTemplate->RelativeLocation );
								UpdatedComponents.Add(SelectedTemplate);
							}

							FComponentEditorUtils::FTransformData NewDefaultTransform(*SelectedTemplate);

							if (SelectedNodePtr->IsNative())
							{
								if (ensure(SelectedTemplate->HasAnyFlags(RF_DefaultSubObject)))
								{
									FComponentEditorUtils::PropagateTransformPropertyChange(SelectedTemplate, OldDefaultTransform, NewDefaultTransform, UpdatedComponents);
								}
							}

							if(PreviewBlueprint != NULL)
							{
								// Like PostEditMove(), but we only need to re-run construction scripts
								if(PreviewBlueprint && PreviewBlueprint->bRunConstructionScriptOnDrag)
								{
									PreviewActor->RerunConstructionScripts();
								}

								SceneComp->PostEditComponentMove(true); // @TODO HACK passing 'finished' every frame...

								// If a constraint, copy back updated constraint frames to template
								UPhysicsConstraintComponent* ConstraintComp = Cast<UPhysicsConstraintComponent>(SceneComp);
								UPhysicsConstraintComponent* TemplateComp = Cast<UPhysicsConstraintComponent>(SelectedTemplate);
								if(ConstraintComp && TemplateComp)
								{
									TemplateComp->ConstraintInstance.CopyConstraintGeometryFrom(&ConstraintComp->ConstraintInstance);
								}

								// Get the Blueprint class default object
								AActor* CDO = NULL;
								if(PreviewBlueprint->GeneratedClass)
								{
									CDO = Cast<AActor>(PreviewBlueprint->GeneratedClass->ClassDefaultObject);
								}
								else if(PreviewBlueprint->ParentClass)
								{
									CDO = Cast<AActor>(PreviewBlueprint->ParentClass->ClassDefaultObject);
								}

								if(CDO != NULL)
								{
									// Iterate over all the active archetype instances and propagate the change(s) to the matching component instance
									TArray<UObject*> ArchetypeInstances;
									CDO->GetArchetypeInstances(ArchetypeInstances);
									for(int32 InstanceIndex = 0; InstanceIndex < ArchetypeInstances.Num(); ++InstanceIndex)
									{
										AActor* ArchetypeInstance = Cast<AActor>(ArchetypeInstances[InstanceIndex]);
										if(ArchetypeInstance != NULL)
										{
											const bool bIsProcessingPreviewActor = (ArchetypeInstance == PreviewActor);
											SceneComp = Cast<USceneComponent>(SelectedNodePtr->FindComponentInstanceInActor(ArchetypeInstance, bIsProcessingPreviewActor));
											if(!bIsProcessingPreviewActor && SceneComp != nullptr && !UpdatedComponents.Contains(SceneComp))
											{
												FComponentEditorUtils::PropagateTransformPropertyChange(SceneComp, SceneComp->RelativeLocation, OldRelativeLocation, SelectedTemplate->RelativeLocation, UpdatedComponents);
												FComponentEditorUtils::PropagateTransformPropertyChange(SceneComp, SceneComp->RelativeRotation, OldRelativeRotation, SelectedTemplate->RelativeRotation, UpdatedComponents);
												FComponentEditorUtils::PropagateTransformPropertyChange(SceneComp, SceneComp->RelativeScale3D,  OldRelativeScale3D,  SelectedTemplate->RelativeScale3D,  UpdatedComponents);
											}
										}
									}
								}
							}
						}
					}
				}
				GUnrealEd->RedrawLevelEditingViewports();
			}
		}

		Invalidate();
	}

	return bHandled;
}