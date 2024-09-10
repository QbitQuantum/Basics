void FEdMode::Render(const FSceneView* View,FViewport* Viewport,FPrimitiveDrawInterface* PDI)
{
    // Let the current mode tool render if it wants to
    FModeTool* tool = GetCurrentTool();
    if( tool )
    {
        tool->Render( View, Viewport, PDI );
    }

    if(UsesPropertyWidgets())
    {
        bool bHitTesting = PDI->IsHitTesting();
        AActor* SelectedActor = GetFirstSelectedActorInstance();
        if (SelectedActor != NULL)
        {
            UClass* Class = SelectedActor->GetClass();
            TArray<FPropertyWidgetInfo> WidgetInfos;
            GetPropertyWidgetInfos(Class, SelectedActor, WidgetInfos);
            FEditorScriptExecutionGuard ScriptGuard;
            for(int32 i=0; i<WidgetInfos.Num(); i++)
            {
                FString WidgetName = WidgetInfos[i].PropertyName;
                FName WidgetValidator = WidgetInfos[i].PropertyValidationName;
                int32 WidgetIndex = WidgetInfos[i].PropertyIndex;
                bool bIsTransform = WidgetInfos[i].bIsTransform;

                bool bSelected = (WidgetName == EditedPropertyName) && (WidgetIndex == EditedPropertyIndex);
                FColor WidgetColor = bSelected ? FColor::White : FColor(128, 128, 255);

                FVector LocalPos = FVector::ZeroVector;
                if(bIsTransform)
                {
                    FTransform LocalTM = GetPropertyValueByName<FTransform>(SelectedActor, WidgetName, WidgetIndex);
                    LocalPos = LocalTM.GetLocation();
                }
                else
                {
                    LocalPos = GetPropertyValueByName<FVector>(SelectedActor, WidgetName, WidgetIndex);
                }

                FTransform ActorToWorld = SelectedActor->ActorToWorld();
                FVector WorldPos = ActorToWorld.TransformPosition(LocalPos);

                UFunction* ValidateFunc= NULL;
                if(WidgetValidator != NAME_None &&
                        (ValidateFunc = SelectedActor->FindFunction(WidgetValidator)) != NULL)
                {
                    FString ReturnText;
                    SelectedActor->ProcessEvent(ValidateFunc, &ReturnText);

                    //if we have a negative result, the widget color is red.
                    WidgetColor = ReturnText.IsEmpty() ? WidgetColor : FColor::Red;
                }

                FTranslationMatrix WidgetTM(WorldPos);

                const float WidgetSize = 0.035f;
                const float ZoomFactor = FMath::Min<float>(View->ViewMatrices.ProjMatrix.M[0][0], View->ViewMatrices.ProjMatrix.M[1][1]);
                const float WidgetRadius = View->Project(WorldPos).W * (WidgetSize / ZoomFactor);

                if(bHitTesting) PDI->SetHitProxy( new HPropertyWidgetProxy(WidgetName, WidgetIndex, bIsTransform) );
                DrawWireDiamond(PDI, WidgetTM, WidgetRadius, WidgetColor, SDPG_Foreground );
                if(bHitTesting) PDI->SetHitProxy( NULL );
            }
        }
    }
}