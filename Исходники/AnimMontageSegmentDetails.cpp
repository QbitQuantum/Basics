void SAnimationSegmentViewport::InitSkeleton()
{
	UObject *Object = NULL;
	AnimRefPropertyHandle->GetValue(Object);
	UAnimSequenceBase *AnimSequence = Cast<UAnimSequenceBase>(Object);
	USkeleton *Skeleton = NULL;
	if(AnimSequence != NULL)
	{
		Skeleton = AnimSequence->GetSkeleton();
	}

	if( PreviewComponent != NULL && Skeleton != NULL )
	{
		USkeletalMesh* PreviewMesh = Skeleton->GetAssetPreviewMesh(AnimSequence);
		if (PreviewMesh)
		{
			UAnimSingleNodeInstance * Preview = PreviewComponent->PreviewInstance;
			if((Preview == NULL || Preview->GetCurrentAsset() != AnimSequence) ||
				(PreviewComponent->SkeletalMesh != PreviewMesh))
			{
				PreviewComponent->SetSkeletalMesh(PreviewMesh);
				PreviewComponent->EnablePreview(true, AnimSequence, NULL);
				PreviewComponent->PreviewInstance->SetLooping(true);

				//Place the camera at a good viewer position
				FVector NewPosition = LevelViewportClient->GetViewLocation();
				NewPosition.Normalize();
				LevelViewportClient->SetViewLocation(NewPosition * (PreviewMesh->GetImportedBounds().SphereRadius*1.5f));
			}
		}
	}

	TargetSkeleton = Skeleton;
}