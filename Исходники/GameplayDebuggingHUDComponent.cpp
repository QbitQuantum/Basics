void AGameplayDebuggingHUDComponent::DrawOverHeadInformation(APlayerController* PC, class UGameplayDebuggingComponent *DebugComponent)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	APawn* MyPawn = Cast<APawn>(DebugComponent->GetSelectedActor());
	const FVector Loc3d = MyPawn ? MyPawn->GetActorLocation() + FVector(0.f, 0.f, MyPawn->GetSimpleCollisionHalfHeight()) : FVector::ZeroVector;

	if (OverHeadContext.Canvas->SceneView == NULL || OverHeadContext.Canvas->SceneView->ViewFrustum.IntersectBox(Loc3d, FVector::ZeroVector) == false)
	{
		return;
	}

	const FVector ScreenLoc = OverHeadContext.Canvas->Project(Loc3d);
	static const FVector2D FontScale(1.f, 1.f);
	UFont* Font = GEngine->GetSmallFont();

	float TextXL = 0.f;
	float YL = 0.f;
	FString ObjectName = FString::Printf( TEXT("{yellow}%s {white}(%s)"), *DebugComponent->ControllerName, *DebugComponent->PawnName);
	CalulateStringSize(OverHeadContext, OverHeadContext.Font, ObjectName, TextXL, YL);

	bool bDrawFullOverHead = MyPawn != nullptr && GetDebuggingReplicator()->GetSelectedActorToDebug() == MyPawn;
	float IconXLocation = OverHeadContext.DefaultX;
	float IconYLocation = OverHeadContext.DefaultY;
	if (bDrawFullOverHead)
	{
		OverHeadContext.DefaultX -= (0.5f*TextXL*FontScale.X);
		OverHeadContext.DefaultY -= (1.2f*YL*FontScale.Y);
		IconYLocation = OverHeadContext.DefaultY;
		OverHeadContext.CursorX = OverHeadContext.DefaultX;
		OverHeadContext.CursorY = OverHeadContext.DefaultY;
	}

	if (DebugComponent->DebugIcon.Len() > 0)
	{
		UTexture2D* RegularIcon = (UTexture2D*)StaticLoadObject(UTexture2D::StaticClass(), NULL, *DebugComponent->DebugIcon, NULL, LOAD_NoWarn | LOAD_Quiet, NULL);
		if (RegularIcon)
		{
			FCanvasIcon Icon = UCanvas::MakeIcon(RegularIcon);
			if (Icon.Texture)
			{
				const float DesiredIconSize = bDrawFullOverHead ? 32.f : 16.f;
				DrawIcon(OverHeadContext, FColor::White, Icon, IconXLocation, IconYLocation - DesiredIconSize, DesiredIconSize / Icon.Texture->GetSurfaceWidth());
			}
		}
	}

	if (bDrawFullOverHead)
	{
		OverHeadContext.FontRenderInfo.bEnableShadow = bDrawFullOverHead;
		PrintString(OverHeadContext, bDrawFullOverHead ? FColor::White : FColor(255, 255, 255, 128), FString::Printf(TEXT("%s\n"), *ObjectName));
		OverHeadContext.FontRenderInfo.bEnableShadow = false;
	}

	if (EngineShowFlags.DebugAI)
	{
		DrawPath(PC, DebugComponent);
	}
#endif //!(UE_BUILD_SHIPPING || UE_BUILD_TEST)
}